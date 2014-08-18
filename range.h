struct range_t {
  struct iterator_t : std::iterator<std::input_iterator_tag, int> {
    iterator_t(int count);

    const int&  operator* (                 ) const;
    iterator_t  operator++(int              )      ;
    iterator_t& operator++(                 )      ;
    iterator_t& operator+=(int n            )      ;
    bool        operator< (const iterator_t&) const;
    bool        operator==(const iterator_t&) const;
    bool        operator!=(const iterator_t&) const;
  private:
    int count;
  };

  range_t(int max);
  range_t(int min, int max);

  iterator_t begin() const;
  iterator_t end  () const;

private:
  int min;
  int max;
};
