#import "out.h"

struct auto_register_t {
  auto_register_t(void (*function)(), string name, string file, int line);
};

#define UNIQUE_NAME(base) TOKEN_PASTE(base, __COUNTER__)

#define TEST_INNER(name, counter) \
static void TOKEN_PASTE(test_function, counter) (); \
namespace { \
  auto_register_t UNIQUE_NAME(auto_register_t)( \
      &TOKEN_PASTE(test_function, counter), #name, __FILE__, __LINE__); \
} \
static void TOKEN_PASTE(test_function, counter)()

#define TEST(name) TEST_INNER(name, __COUNTER__)

out_t assert_function(const char* expr, bool value, bool fatal, const char* file, int line, const char* macro_name);

#define ASSERT(expr) assert_function(#expr, expr, true,  __FILE__, __LINE__, "ASSERT")
#define EXPECT(expr) assert_function(#expr, expr, false, __FILE__, __LINE__, "EXPECT")
#define FAIL() ASSERT(false)

#define ASSERT_EQ(lhs, rhs)

void run_tests();
