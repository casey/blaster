#define SYM(a) (sym_t(@selector(a)))

struct sym_t {
  sym_t();
  sym_t(const char*);
  sym_t(const string&);
  sym_t(string&&);
  sym_t(const sym_t&);
  explicit sym_t(SEL);
  SEL selector() const;
  bool operator==(const char*) const;
  bool operator!=(const char*) const;
  bool operator==(const string&) const;
  bool operator!=(const string&) const;
  bool operator==(const sym_t&) const;
  bool operator!=(const sym_t&) const;
  operator const string&() const;
  explicit operator bool() const;
  const string& str() const;
  const char*  c_str() const;

  static sym_t gensym();
private:
  SEL s;
};

string   operator+     (const string&, sym_t);
ostream& operator<<    (ostream&, const sym_t&);
sym_t    operator""_sym(const char*, size_t);

namespace std {
  template<>
  struct hash<sym_t> {
    size_t operator()(sym_t const&) const;
  };
}
