#import "val.h"
#import "rmr.h"
#import "fmt.h"

#import "yajl/yajl_tree.h"
#import "yajl/yajl_gen.h"

// SECTION: DATA

struct payload_t {
  virtual bool truthy()      const = 0;
  virtual void gen(yajl_gen) const = 0;
  virtual ~payload_t() { }
};

struct val_t::data_t {
  const payload_t* get()        { return __.get(); }
  const payload_t* operator->() { return get();    }
  std::shared_ptr<payload_t> __;
};

struct null_payload_t : payload_t {
  virtual bool truthy()          const { return false;                 }
  virtual void gen(yajl_gen gen) const { yajl_gen_null(gen);           }
};

struct boolean_payload_t : payload_t {
  boolean_payload_t(bool x) : x(x) { }
  const bool x;
  virtual bool truthy()          const { return x;                         }
  virtual void gen(yajl_gen gen) const { yajl_gen_bool(gen, x);            }
};

struct string_payload_t : payload_t {
  string_payload_t(const string& x) : x(x) { }
  const string x;
  virtual bool truthy()          const { return !x.empty();                                      }
  virtual void gen(yajl_gen gen) const { yajl_gen_string(gen, (uchar*)x.c_str(), x.length());    }
};

struct number_payload_t : payload_t {
  number_payload_t(double x) : x(x) { }
  const double x;
  virtual bool truthy()          const { return x != 0.0;                 }
  virtual void gen(yajl_gen gen) const { yajl_gen_double(gen, x);         }
};

struct object_payload_t : payload_t {
  object_payload_t(const map<string, val_t>& x) : x(x) {}
  const map<string, val_t> x;
  virtual bool truthy()          const { return !x.empty(); }
  virtual void gen(yajl_gen gen) const {
    yajl_gen_map_open(gen);
    for (auto& _ : x) {
      string_payload_t(_.first).gen(gen);
      _.second.__->gen(gen);
    }
    yajl_gen_map_close(gen);
  }
};

struct array_payload_t : payload_t {
  array_payload_t(const vector<val_t>& x) : x(x) {}
  array_payload_t(init_t<val_t>        x) : x(x) {}
  const vector<val_t> x;
  virtual bool truthy() const { return !x.empty(); }
  virtual void gen(yajl_gen gen) const {
    yajl_gen_array_open(gen);
    for (auto& _ : x) _.__->gen(gen);
    yajl_gen_array_close(gen);
  }
};


// SECTION: VAL

val_t::val_t(                           ) : __(*new data_t{std::make_shared<   null_payload_t>( )}) { }
val_t::val_t(bool                      _) : __(*new data_t{std::make_shared<boolean_payload_t>(_)}) { }
val_t::val_t(const string&             _) : __(*new data_t{std::make_shared< string_payload_t>(_)}) { }
val_t::val_t(const char*               _) : __(*new data_t{std::make_shared< string_payload_t>(_)}) { }
val_t::val_t(double                    _) : __(*new data_t{std::make_shared< number_payload_t>(_)}) { }
val_t::val_t(const vector<val_t>&      _) : __(*new data_t{std::make_shared<  array_payload_t>(_)}) { }
val_t::val_t(const map<string, val_t>& _) : __(*new data_t{std::make_shared< object_payload_t>(_)}) { }
val_t::val_t(const val_t&              _) : __(*new data_t{_.__.__                               }) { }

const    null_payload_t*    null_payload_pointer(val_t v) { return dynamic_cast<const    null_payload_t*>(v.__.get()); }
const  string_payload_t*  string_payload_pointer(val_t v) { return dynamic_cast<const  string_payload_t*>(v.__.get()); }
const  number_payload_t*  number_payload_pointer(val_t v) { return dynamic_cast<const  number_payload_t*>(v.__.get()); }
const boolean_payload_t* boolean_payload_pointer(val_t v) { return dynamic_cast<const boolean_payload_t*>(v.__.get()); }
const   array_payload_t*   array_payload_pointer(val_t v) { return dynamic_cast<const   array_payload_t*>(v.__.get()); }
const  object_payload_t*  object_payload_pointer(val_t v) { return dynamic_cast<const  object_payload_t*>(v.__.get()); }

bool val_t::is_null   () { return !!   null_payload_pointer(*this); }
bool val_t::is_string () { return !! string_payload_pointer(*this); }
bool val_t::is_number () { return !! number_payload_pointer(*this); }
bool val_t::is_boolean() { return !!boolean_payload_pointer(*this); }
bool val_t::is_array  () { return !!  array_payload_pointer(*this); }
bool val_t::is_object () { return !! object_payload_pointer(*this); }

void* val_t::as_null() { is_null() || rmr.die("val.as_null: non-null value"); return nullptr; }

const string& val_t::as_string() {
  auto p = string_payload_pointer(*this);
  p || rmr.die("val.as_string: non-string value");
  return p->x;
}

double val_t::as_number() {
  auto p = number_payload_pointer(*this);
  p || rmr.die("val.as_number: non-number value");
  return p->x;
}

bool val_t::as_boolean() {
  auto p = boolean_payload_pointer(*this);
  p || rmr.die("val.as_boolean: non-boolean value");
  return p->x;
}

const vector<val_t>& val_t::as_array () {
  auto p = array_payload_pointer(*this);
  p || rmr.die("val.as_array: non-array value");
  return p->x;
}

const map<string, val_t>& val_t::as_object () {
  auto p = object_payload_pointer(*this);
  p || rmr.die("val.as_object: non-object value");
  return p->x;
}

void*                     val_t::nil() { return as_null   (); }
const string&             val_t::str() { return as_string (); }
double                    val_t::num() { return as_number (); }
bool                      val_t::bln() { return as_boolean(); }
const vector<val_t>&      val_t::ary() { return as_array  (); }
const map<string, val_t>& val_t::obj() { return as_object (); }

val_t val_t::get(const string& key) {
  auto& o = as_object();
  auto i = o.find(key);

  if (i == o.end()) {
    rmr.die("val.get: missing key: %"_fmt(key));
  }

  return i->second;
}

bool val_t::has(const string& key) {
  auto& o = as_object();
  return o.find(key) != o.end();
}

val_t& val_t::operator=(const val_t& _) {
  __.__ = _.__.__;
  return *this;
}

val_t::~val_t() {
  delete &__;
}

string val_t::dump() {
  auto gen = yajl_gen_alloc(nullptr);
  yajl_gen_config(gen, yajl_gen_validate_utf8, 1);
  __->gen(gen);
  const char* buf;
  size_t len;
  yajl_gen_get_buf(gen, (const unsigned char**)&buf, &len);
  auto s = string(buf, len);
  yajl_gen_free(gen);
  return s;
}

val_t parse_any(yajl_val);

val_t::operator bool() const {
  return __->truthy();
}

val_t val_t::parse(const string& s) {
  char errbuf[1024];
  errbuf[0] = 0;

  auto yt = yajl_tree_parse(s.c_str(), errbuf, sizeof(errbuf));
  string err = errbuf;
  err.empty() || rmr.die("val.parse: %"_fmt(err));
  val_t v = parse_any(yt);
  yajl_tree_free(yt);

  return v;
};

// SECTION: PARSE

val_t parse_integer(yajl_val x) { return val_t((double)x->u.number.i);                                };
val_t parse_double (yajl_val x) { return val_t(x->u.number.d);                                        };
val_t parse_string (yajl_val x) { return val_t(x->u.string);                                          };
val_t parse_true   (yajl_val x) { return val_t(true);                                                 };
val_t parse_false  (yajl_val x) { return val_t(false);                                                };
val_t parse_null   (yajl_val x) { return val_t();                                                     };
val_t parse_number (yajl_val x) { rmr.die("val.parse: unrepresentable number: %"_fmt(x->u.number.r)); };

val_t parse_object(yajl_val x) {
  auto k = x->u.object.keys;
  auto v = x->u.object.values;
  auto n = x->u.object.len;
  map<string, val_t> m;
  for (int i = 0; i < n; i++) m.insert({string(k[i]), parse_any(v[i])});
  return val_t(m);
}

val_t parse_array(yajl_val x) {
  auto p = x->u.array.values;
  auto n = x->u.array.len;
  vector<val_t> v;
  for (int i = 0; i < n; i++) v.push_back(parse_any(p[i]));
  return val_t(v);
}

val_t parse_any(yajl_val x) {
  if (YAJL_IS_STRING (x)) return parse_string (x);
  if (YAJL_IS_INTEGER(x)) return parse_integer(x);
  if (YAJL_IS_DOUBLE (x)) return parse_double (x); 
  if (YAJL_IS_NUMBER (x)) return parse_number (x);
  if (YAJL_IS_OBJECT (x)) return parse_object (x); 
  if (YAJL_IS_ARRAY  (x)) return parse_array  (x); 
  if (YAJL_IS_TRUE   (x)) return parse_true   (x); 
  if (YAJL_IS_FALSE  (x)) return parse_false  (x); 
  if (YAJL_IS_NULL   (x)) return parse_null   (x); 
  rmr.die("parse_any: something went wrong");
}

// SECTION: EXTRAS

ostream& operator<<(ostream& o, val_t _) {
  return o << _.dump();
}
