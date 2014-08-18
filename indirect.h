template<typename T>
struct indirect_iterator_t : std::iterator<std::input_iterator_tag, T> {
  indirect_iterator_t(T** pointer) : pointer(pointer) {}
  T& operator*() const { return **pointer; }
  bool operator!=(const indirect_iterator_t& x) const { return pointer != x.pointer; }
  indirect_iterator_t& operator++() { pointer++; return *this; }
private:
  T** pointer;
};
