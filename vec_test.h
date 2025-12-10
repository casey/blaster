
#import "vec.h"
#import "rmr.h"
// stuff common to both vectors and matrices
TEST(vec4) {
  // no argument constructor
  {
    vec4 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    _.w(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    ASSERT(_.w() == 1.0);
    new (&_) vec4;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
  }

  // whatever constructor
  {
    float* buffer = new float[4];
    buffer[0] = 7.0;
    new (buffer) vec4(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) vec4(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    vec4 _{  7,  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);
    ASSERT(_.w() == 7);

  }

  // single component constructor
  {
    vec4 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
    ASSERT(_.w() == 100);
  }
  // pointer initializer
  {
    float p[4] = {1};
    vec4 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(vec4().x(3).x() == 3);
  ASSERT(vec4().y(3).y() == 3);
  ASSERT(vec4().z(3).z() == 3);
  ASSERT(vec4().w(3).w() == 3);
  ASSERT(vec4().r(3).r() == 3);
  ASSERT(vec4().g(3).g() == 3);
  ASSERT(vec4().b(3).b() == 3);
  ASSERT(vec4().a(3).a() == 3);
  ASSERT(vec4().s(3).s() == 3);
  ASSERT(vec4().t(3).t() == 3);
  ASSERT(vec4().p(3).p() == 3);
  ASSERT(vec4().q(3).q() == 3);
  // swizzles
  // data pointers
  {
    vec4 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    vec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    vec4 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    vec4 _;
    ASSERT(_.size  () == 4);
  }
  // sum
  {
    vec4 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    vec4 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    vec4 a;
    vec4 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    vec4 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == float(sqrt(2))); // probably close enough

  }

  // normalize

  {
    vec4 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend
  // hash
  // from heading
  // to heading
  // dot
  {
    vec4     a{77};
    vec4     b{88};
    float d = a.dot(b);
    ASSERT(d == 77 * 88 * 4);
  }
  // dot
  // bits
  {
    vec4 _ = vec4::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(dvec4) {
  // no argument constructor
  {
    dvec4 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    _.w(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    ASSERT(_.w() == 1.0);
    new (&_) dvec4;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
  }

  // whatever constructor
  {
    double* buffer = new double[4];
    buffer[0] = 7.0;
    new (buffer) dvec4(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) dvec4(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    dvec4 _{  7,  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);
    ASSERT(_.w() == 7);

  }

  // single component constructor
  {
    dvec4 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
    ASSERT(_.w() == 100);
  }
  // pointer initializer
  {
    double p[4] = {1};
    dvec4 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(dvec4().x(3).x() == 3);
  ASSERT(dvec4().y(3).y() == 3);
  ASSERT(dvec4().z(3).z() == 3);
  ASSERT(dvec4().w(3).w() == 3);
  ASSERT(dvec4().r(3).r() == 3);
  ASSERT(dvec4().g(3).g() == 3);
  ASSERT(dvec4().b(3).b() == 3);
  ASSERT(dvec4().a(3).a() == 3);
  ASSERT(dvec4().s(3).s() == 3);
  ASSERT(dvec4().t(3).t() == 3);
  ASSERT(dvec4().p(3).p() == 3);
  ASSERT(dvec4().q(3).q() == 3);
  // swizzles
  // data pointers
  {
    dvec4 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    dvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    dvec4 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    dvec4 _;
    ASSERT(_.size  () == 4);
  }
  // sum
  {
    dvec4 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    dvec4 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    dvec4 a;
    dvec4 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    dvec4 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == double(sqrt(2))); // probably close enough

  }

  // normalize

  {
    dvec4 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend
  // hash
  // from heading
  // to heading
  // dot
  {
    dvec4     a{77};
    dvec4     b{88};
    double d = a.dot(b);
    ASSERT(d == 77 * 88 * 4);
  }
  // dot
  // bits
  {
    dvec4 _ = dvec4::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(ivec4) {
  // no argument constructor
  {
    ivec4 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    _.w(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    ASSERT(_.w() == 1.0);
    new (&_) ivec4;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
  }

  // whatever constructor
  {
    int* buffer = new int[4];
    buffer[0] = 7.0;
    new (buffer) ivec4(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) ivec4(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    ivec4 _{  7,  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);
    ASSERT(_.w() == 7);

  }

  // single component constructor
  {
    ivec4 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
    ASSERT(_.w() == 100);
  }
  // pointer initializer
  {
    int p[4] = {1};
    ivec4 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(ivec4().x(3).x() == 3);
  ASSERT(ivec4().y(3).y() == 3);
  ASSERT(ivec4().z(3).z() == 3);
  ASSERT(ivec4().w(3).w() == 3);
  ASSERT(ivec4().r(3).r() == 3);
  ASSERT(ivec4().g(3).g() == 3);
  ASSERT(ivec4().b(3).b() == 3);
  ASSERT(ivec4().a(3).a() == 3);
  ASSERT(ivec4().s(3).s() == 3);
  ASSERT(ivec4().t(3).t() == 3);
  ASSERT(ivec4().p(3).p() == 3);
  ASSERT(ivec4().q(3).q() == 3);
  // swizzles
  // data pointers
  {
    ivec4 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    ivec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    ivec4 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    ivec4 _;
    ASSERT(_.size  () == 4);
  }
  // sum
  {
    ivec4 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    ivec4 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    ivec4 a;
    ivec4 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    ivec4 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == int(sqrt(2))); // probably close enough

  }

  // normalize

  {
    ivec4 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend
  // hash
  // from heading
  // to heading
  // dot
  {
    ivec4     a{77};
    ivec4     b{88};
    int d = a.dot(b);
    ASSERT(d == 77 * 88 * 4);
  }
  // dot
  // bits
  {
    ivec4 _ = ivec4::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(uvec4) {
  // no argument constructor
  {
    uvec4 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    _.w(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    ASSERT(_.w() == 1.0);
    new (&_) uvec4;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
  }

  // whatever constructor
  {
    uint* buffer = new uint[4];
    buffer[0] = 7.0;
    new (buffer) uvec4(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) uvec4(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    uvec4 _{  7,  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);
    ASSERT(_.w() == 7);

  }

  // single component constructor
  {
    uvec4 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
    ASSERT(_.w() == 100);
  }
  // pointer initializer
  {
    uint p[4] = {1};
    uvec4 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(uvec4().x(3).x() == 3);
  ASSERT(uvec4().y(3).y() == 3);
  ASSERT(uvec4().z(3).z() == 3);
  ASSERT(uvec4().w(3).w() == 3);
  ASSERT(uvec4().r(3).r() == 3);
  ASSERT(uvec4().g(3).g() == 3);
  ASSERT(uvec4().b(3).b() == 3);
  ASSERT(uvec4().a(3).a() == 3);
  ASSERT(uvec4().s(3).s() == 3);
  ASSERT(uvec4().t(3).t() == 3);
  ASSERT(uvec4().p(3).p() == 3);
  ASSERT(uvec4().q(3).q() == 3);
  // swizzles
  // data pointers
  {
    uvec4 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    uvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec4 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    uvec4 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    uvec4 _;
    ASSERT(_.size  () == 4);
  }
  // sum
  {
    uvec4 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  // equality
  {
    uvec4 a;
    uvec4 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    uvec4 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == uint(sqrt(2))); // probably close enough

  }

  // normalize

  {
    uvec4 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    ASSERT(_.w() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend
  // hash
  // from heading
  // to heading
  // dot
  {
    uvec4     a{77};
    uvec4     b{88};
    uint d = a.dot(b);
    ASSERT(d == 77 * 88 * 4);
  }
  // dot
  // bits
  {
    uvec4 _ = uvec4::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(vec3) {
  // no argument constructor
  {
    vec3 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    new (&_) vec3;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
  }

  // whatever constructor
  {
    float* buffer = new float[3];
    buffer[0] = 7.0;
    new (buffer) vec3(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) vec3(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    vec3 _{  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);

  }

  // single component constructor
  {
    vec3 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
  }
  // pointer initializer
  {
    float p[3] = {1};
    vec3 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(vec3().x(3).x() == 3);
  ASSERT(vec3().y(3).y() == 3);
  ASSERT(vec3().z(3).z() == 3);
  ASSERT(vec3().r(3).r() == 3);
  ASSERT(vec3().g(3).g() == 3);
  ASSERT(vec3().b(3).b() == 3);
  ASSERT(vec3().s(3).s() == 3);
  ASSERT(vec3().t(3).t() == 3);
  ASSERT(vec3().p(3).p() == 3);
  // swizzles
  // data pointers
  {
    vec3 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    vec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    vec3 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    vec3 _;
    ASSERT(_.size  () == 3);
  }
  // sum
  {
    vec3 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    vec3 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    vec3 a;
    vec3 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    vec3 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == float(sqrt(2))); // probably close enough

  }

  // normalize

  {
    vec3 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    vec3     a{77};
    vec3     b{88};
    float d = a.dot(b);
    ASSERT(d == 77 * 88 * 3);
  }
  // dot
  {
    // lol testing
  }
  // bits
  {
    vec3 _ = vec3::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(dvec3) {
  // no argument constructor
  {
    dvec3 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    new (&_) dvec3;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
  }

  // whatever constructor
  {
    double* buffer = new double[3];
    buffer[0] = 7.0;
    new (buffer) dvec3(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) dvec3(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    dvec3 _{  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);

  }

  // single component constructor
  {
    dvec3 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
  }
  // pointer initializer
  {
    double p[3] = {1};
    dvec3 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(dvec3().x(3).x() == 3);
  ASSERT(dvec3().y(3).y() == 3);
  ASSERT(dvec3().z(3).z() == 3);
  ASSERT(dvec3().r(3).r() == 3);
  ASSERT(dvec3().g(3).g() == 3);
  ASSERT(dvec3().b(3).b() == 3);
  ASSERT(dvec3().s(3).s() == 3);
  ASSERT(dvec3().t(3).t() == 3);
  ASSERT(dvec3().p(3).p() == 3);
  // swizzles
  // data pointers
  {
    dvec3 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    dvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    dvec3 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    dvec3 _;
    ASSERT(_.size  () == 3);
  }
  // sum
  {
    dvec3 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    dvec3 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    dvec3 a;
    dvec3 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    dvec3 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == double(sqrt(2))); // probably close enough

  }

  // normalize

  {
    dvec3 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    dvec3     a{77};
    dvec3     b{88};
    double d = a.dot(b);
    ASSERT(d == 77 * 88 * 3);
  }
  // dot
  {
    // lol testing
  }
  // bits
  {
    dvec3 _ = dvec3::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(ivec3) {
  // no argument constructor
  {
    ivec3 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    new (&_) ivec3;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
  }

  // whatever constructor
  {
    int* buffer = new int[3];
    buffer[0] = 7.0;
    new (buffer) ivec3(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) ivec3(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    ivec3 _{  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);

  }

  // single component constructor
  {
    ivec3 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
  }
  // pointer initializer
  {
    int p[3] = {1};
    ivec3 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(ivec3().x(3).x() == 3);
  ASSERT(ivec3().y(3).y() == 3);
  ASSERT(ivec3().z(3).z() == 3);
  ASSERT(ivec3().r(3).r() == 3);
  ASSERT(ivec3().g(3).g() == 3);
  ASSERT(ivec3().b(3).b() == 3);
  ASSERT(ivec3().s(3).s() == 3);
  ASSERT(ivec3().t(3).t() == 3);
  ASSERT(ivec3().p(3).p() == 3);
  // swizzles
  // data pointers
  {
    ivec3 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    ivec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    ivec3 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    ivec3 _;
    ASSERT(_.size  () == 3);
  }
  // sum
  {
    ivec3 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    ivec3 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    ivec3 a;
    ivec3 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    ivec3 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == int(sqrt(2))); // probably close enough

  }

  // normalize

  {
    ivec3 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    ivec3     a{77};
    ivec3     b{88};
    int d = a.dot(b);
    ASSERT(d == 77 * 88 * 3);
  }
  // dot
  {
    // lol testing
  }
  // bits
  {
    ivec3 _ = ivec3::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(uvec3) {
  // no argument constructor
  {
    uvec3 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x(1.0);
    _.y(1.0);
    _.z(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    ASSERT(_.z() == 1.0);
    new (&_) uvec3;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
  }

  // whatever constructor
  {
    uint* buffer = new uint[3];
    buffer[0] = 7.0;
    new (buffer) uvec3(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) uvec3(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    uvec3 _{  7,  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);
    ASSERT(_.z() == 7);

  }

  // single component constructor
  {
    uvec3 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
    ASSERT(_.z() == 100);
  }
  // pointer initializer
  {
    uint p[3] = {1};
    uvec3 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(uvec3().x(3).x() == 3);
  ASSERT(uvec3().y(3).y() == 3);
  ASSERT(uvec3().z(3).z() == 3);
  ASSERT(uvec3().r(3).r() == 3);
  ASSERT(uvec3().g(3).g() == 3);
  ASSERT(uvec3().b(3).b() == 3);
  ASSERT(uvec3().s(3).s() == 3);
  ASSERT(uvec3().t(3).t() == 3);
  ASSERT(uvec3().p(3).p() == 3);
  // swizzles
  // data pointers
  {
    uvec3 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    uvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec3 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    uvec3 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    uvec3 _;
    ASSERT(_.size  () == 3);
  }
  // sum
  {
    uvec3 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  // equality
  {
    uvec3 a;
    uvec3 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    uvec3 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == uint(sqrt(2))); // probably close enough

  }

  // normalize

  {
    uvec3 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    ASSERT(_.z() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    uvec3     a{77};
    uvec3     b{88};
    uint d = a.dot(b);
    ASSERT(d == 77 * 88 * 3);
  }
  // dot
  {
    // lol testing
  }
  // bits
  {
    uvec3 _ = uvec3::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(vec2) {
  // no argument constructor
  {
    vec2 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    _.x(1.0);
    _.y(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    new (&_) vec2;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
  }

  // whatever constructor
  {
    float* buffer = new float[2];
    buffer[0] = 7.0;
    new (buffer) vec2(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) vec2(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    vec2 _{  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);

  }

  // single component constructor
  {
    vec2 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
  }
  // pointer initializer
  {
    float p[2] = {1};
    vec2 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(vec2().x(3).x() == 3);
  ASSERT(vec2().y(3).y() == 3);
  ASSERT(vec2().r(3).r() == 3);
  ASSERT(vec2().g(3).g() == 3);
  ASSERT(vec2().s(3).s() == 3);
  ASSERT(vec2().t(3).t() == 3);
  // swizzles
  // data pointers
  {
    vec2 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    vec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    vec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    vec2 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    vec2 _;
    ASSERT(_.size  () == 2);
  }
  // sum
  {
    vec2 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    vec2 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    vec2 a;
    vec2 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    vec2 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == float(sqrt(2))); // probably close enough

  }

  // normalize

  {
    vec2 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    vec2     a{77};
    vec2     b{88};
    float d = a.dot(b);
    ASSERT(d == 77 * 88 * 2);
  }
  // dot
  // bits
  {
    vec2 _ = vec2::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(dvec2) {
  // no argument constructor
  {
    dvec2 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    _.x(1.0);
    _.y(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    new (&_) dvec2;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
  }

  // whatever constructor
  {
    double* buffer = new double[2];
    buffer[0] = 7.0;
    new (buffer) dvec2(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) dvec2(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    dvec2 _{  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);

  }

  // single component constructor
  {
    dvec2 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
  }
  // pointer initializer
  {
    double p[2] = {1};
    dvec2 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(dvec2().x(3).x() == 3);
  ASSERT(dvec2().y(3).y() == 3);
  ASSERT(dvec2().r(3).r() == 3);
  ASSERT(dvec2().g(3).g() == 3);
  ASSERT(dvec2().s(3).s() == 3);
  ASSERT(dvec2().t(3).t() == 3);
  // swizzles
  // data pointers
  {
    dvec2 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    dvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    dvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    dvec2 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    dvec2 _;
    ASSERT(_.size  () == 2);
  }
  // sum
  {
    dvec2 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    dvec2 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    dvec2 a;
    dvec2 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    dvec2 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == double(sqrt(2))); // probably close enough

  }

  // normalize

  {
    dvec2 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    dvec2     a{77};
    dvec2     b{88};
    double d = a.dot(b);
    ASSERT(d == 77 * 88 * 2);
  }
  // dot
  // bits
  {
    dvec2 _ = dvec2::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(ivec2) {
  // no argument constructor
  {
    ivec2 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    _.x(1.0);
    _.y(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    new (&_) ivec2;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
  }

  // whatever constructor
  {
    int* buffer = new int[2];
    buffer[0] = 7.0;
    new (buffer) ivec2(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) ivec2(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    ivec2 _{  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);

  }

  // single component constructor
  {
    ivec2 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
  }
  // pointer initializer
  {
    int p[2] = {1};
    ivec2 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(ivec2().x(3).x() == 3);
  ASSERT(ivec2().y(3).y() == 3);
  ASSERT(ivec2().r(3).r() == 3);
  ASSERT(ivec2().g(3).g() == 3);
  ASSERT(ivec2().s(3).s() == 3);
  ASSERT(ivec2().t(3).t() == 3);
  // swizzles
  // data pointers
  {
    ivec2 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    ivec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    ivec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    ivec2 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    ivec2 _;
    ASSERT(_.size  () == 2);
  }
  // sum
  {
    ivec2 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  {
    ivec2 _(7);
    _ = -_;
    ASSERT(_.x() == -7);
  }
  // equality
  {
    ivec2 a;
    ivec2 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    ivec2 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == int(sqrt(2))); // probably close enough

  }

  // normalize

  {
    ivec2 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    ivec2     a{77};
    ivec2     b{88};
    int d = a.dot(b);
    ASSERT(d == 77 * 88 * 2);
  }
  // dot
  // bits
  {
    ivec2 _ = ivec2::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
TEST(uvec2) {
  // no argument constructor
  {
    uvec2 _;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
    _.x(1.0);
    _.y(1.0);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 1.0);
    new (&_) uvec2;
    ASSERT(_.x() == 0.0);
    ASSERT(_.y() == 0.0);
  }

  // whatever constructor
  {
    uint* buffer = new uint[2];
    buffer[0] = 7.0;
    new (buffer) uvec2(rmr.whatever());
    ASSERT(buffer[0] == 7.0);
    new (buffer) uvec2(5);
    ASSERT(buffer[0] == 5.0);

  }

  // scalar component constructor
  {
    uvec2 _{  7,  7   };
    ASSERT(_.x() == 7);
    ASSERT(_.y() == 7);

  }

  // single component constructor
  {
    uvec2 _{ 100 };
    ASSERT(_.x() == 100);
    ASSERT(_.y() == 100);
  }
  // pointer initializer
  {
    uint p[2] = {1};
    uvec2 v(p);
    ASSERT(v.x() == 1);
    ASSERT(v.y() == 0);
  }
  // component accessors
  ASSERT(uvec2().x(3).x() == 3);
  ASSERT(uvec2().y(3).y() == 3);
  ASSERT(uvec2().r(3).r() == 3);
  ASSERT(uvec2().g(3).g() == 3);
  ASSERT(uvec2().s(3).s() == 3);
  ASSERT(uvec2().t(3).t() == 3);
  // swizzles
  // data pointers
  {
    uvec2 _;
    _.data()[0] = 2;
    ASSERT(_.x() == 2);
  }
  // operators

  {
    uvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  {
    uvec2 _;
    _ += 2;
    ASSERT(_.x() == 2);
    _ *= 3;
    ASSERT(_.y() == 6);

  }

  // unary +

  {
    uvec2 _(7);
    _ = +_;
    ASSERT(_.x() == 7);

  }

  // const subscript
  // mutable subscript
  // iteration
  // length and size
  {
    uvec2 _;
    ASSERT(_.size  () == 2);
  }
  // sum
  {
    uvec2 _(111);
    ASSERT(_.sum() == 111 * _.size());
  }
  // unary -
  // equality
  {
    uvec2 a;
    uvec2 b;
    ASSERT(a == b);
    ASSERT(!(a != b));
    a[0]++;
    ASSERT(!(a == b));
    ASSERT(a != b);

  }

  {
    uvec2 _;
    ASSERT(_.magnitude() == 0);
    _.x(1);
    ASSERT(_.magnitude() == 1);
    _.y(1);
    ASSERT(_.magnitude() == uint(sqrt(2))); // probably close enough

  }

  // normalize

  {
    uvec2 _;
    _.x() = 10;
    _.normalize();
    ASSERT(_.x() == 1);
    ASSERT(_.y() == 0.0);
    _.x() = 0.0;
    _.y() = 20;
    _.normalize();
    ASSERT(_.y() == 1.0);

  }

  // extend

  // hash
  // from heading
  // to heading
  // dot
  {
    uvec2     a{77};
    uvec2     b{88};
    uint d = a.dot(b);
    ASSERT(d == 77 * 88 * 2);
  }
  // dot
  // bits
  {
    uvec2 _ = uvec2::bits(1);
    ASSERT(_.x() == 1.0);
    ASSERT(_.y() == 0.0);
  }
}
// matrices
TEST(dmat4) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    dmat4 a;
    dmat4 b;
    a * b;
  }
  {
    dmat4 a;
    dmat4 b;
    a * b;
  }
  // translation
  // rotate
}
TEST(mat4) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    mat4 a;
    mat4 b;
    a * b;
  }
  {
    mat4 a;
    mat4 b;
    a * b;
  }
  // translation
  // rotate
}
TEST(dmat3) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    dmat3 a;
    dmat3 b;
    a * b;
  }
  {
    dmat3 a;
    dmat3 b;
    a * b;
  }
  // translation
  // rotate
}
TEST(mat3) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    mat3 a;
    mat3 b;
    a * b;
  }
  {
    mat3 a;
    mat3 b;
    a * b;
  }
  // translation
  // rotate
}
TEST(dmat2) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    dmat2 a;
    dmat2 b;
    a * b;
  }
  {
    dmat2 a;
    dmat2 b;
    a * b;
  }
  // translation
  // rotate
}
TEST(mat2) {
  // no argument constructor
  // whatever constructor
  // component constructor
  // data pointers
  // floats
  {
    mat2 a;
    mat2 b;
    a * b;
  }
  {
    mat2 a;
    mat2 b;
    a * b;
  }
  // translation
  // rotate
}

