template <typename T>
struct seq_t {
  seq_t() { }

  template<typename S>
  seq_t(S& s) {
    using real_iterator_t = typename std::conditional< 
      std::is_const<S>::value,
      typename S::const_iterator,
      typename S::iterator
    >::type;

    b = new real_iterator_t(s.begin());
    e = new real_iterator_t(s.end  ());

    copy  = [](void* ip          ) -> void* { return new real_iterator_t(*(real_iterator_t*)ip);     };
    del   = [](void* ip          ) -> void  { delete (real_iterator_t*)ip;                           };
    inc   = [](void* ip          ) -> void  { (*(real_iterator_t*)ip)++;                             };
    deref = [](void* ip          ) -> T&    { return **(real_iterator_t*)ip;                         };
    equal = [](void* ap, void* bp) -> bool  { return *(real_iterator_t*)ap == *(real_iterator_t*)bp; };
  }

  seq_t(const seq_t& _) {
    copy  = _.copy;
    del   = _.del;
    inc   = _.inc;
    deref = _.deref;
    equal = _.equal;
    b = copy(_.b);
    e = copy(_.e);
  }

  seq_t& operator=(const seq_t&) = delete;

  void* b = nullptr;
  void* e = nullptr;

  void* (*copy )(void*       ) = [](void*) -> void*       { return nullptr;            };
  void  (*del  )(void*       ) = [](void*) -> void        {                            };
  void  (*inc  )(void*       ) = [](void*) -> void        {                            };
  T&    (*deref)(void*       ) = [](void*) -> T&          { static T _ = {}; return _; };
  bool  (*equal)(void*, void*) = [](void*, void*) -> bool { return true;               };

  ~seq_t() {
    del(b);
    del(e);
  }

  struct iterator_t : std::iterator<std::input_iterator_tag, T> {
    iterator_t(const seq_t& s, void* i) : s(s), i(s.copy(i)) { }
    ~iterator_t() { s.del(i); }
    T& operator*() const { return s.deref(i); }
    bool operator!=(const iterator_t& _) const { return !s.equal(i, _.i); }
    iterator_t& operator++() { s.inc(i); return *this; }
    seq_t s;
    void* i;
  };

  iterator_t begin() const {
    return iterator_t(*this, b);
  }

  iterator_t end() const {
    return iterator_t(*this, e);
  }
};
