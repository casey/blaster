template<typename T>
struct ephemera_t {
  T    payload = {};
  bool valid   = false;

  template<typename ...P>
  void set(P&&... args) {
    valid && rmr_die("ephemera.set: spurious call");
    payload = T{std::forward<P>(args)...};
    valid = true;
  }

  T get() {
    valid || rmr_die("ephemera.get: spurious call");
    valid = false;
    return payload;
  }
};
