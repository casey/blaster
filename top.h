#import "event.h"
#import "target.h"
#import "unique.h"

struct top_t : noncopyable_t, null_target_t {
  using _ = top_t&;
  _ broadcast(const event_t&);
  _ emit(const event_t&);
  virtual ~top_t();
  _ spawn();
  _ parent();
  _ clear();

  _ for_each(fun_t<void(top_t&)>);
  _ for_ancestors(fun_t<void(top_t&)>);
  _ for_descendants(fun_t<void(top_t&)>);

  unique_ptr<top_t> orphan();

  using iterator_t = unique_iterator_t<top_t>;

  iterator_t begin();
  iterator_t end();

  _ child(size_t);

  _ adopt(top_t&);
  _ adopt(unique_ptr<top_t>);

  bool is_root();

  template<typename T, typename ...P>
  T& spawn(P&&... args) {
    imprint();
    return *new T(std::forward<P>(args)...);
  }

  template<typename T, typename ...P>
  _ add(P&&... args) {
    spawn<T, P...>(std::forward<P>(args)...);
    return *this;
  }

  template<typename T>
  bool is() {
    return !!dynamic_cast<T*>(this);
  }

  template<typename T>
  T& as() {
    T* p = dynamic_cast<T*>(this);
    p || rmr_die("top.as: cast failed");
    return *p;
  }

  bool operator==(const top_t&) const;
  bool operator!=(const top_t&) const;

  const string& name();
  _ name(const string&);

  bool hidden();
  _ hidden(bool);
  _ toggle();
  _ hide();
  _ show();

  u64 id();

  explicit operator bool() const;

  _ tree();

  top_t(nothing_t);

protected:
  top_t();

private:
  _ tree(int indent);

  _ imprint();
  top_t(top_t*);
  struct data_t;
  data_t& __;
};
