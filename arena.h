struct arena_t {
  arena_t(size_t size);
  ~arena_t();

  template<typename T, typename... P>
  T* alloc(size_t count, P&&... args) {
    static_assert(std::is_trivially_destructible<T>::value, "arena.alloc: only trivially destructable types allowed");
    T* p = (T*)helper(alignof(T), sizeof(T), count);
    for (int i = 0; i < count; i++) new (p + i) T(std::forward<P>(args)...);
    return p;
  }

  template<typename T, typename... P>
  T* alloc_nontrivial(size_t count, P&&... args) {
    T* p = (T*)helper(alignof(T), sizeof(T), count);
    for (int i = 0; i < count; i++) new (p + i) T(std::forward<P>(args)...);
    return p;
  }

  template<typename T>
  void free_nontrivial(void* old_top, T* allocation, void* expected_top) {
    top() == expected_top || rmr_die("arena.free: out of order free");
    size_t count = ((T*)expected_top - allocation);
    for (int i = count - 1; i >= 0; i--) {
      allocation[i].~T();
    }
    space = size - ((char*)old_top - memory);
  }

  void   clear();
  size_t allocated();
  size_t available();
  void*  top();

  template<typename T>
  struct alloc_t {
    template<typename... P>
    alloc_t(arena_t& arena, size_t count, P&&... args) : arena(arena) {
      old_top    = arena.top();
      allocation = arena.alloc_nontrivial<T, P...>(count, std::forward<P>(args)...);
      new_top    = arena.top();
      active     = true;
    }

    alloc_t(alloc_t&& x)
      : arena(x.arena), old_top(x.old_top), allocation(x.allocation), new_top(x.new_top), active(x.active)
    {
      x.active = false;
    }

    ~alloc_t() {
      if (active) arena.free_nontrivial(old_top, allocation, new_top);
    }

    T* begin() { return allocation;  }
    T* end()   { return (T*)new_top; }

    T* data()    { return allocation; }
    T& at(int i) { auto p = allocation + i; p < new_top || rmr_die("arena.alloc.at: out of bounds"); return *p; }

  private:
    arena_t& arena;
    void*    old_top;
    T*       allocation;
    void*    new_top;
    bool     active;
  };

  template<typename T, typename ...P>
  alloc_t<T> scoped_alloc(size_t count, P&&... args) {
    return alloc_t<T>(*this, count, std::forward<P>(args)...);
  }

private:
  void* helper(size_t alignment, size_t size, size_t count);
  size_t size;
  size_t space;
  char*  memory;
};
