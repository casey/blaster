#import "ring.h"

TEST(ring) {
  {
    ring_t<double, 100> _{20};
    ASSERT(rmr.mean(_) == 20);

    for (int i = 0; i < 1000; i++) {
      _.write(20);
      auto m = rmr.mean(_);
      if (m != 20) {
        for (auto x : _) {
          rmr << x;
        }

        rmr << m << i;
        ASSERT(false);
      }
    }
  }

  {
    const ring_t<double, 100> c{2};
    double sum  = rmr.sum(c);
    double mean = rmr.mean(c);
    ASSERT(sum  == 200) << "sum was actually:" << sum;
    ASSERT(mean ==   2) << "mean was actually:" << mean;
  }
}
