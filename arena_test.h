#import "arena.h"

TEST(arena) {
  struct foo_t {
    char string[4] = "foo";
  };

  struct bar_t {
    char string[7] = "barbar";
  };

  struct hello_t {
    hello_t()  { n = alive()++;         }
    ~hello_t() { alive()--;     n = -1; }
    int n;

    static int& alive() { static int x = 0; return x; }
  };

  arena_t arena(rmr.mb());

  int count = 10;
  auto foos = arena.alloc<foo_t>(count);
  arena.alloc<double>(1000);
  ASSERT(arena.allocated() >= sizeof(double) * 1000 + sizeof(foo_t) * count);
  for (int i = 0; i < count; i++) ASSERT(string(foos[i].string) == "foo");
  arena.clear();

  ASSERT(arena.allocated() == 0);

  auto bars = arena.alloc<bar_t>(count);
  arena.alloc<char>(2000);
  ASSERT(arena.allocated() >= sizeof(char) * 2000 + sizeof(bar_t) * count);
  for (int i = 0; i < 10; i++) ASSERT(string(bars[i].string) == "barbar");
  arena.clear();

  ASSERT(arena.allocated() == 0);

  hello_t* begin;
  hello_t* end;

  {
    auto alloc = arena.scoped_alloc<hello_t>(10);
    begin = alloc.begin();
    end   = alloc.end();
    ASSERT(hello_t::alive() == 10);
  }

  ASSERT(hello_t::alive() == 0);
  ASSERT(arena.allocated() == 0);

  while(begin != end) {
    hello_t& h = *begin;
    ASSERT(h.n == -1);
    begin++;
  }

  {
    auto alloc = arena.scoped_alloc<string>(5, "string");
    for (string& s : alloc) {
      ASSERT(s == "string");
    }
  }

  ASSERT(arena.allocated() == 0);
}
