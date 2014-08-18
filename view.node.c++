#import "view.node.h"
#import "node.h"
#import "sym.h"
#import "fmt.h"
#import "rmr.h"
#import "vec.h"
#import "sketch.h"

SKETCH { return _.spawn<node_v>(); };

using group_map_t = map<type_index, vector<node_t*>>;

struct node_v::data_t {
  node_t  root  {"root"_sym};
  node_t* scene {&root     };
  node_t* eye   {&root     };

};

node_t& node_v::scene() { return *__.scene; }
node_t& node_v::eye()   { return *__.eye;   } 
node_t& node_v::root()  { return __.root;   }

node_v::node_v() : __(*new data_t())  {
}

node_v::~node_v() {
  delete &__;
}

void traverse(node_t& node, const mat4& parent_transform, group_map_t& groups) {
  if (node.hidden()) return;
  node.matrix(parent_transform * node.transform());
  groups[typeid(node)].push_back(&node);
  for (node_t& child : node) traverse(child, node.matrix(), groups);
}

void node_v::operator()(const draw_e& e) {
  (scene() == eye() && eye() == root()) || rmr.die("root must equal eye and scene");
  group_map_t groups;

  traverse(root(), mat4::identity(), groups);

  for (auto& p : groups) {
    auto&   index = p.first;
    auto&   group = p.second;
    node_t& prime = *group[0];
    rmr.spam("node_c.render: rendering group with % members"_fmt(group.size()));
    prime.render(gl(), frame_t<node_t*>(group));
  }
} 
