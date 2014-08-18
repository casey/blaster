template<typename T, int N>
struct $array {
  using A = T[N];
  $array(A& _) : _(_) { }
  A& _;

  T min(T initial) { T result = initial; for (T x : _) result = std::min(result, x); return result; }
  T max(T initial) { T result = initial; for (T x : _) result = std::max(result, x); return result; }
  T min() { return min(std::numeric_limits<T>::min()); }
  T max() { return max(std::numeric_limits<T>::min()); }
};

template<typename T, int N>
inline $array<T, N> $(T(&_)[N]) { return $array<T, N>(_); }

struct $number {
  $number(double _) : _(_) { }
  $number min(double x);
  double operator()() { return _; }
  double _;
};

inline $number $(double _) { return $number(_); }
