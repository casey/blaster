#import "arena.h"

arena_t::arena_t(size_t size) : size(size), space(size), memory(new char[size]) {
    memory || rmr_die("arena: allocation falied");
}

arena_t::~arena_t() { delete[] memory; }

void   arena_t::clear()     { space = size;                }
size_t arena_t::allocated() { return size - space;         }
size_t arena_t::available() { return size - allocated();   }
void*  arena_t::top()       { return memory + allocated(); }

void*  arena_t::helper(size_t alignment, size_t size, size_t count) {
  void*  p         = top();
  size_t requested = size * count;
  std::align(alignment, requested, p, space) || rmr_die("arena.alloc: allocation failed");
  space -= requested;
  return p;
}
