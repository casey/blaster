template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << "pair(" << p.first << ", " << p.second << ")";
}

struct stringify_t {
  template<typename T>
  stringify_t(const T& x) {
    stringstream stream;
    stream << x;
    s = stream.str();
  }

  string str() const;

private:
  string s;
};

using str_t = const stringify_t&;
