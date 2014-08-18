#import "fmt.h"

TEST(fmt) {
  ASSERT("hi % there"_fmt(1.777) == "hi 1.777 there");
}
