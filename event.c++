#import "event.h"
#import "rmr.h"
#import "top.h"

void       tick_e::operator()(target_t& target) const { target(*this); }
void     verify_e::operator()(target_t& target) const { target(*this); }
void       quit_e::operator()(target_t& target) const { target(*this); }
void     rename_e::operator()(target_t& target) const { target(*this); }
void       hide_e::operator()(target_t& target) const { target(*this); }
void       show_e::operator()(target_t& target) const { target(*this); }
void  character_e::operator()(target_t& target) const { target(*this); }
void    mouseup_e::operator()(target_t& target) const { target(*this); }
void  mousedown_e::operator()(target_t& target) const { target(*this); }
void mouseenter_e::operator()(target_t& target) const { target(*this); }
void mouseleave_e::operator()(target_t& target) const { target(*this); }
void  mousemove_e::operator()(target_t& target) const { target(*this); }
void     resize_e::operator()(target_t& target) const { target(*this); }
void     scroll_e::operator()(target_t& target) const { target(*this); }
void    keydown_e::operator()(target_t& target) const { target(*this); }
void      keyup_e::operator()(target_t& target) const { target(*this); }
void  keyrepeat_e::operator()(target_t& target) const { target(*this); }
void     render_e::operator()(target_t& target) const { target(*this); }
void       draw_e::operator()(target_t& target) const { target(*this); }
void       push_e::operator()(target_t& target) const { target(*this); }

event_t::event_t() : time(rmr.now()), cancelled(false) {
}

event_t::operator bool() const {
  return !cancelled;
}

tick_e::tick_e() : dt(0), count(0) {
}

tick_e tick_e::next() const {
  tick_e e;
  e.dt     = e.time - time;
  e.count  = count + 1;
  return e;
}

bool tick_e::first() const {
  return count == 0;
}

double tick_e::elapsed() const {
  return rmr.now() - time;
}

bool push_e::down() const { return type == 0; }
bool push_e::up()   const { return type == 1; }
bool push_e::set()  const { return type == 2; }

character_e::character_e(int codepoint) : codepoint(codepoint) {
  int i = wctomb(str, codepoint);
  str[i] = '\0';
}

render_e::render_e(tick_e& tick) : tick(tick) {
}

draw_e::draw_e(tick_e& tick) : tick(tick) {
}

tick_e tick_e::operator++(int) {
  tick_e last = *this;
  *this = next();
  return last;
}

    keyup_e::    keyup_e() { up     = true; }
  keydown_e::  keydown_e() { down   = true; }
keyrepeat_e::keyrepeat_e() { repeat = true; }
