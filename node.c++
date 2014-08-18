#import "node.h"
#import "sym.h"
#import "vec.h"
#import "rmr.h"
#import "once.h"
#import "gl.h"
#import "ephemera.h"

using _ = node_t&;
using iterator_t = node_t::iterator_t;

u64 next_id = 0;

struct imprint_t {
  node_t* begetter  = nullptr;
  sym_t   begotten  = SYM(BAD_SPAWN);
  node_t* blueprint = nullptr;
};

ephemera_t<imprint_t> imprint;

struct node_t::data_t {
  sym_t           name      {                };
  mat4            transform {mat4::identity()};
  mat4            matrix    {rmr.whatever()  };
  bool            hidden    {false           };
  node_t*         parent    {nullptr         };
  vector<node_t*> children  {                };
  vector<tick_f>  ticks     {                };
  population_t    pop       {                };
  u64             id        {next_id++       };
};

node_t::node_t() : __(*new data_t) {
  auto i = ::imprint.get();
  __.name   = i.begotten;
  __.parent = i.begetter;
  __.parent->__.children.push_back(this);

  if (i.blueprint) {
    auto& b = *i.blueprint;
    transform(b.transform());
    hidden(b.hidden());
    __.ticks = b.__.ticks;

    for (int j = 0; j < b.child_count(); j++) {
      adopt(b.child(j).clone().orphan());
    }
  }
}

node_t::node_t(const sym_t& name) : __(*new data_t) {
  __.name = name;
}

node_t::~node_t() {
  for (auto child : __.children) delete child;
  delete &__;
}

void node_t::render(gl_t& gl, const frame_t<node_t*>& nodes) {
  static once_t once;
  if (once) {
    vec4 position = {0, 0, 0, 1};
    gl
    .new_vbo(SYM(position))
    .buffer_data_dynamic(SYM(position), sizeof(position), &position)
    ;
  }

  for (auto node : nodes) {
    gl
    .point_size(10.0)
    .prepare(SYM(node))
    .value(SYM(transform), node->matrix())
    .value(SYM(color), vec3::hash(node).extend(1.0))
    .pack({SYM(position)},  SYM(position))
    .ready()
    .points()
    .draw_arrays(0, 1)
    .done()
    ;
  }
}

u64 node_t::id() {
  return __.id;
}

_ node_t::tree(int indent) {
  cerr << string(indent, ' ');
  if (name()) cerr << name();
  else        cerr << "node:" << id();
  cerr << endl;
  for (auto child : __.children) child->tree(indent + 2);
  return *this;
}

int node_t::population() {
  int p = 1;
  for (auto& child : *this) {
    p += child.population();
  }
  return p;
}

_ node_t::traverse(void_f f) {
  f(*this);
  for (auto child : __.children) child->traverse(f);
  return *this;
}

_ node_t::iterate(int n, for_f f) {
  for (int i = 0; i < n; i++) {
    f(*this, n, i);
  }
  return *this;
}

_ node_t::iterate(int n, iter_f f) {
  node_t* current = this;
  for (int i = 0; i < n; i++) {
    node_t* result = f(*current, n, i);
    if (result) current = result;
  }
  return *this;
}

_ node_t::hide() {
  return hidden(true);
}

_ node_t::show() {
  return hidden(false);
}

_ node_t::hidden(bool x) {
  __.hidden = x;
  return *this;
}

bool node_t::hidden() {
  return __.hidden;
}

_ node_t::parent() {
  __.parent || rmr.die("node.parent: no parent");
  return *__.parent;
};

_ node_t::up() {
  return parent();
};

_ node_t::chain_tick(tick_f f) {
  __.ticks.push_back(f);
  return *this;
}

_ node_t::tick(double now, double dt) {
  for (auto tick : __.ticks)     tick(*this, now, dt);
  for (auto child : __.children) child->tick(now, dt);
  return *this;
}

_ node_t::imprint(const sym_t& name, node_t* blueprint) {
  ::imprint.set(this, name, blueprint);
  return *this;
}

_ node_t::spawn(const sym_t& name) {
  return spawn<node_t>(name);
}

_ node_t::clone(const sym_t& name) {
  return clone<node_t>(name);
}

_ node_t::clone() {
  return clone(name());
}

_ node_t::name(const sym_t& name) {
  __.name = name;
  return *this;
}

const mat4& node_t::transform() const {
  return __.transform;
}

mat4& node_t::transform() {
  return __.transform;
}

const mat4& node_t::matrix() const {
  return __.matrix;
}

mat4& node_t::matrix() {
  return __.matrix;
}

_ node_t::matrix(const mat4& m) {
  __.matrix = m;
  return *this;
}

_ node_t::transform(const mat4& m) {
  __.transform = m;
  return *this;
}

_ node_t::translate  (float x, float y, float z) { transform().translate(x, y, z); return *this; }
_ node_t::translate  (const vec3& v              ) { return translate(v.x(), v.y(), v.z());        }
_ node_t::translate_x(float x                  ) { transform().translate_x(x);     return *this; }
_ node_t::translate_y(float y                  ) { transform().translate_y(y);     return *this; }
_ node_t::translate_z(float z                  ) { transform().translate_z(z);     return *this; }

const sym_t& node_t::name() {
  return __.name;
}

int node_t::child_count() {
  return __.children.size();
}

_ node_t::child(int i) {
  i >= 0 || rmr.die("node.child: negative index");
  i < child_count() || rmr.die("node.child: out of range index");
  return *__.children[i];
}

_ node_t::adopt(node_t& node) {
  node.__.parent == nullptr || rmr.die("node.adopt: can only adopt orphans");
  node.__.parent = this;
  __.children.push_back(&node);
  return *this;
}

_ node_t::orphan() {
  auto& siblings = parent().__.children;
  auto f = siblings.rbegin();
  auto l = siblings.rend();
  auto i = std::find(f, l, this);
  i == l && rmr.die("node.orphan: something went terribly wrong");
  siblings.erase((i+1).base());
  __.parent = nullptr;
  return *this;
}

bool node_t::operator==(const node_t& x) {
  return this == &x;
}

iterator_t node_t::begin() {
  return iterator_t(&*__.children.begin());
}

iterator_t node_t::end() {
  return iterator_t(&*__.children.end());
}
