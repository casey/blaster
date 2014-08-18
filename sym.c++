#import "sym.h"

#import <objc/objc.h>

sym_t::sym_t()                 : s(nullptr)                       { }
sym_t::sym_t(SEL x)            : s(x)                             { }
sym_t::sym_t(const sym_t& x)   : s(x.s)                           { }
sym_t::sym_t(const char* p)    : s(sel_registerName(p))           { }
sym_t::sym_t(const string& str): s(sel_registerName(str.c_str())) { }
sym_t::sym_t(string&& str)     : s(sel_registerName(str.c_str())) { }

SEL sym_t::selector() const { 
  return s;
}

const string& sym_t::str() const { 
  static map<const char*, string> cache;
  const char* s = c_str();
  return cache.emplace(s, s).first->second;
}

const char* sym_t::c_str() const { 
  return s == nullptr ? "" : sel_getName(s);
}

sym_t::operator const string&() const {
  return str();
}

sym_t::operator bool() const {
  return s;
}

bool sym_t::operator==(const sym_t& sym) const {
  return s == sym.s;
}

bool sym_t::operator!=(const sym_t& sym) const {
  return !(*this == sym);
}

bool sym_t::operator==(const string& s) const {
  return str() == s;
}

bool sym_t::operator!=(const string& s) const {
  return !(*this == s);
}

bool sym_t::operator==(const char* s) const {
  return strcmp(c_str(), s) == 0;
}

bool sym_t::operator!=(const char* s) const {
  return !(*this == s);
}

sym_t sym_t::gensym() {
  static int counter = 0;
  stringstream s;
  s << "__" << counter++ << "__";
  return sym_t(s.str());
}

ostream& operator<<(ostream& os, const sym_t& s) {
  return os << (const string&)s;
}

string operator+(const string& lhs, sym_t rhs) {
  return lhs + rhs.str();
}

sym_t operator""_sym(const char* b, size_t l) {
  return sym_t(string(b, l));
}

size_t std::hash<sym_t>::operator()(sym_t const& s) const {
  return std::hash<SEL>()(s.selector());
}
