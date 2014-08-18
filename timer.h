struct timer_t {
  timer_t();

  double elapsed();
  u64    ms();
  u64    ns();
  u64    us();
  void   reset();

private:
  std::chrono::system_clock::time_point start;
};
