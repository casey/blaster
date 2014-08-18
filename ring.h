template<typename T, size_t N>
struct ring_t {
  T   buffer[N];
  u64 written = 0;
  u64 dropped = 0;

  ring_t(   ) {          }
  ring_t(T v) { fill(v); }

  u64  size()     const { return std::min(written - dropped, capacity()); }
  u64  capacity() const { return N;                                       }
  bool full()     const { return size() == capacity();                    }

  ring_t& set(T v) {
    for (int i = 0; i < capacity(); i++) write(v);
    return *this;
  }

  ring_t& fill(T v) {
    while (!full()) write(v);
    return *this;
  }

  T& get(int i) {
    return rmr.variable(rmr.constant(*this).get(i));
  }

  const T& get(int i) const {
    (i >= 0 && i < size()) || (rmr.fatal() << "ring_t.get: bad index:" << i);
    int index = (i + dropped) % capacity();
    return buffer[index];
  }

  ring_t& write(T v) {
    int index = (written % capacity());
    buffer[index] = v;
    written++;
    return *this;
  }

  T drop() {
    size() > 0 || rmr.die("ring_t.drop: drop called while empty");
    int index = dropped % capacity();
    T x = buffer[index];
    dropped++;
    return x;
  }

  struct const_iterator_t : std::iterator<std::input_iterator_tag, T> {
    const_iterator_t(const ring_t& ring, u64 index) : ring(ring), index(index) { }
    const T& operator*() const { return ring.get(index); }
    bool operator!=(const const_iterator_t& rhs) const { return index != rhs.index; }
    const_iterator_t& operator++() { index++; return *this; }
  private:
    const ring_t& ring;
    u64           index;
  };

  struct iterator_t : std::iterator<std::input_iterator_tag, T> {
    iterator_t(ring_t& ring, u64 index) : ring(ring), index(index) { }
    T& operator*() const { return ring.get(index); }
    bool operator!=(const iterator_t& rhs) const { return index != rhs.index; }
    iterator_t& operator++() { index++; return *this; }
  private:
    ring_t& ring;
    u64     index;
  };

  iterator_t       begin()       { return iterator_t      (*this, 0);      }
  iterator_t       end()         { return iterator_t      (*this, size()); }
  const_iterator_t begin() const { return const_iterator_t(*this, 0);      }
  const_iterator_t end()   const { return const_iterator_t(*this, size()); }
};
