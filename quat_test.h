#import "quat.h"

TEST(quat) {
  quat q = quat::identity();
  ASSERT(q.magnitude() == 1.0);
}

