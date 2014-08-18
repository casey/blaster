template<typename T>
struct counter_t {
  static int& count() {
    static int _ = 0;
    return _;
  }

  bool solo() { return count() == 1; };

   counter_t() { count()++; }
  ~counter_t() { count()--; }
};
