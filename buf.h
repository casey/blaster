struct buf_t {
  template<typename T>
  buf_t(T& x) {
    _buffer = &x;
    _size   = sizeof(T);
  }

  void*  buffer();
  size_t size();

private:
  void*  _buffer;
  size_t _size;
};
