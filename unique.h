template<typename T>
struct unique_iterator_t : std::iterator<std::input_iterator_tag, T> {
  unique_iterator_t(unique_ptr<T>* pointer) : pointer(pointer) {}
  T& operator*() const { return **pointer; }
  bool operator!=(const unique_iterator_t& x) const { return pointer != x.pointer; }
  unique_iterator_t& operator++() { pointer++; return *this; }
private:
  unique_ptr<T>* pointer;
};
