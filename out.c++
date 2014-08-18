#import "out.h"
#import "str.h"
#import "rmr.h"

using _ = out_t&;

out_t::out_t() : used(false), null(false), last(true), fatal(false) { }
out_t::out_t(out_t&  _) : out_t() { _.last = false; used = _.used; fatal = _.fatal; null = _.null; }
out_t::out_t(out_t&& _) : out_t() { _.last = false; used = _.used; fatal = _.fatal; null = _.null; }

_ out_t::operator<<(str_t _) {
  if (!null && rmr.loglevel() >= 0) cerr << _.str() << " ";
  used = true;
  return *this;
}

_ out_t::operator,(str_t _) { return *this << _; }
_ out_t::arm()    { fatal = true;  return *this; }
_ out_t::disarm() { fatal = false; return *this; }
_ out_t::off()    { null  = true;  return *this; }
_ out_t::on()     { null  = false; return *this; }

out_t::operator bool() { return true; }

out_t::~out_t() {
  if (last && used && !null) cerr << rmr_t::ansi_clear() << endl;
  cerr.flush();
  if (last && fatal) rmr_t::die("out_t: fatal");
}
