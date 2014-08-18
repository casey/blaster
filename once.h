struct once_t {
  once_t();
  explicit operator bool();
private:
  bool triggered;
};
