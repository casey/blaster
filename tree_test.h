#import "tree.h"
#import "rmr.h"

static uint next_id = 0;

struct tree_t {
  bool is_root() { 
    return parent_p == nullptr; 
  }

  tree_t& parent() {
    if (is_root()) rmr.die("tree.parent: root");
    return *parent_p;
  }

  using iterator_t = indirect_iterator_t<tree_t>;

  iterator_t begin() { return children.data() + 0;               }
  iterator_t end()   { return children.data() + children.size(); }

  uint id = next_id++;
  tree_t* parent_p{};
  vector<tree_t*> children{};

  tree_t& spawn() {
    tree_t* child = new tree_t();
    child->parent_p = this;
    children.push_back(child);
    return *child;
  }

  ~tree_t() {
    for (auto child : children) delete child;
  }
};

TEST(tree) {
  tree_t root;

  ASSERT(tree<tree_t>::count_children(root) == 0);

  for (int i = 0; i < 100; i++) {
    root.spawn().spawn();
  }

  ASSERT(tree<tree_t>::count_children(root) == 100);
}
