struct hashify_t {
  template<typename T>
  hashify_t(const T& x) : hash(std::hash<T>()(x)) {}
  operator size_t() const;
private:
  size_t hash;
};

using hash_t = const hashify_t&;
