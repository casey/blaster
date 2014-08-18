#import "sym.h"

TEST(sym) {
  sym_t a0("a");
  sym_t a1 = "a"_sym;
  sym_t b0 = "b"_sym;
  sym_t b1("b");
  sym_t g0 = sym_t::gensym();
  sym_t g1 = sym_t::gensym();
  sym_t g2 = sym_t::gensym();
  sym_t g3 = sym_t::gensym();

  ASSERT(a0.str() == a1.str());
  ASSERT(a1.str() != b0.str());

  sym_t empty0;
  sym_t empty1;
  sym_t empty2 = "";

  ASSERT(!empty0);
  ASSERT(empty0 == empty1);
  ASSERT(empty0 != empty2);

  ASSERT(!!a0);
  ASSERT(a0 == a1);
  ASSERT(a0 != b0);
  ASSERT(b0 == b1);
  ASSERT(g0 != g1);
}
