struct $number {
  $number(double _) : _(_) { }
  $number min(double x);
  double operator()() { return _; }
  double _;
};

inline $number $(double _) { return $number(_); }
