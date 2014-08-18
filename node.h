#import "frame.h"
#import "indirect.h"

struct node_t {
  using _      = node_t&;
  using void_f = fun_t<void(node_t&)>;
  using pred_f = fun_t<bool(node_t&)>;
  using for_f  = fun_t<void(node_t&, int, int)>;
  using iter_f = fun_t<node_t*(node_t&, int, int)>;
  using tick_f = fun_t<void(node_t&, double, double)>;

  explicit node_t(const sym_t& name);
  node_t();
  ~node_t();

  void render(gl_t& gl, const frame_t<node_t*>& nodes);

  _ spawn(const sym_t& name = null_sym());
  _ clone(const sym_t& name);
  _ clone();

  template<typename Node>
  Node& spawn(const sym_t& name = null_sym()) {
    static_assert(std::is_base_of<node_t, Node>::value, "node_t must be base of Node");
    imprint(name, nullptr);
    return *new Node();
  }

  template<typename Node>
  Node& clone(const sym_t& name) {
    static_assert(std::is_base_of<node_t, Node>::value, "node_t must be base of Node");
    parent().imprint(name, this);
    return *new Node();
  }

  _ for_each(void_f);
  _ for_each(pred_f);
  _ for_each(const sym_t&, void_f);
  _ iterate(int n, for_f);
  _ iterate(int n, iter_f);
  _ traverse(void_f);
  _ traverse(pred_f);
  _ find(const sym_t&);
  _ chain_tick(tick_f);

  using iterator_t = indirect_iterator_t<node_t>;
  iterator_t begin();
  iterator_t end();

  _ adopt(node_t&);
  _ orphan();
  _ name(const sym_t&);
  _ parent();
  _ up();
  _ child(int);
  _ root();
  _ transform(const mat4&);
  _ matrix(const mat4&);
  _ mul(const mat4&);
  _ translate(float, float, float);
  _ translate(const vec3&);
  _ translate_x(float);
  _ translate_y(float);
  _ translate_z(float);
  _ scale(float, float, float);
  _ scale(const vec3&);
  _ scale(float);
  _ tree(int indent = 0);
  _ hidden(bool);
  _ toggle();
  _ show();
  _ hide();
  _ tick(double, double);

  bool         is_leaf();
  bool         is_root();
  const sym_t& name();
  int          child_count();
  int          height();
  int          depth();
  const mat4&  transform() const;
  mat4&        transform();
  const mat4&  matrix() const;
  mat4&        matrix();
  u64          id();
  int          population();

  bool         hidden();

  bool operator==(const node_t&);

private:
  _ imprint(const sym_t& name, node_t* blueprint);

  node_t(const node_t&)            = delete;
  node_t& operator=(const node_t&) = delete;
  struct data_t;
  data_t& __;
};
