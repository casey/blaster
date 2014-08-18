#import "top.h"
#import "ephemera.h"
#import "fmt.h"
#import "rmr.h"

static ephemera_t<top_t*> begetter;
static u64 next_id = 0;

using _ = top_t&;
using iterator_t = top_t::iterator_t;

struct top_t::data_t {
  population_t                   pop          = {};
  top_t*                         parent       = {};
  vector<std::unique_ptr<top_t>> children     = {};
  string                         name         = {};
  bool                           hidden       = {};
  u64                            id           = next_id++;
};

top_t::top_t() : top_t(begetter.get()) {
}

top_t::top_t(top_t* parent) : __(*new data_t{}) {
  __.parent = parent;
  if (parent) {
    __.parent->__.children.push_back(std::unique_ptr<top_t>(this));
  }
}

top_t::top_t(nothing_t) : top_t(nullptr) {
}

top_t::~top_t() { 
  delete &__;
}

u64 top_t::id() {
  return __.id;
}

_ top_t::clear() {
  __.children.clear();
  return *this;
}

_ top_t::tree() {
  return tree(0);
}

_ top_t::parent() {
  __.parent || rmr.die("top.parent: root node");
  return *__.parent;
}

_ top_t::tree(int indent) {
  cerr << string(indent, ' ');
  if (!name().empty()) cerr << name();
  else        cerr << "id:" << __.id;
  cerr << endl;
  for (auto& child : *this) child.tree(indent + 2);
  return *this;
}

const string& top_t::name() {
  return __.name;
};

_ top_t::name(const string& name) {
  __.name = name;
  rename_e()(*this);
  return *this;
}

_ top_t::imprint() {
  begetter.set(this);
  return *this;
}

_ top_t::emit(const event_t& e) {
  e(*this);
  if (e) __.parent && __.parent->emit(e);
  return *this;
}

_ top_t::broadcast(const event_t& e) {
  e(*this);
  if (e) for (auto& child : *this) child.broadcast(e);
  return *this;
}

top_t::operator bool() const {
  return true;
}

_ top_t::hide() {
  return hidden(true);
}

_ top_t::show() {
  return hidden(false);
}

_ top_t::toggle() {
  __.hidden = !__.hidden;
  return *this;
}

bool top_t::hidden() {
  return __.hidden;
}

iterator_t top_t::begin() {
  return iterator_t(&*__.children.begin());
}

iterator_t top_t::end() {
  return iterator_t(&*__.children.end());;
}

_ top_t::hidden(bool h) {
  if (rmr.rising_edge (__.hidden, h)) hide_e()(*this);
  if (rmr.falling_edge(__.hidden, h)) show_e()(*this);
  __.hidden = h;
  return *this;
}

unique_ptr<top_t> top_t::orphan() {
  auto& siblings = parent().__.children;
  for (auto i = siblings.begin(); i != siblings.end(); i++) {
    if (i->get() == this) {
      unique_ptr<top_t> p{std::move(*i)};
      siblings.erase(i);
      p->__.parent = nullptr;
      return p;
    }
  }

  rmr.die("top.orphan: node not found in siblings");
}

_ top_t::adopt(unique_ptr<top_t> x) {
  adopt(*x.release());
  return *this;
}

_ top_t::adopt(top_t& x) {
  if (x.__.parent) {
    x.orphan().release();
  }

  x.__.parent && rmr.die("adopt: x still has a parent");

  __.children.emplace_back(&x);
  x.__.parent = this;

  return *this;
}

_ top_t::child(size_t index) {
  index < __.children.size() || rmr.die("top.child: index out of bounds: %"_fmt(index));
  return *__.children[index];
}

bool top_t::operator==(const top_t& rhs) const {
  return this == &rhs;
}

bool top_t::operator!=(const top_t& rhs) const  {
  return !(*this == rhs);
}

bool top_t::is_root() {
  return __.parent == nullptr;
}

_ top_t::for_each(fun_t<void(top_t&)> f) {
  f(*this);
  for (auto& child : *this) {
    child.for_each(f);
  }
  return *this;
}

_ top_t::for_ancestors(fun_t<void(top_t&)> f) {
  auto p = __.parent;
  while (p) {
    f(*p);
    p = p->__.parent;
  }
  return *this;
}

_ top_t::for_descendants(fun_t<void(top_t&)> f) {
  for (auto& child : *this) {
    child.for_each(f);
  }
  return *this;
}
