template<typename T>
struct frame_t {
  frame_t(uint size, T* data) : _size(size), _data(data) {}

  template<typename Container>
  frame_t(Container& c) : _size(c.size()), _data(c.data()) {}

  uint size() const { return _size; }
  T*   data() const { return _data; }

  T& operator[] (size_t n) const {
    return data()[n];
  }

  using iterator_t = T*;

  iterator_t begin() const { return iterator_t(_data + 0);      }
  iterator_t end()   const { return iterator_t(_data + size()); }

private:
  uint _size;
  T*   _data;
};
