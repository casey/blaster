
#import "vec.h"
#import "rmr.h"
// stuff common to both vectors and matrices
// static assertions
static_assert(sizeof(vec4) == sizeof(decltype(vec4()[0])) * 4, "vec4: unexpected size"     );
static_assert(!std::is_polymorphic<vec4>::value,                    "vec4: non-polymorphic"     );
static_assert(std::is_standard_layout<vec4>::value,                 "vec4: non-standard layout" );
static_assert(std::is_literal_type<vec4>::value,                    "vec4: non-literal"         );
static_assert(alignof(vec4) == alignof(float),                       "vec4: unexpected alignment");
// static assertions
static_assert(sizeof(mat4) == sizeof(decltype(mat4()[0])) * 4, "mat4: unexpected size"     );
static_assert(!std::is_polymorphic<mat4>::value,                    "mat4: non-polymorphic"     );
static_assert(std::is_standard_layout<mat4>::value,                 "mat4: non-standard layout" );
static_assert(std::is_literal_type<mat4>::value,                    "mat4: non-literal"         );
static_assert(alignof(mat4) == alignof(float),                       "mat4: unexpected alignment");
// static assertions
static_assert(sizeof(dvec4) == sizeof(decltype(dvec4()[0])) * 4, "dvec4: unexpected size"     );
static_assert(!std::is_polymorphic<dvec4>::value,                    "dvec4: non-polymorphic"     );
static_assert(std::is_standard_layout<dvec4>::value,                 "dvec4: non-standard layout" );
static_assert(std::is_literal_type<dvec4>::value,                    "dvec4: non-literal"         );
static_assert(alignof(dvec4) == alignof(double),                       "dvec4: unexpected alignment");
// static assertions
static_assert(sizeof(dmat4) == sizeof(decltype(dmat4()[0])) * 4, "dmat4: unexpected size"     );
static_assert(!std::is_polymorphic<dmat4>::value,                    "dmat4: non-polymorphic"     );
static_assert(std::is_standard_layout<dmat4>::value,                 "dmat4: non-standard layout" );
static_assert(std::is_literal_type<dmat4>::value,                    "dmat4: non-literal"         );
static_assert(alignof(dmat4) == alignof(double),                       "dmat4: unexpected alignment");
// static assertions
static_assert(sizeof(ivec4) == sizeof(decltype(ivec4()[0])) * 4, "ivec4: unexpected size"     );
static_assert(!std::is_polymorphic<ivec4>::value,                    "ivec4: non-polymorphic"     );
static_assert(std::is_standard_layout<ivec4>::value,                 "ivec4: non-standard layout" );
static_assert(std::is_literal_type<ivec4>::value,                    "ivec4: non-literal"         );
static_assert(alignof(ivec4) == alignof(int),                       "ivec4: unexpected alignment");
// static assertions
static_assert(sizeof(uvec4) == sizeof(decltype(uvec4()[0])) * 4, "uvec4: unexpected size"     );
static_assert(!std::is_polymorphic<uvec4>::value,                    "uvec4: non-polymorphic"     );
static_assert(std::is_standard_layout<uvec4>::value,                 "uvec4: non-standard layout" );
static_assert(std::is_literal_type<uvec4>::value,                    "uvec4: non-literal"         );
static_assert(alignof(uvec4) == alignof(uint),                       "uvec4: unexpected alignment");
// static assertions
static_assert(sizeof(vec3) == sizeof(decltype(vec3()[0])) * 3, "vec3: unexpected size"     );
static_assert(!std::is_polymorphic<vec3>::value,                    "vec3: non-polymorphic"     );
static_assert(std::is_standard_layout<vec3>::value,                 "vec3: non-standard layout" );
static_assert(std::is_literal_type<vec3>::value,                    "vec3: non-literal"         );
static_assert(alignof(vec3) == alignof(float),                       "vec3: unexpected alignment");
// static assertions
static_assert(sizeof(mat3) == sizeof(decltype(mat3()[0])) * 3, "mat3: unexpected size"     );
static_assert(!std::is_polymorphic<mat3>::value,                    "mat3: non-polymorphic"     );
static_assert(std::is_standard_layout<mat3>::value,                 "mat3: non-standard layout" );
static_assert(std::is_literal_type<mat3>::value,                    "mat3: non-literal"         );
static_assert(alignof(mat3) == alignof(float),                       "mat3: unexpected alignment");
// static assertions
static_assert(sizeof(dvec3) == sizeof(decltype(dvec3()[0])) * 3, "dvec3: unexpected size"     );
static_assert(!std::is_polymorphic<dvec3>::value,                    "dvec3: non-polymorphic"     );
static_assert(std::is_standard_layout<dvec3>::value,                 "dvec3: non-standard layout" );
static_assert(std::is_literal_type<dvec3>::value,                    "dvec3: non-literal"         );
static_assert(alignof(dvec3) == alignof(double),                       "dvec3: unexpected alignment");
// static assertions
static_assert(sizeof(dmat3) == sizeof(decltype(dmat3()[0])) * 3, "dmat3: unexpected size"     );
static_assert(!std::is_polymorphic<dmat3>::value,                    "dmat3: non-polymorphic"     );
static_assert(std::is_standard_layout<dmat3>::value,                 "dmat3: non-standard layout" );
static_assert(std::is_literal_type<dmat3>::value,                    "dmat3: non-literal"         );
static_assert(alignof(dmat3) == alignof(double),                       "dmat3: unexpected alignment");
// static assertions
static_assert(sizeof(ivec3) == sizeof(decltype(ivec3()[0])) * 3, "ivec3: unexpected size"     );
static_assert(!std::is_polymorphic<ivec3>::value,                    "ivec3: non-polymorphic"     );
static_assert(std::is_standard_layout<ivec3>::value,                 "ivec3: non-standard layout" );
static_assert(std::is_literal_type<ivec3>::value,                    "ivec3: non-literal"         );
static_assert(alignof(ivec3) == alignof(int),                       "ivec3: unexpected alignment");
// static assertions
static_assert(sizeof(uvec3) == sizeof(decltype(uvec3()[0])) * 3, "uvec3: unexpected size"     );
static_assert(!std::is_polymorphic<uvec3>::value,                    "uvec3: non-polymorphic"     );
static_assert(std::is_standard_layout<uvec3>::value,                 "uvec3: non-standard layout" );
static_assert(std::is_literal_type<uvec3>::value,                    "uvec3: non-literal"         );
static_assert(alignof(uvec3) == alignof(uint),                       "uvec3: unexpected alignment");
// static assertions
static_assert(sizeof(vec2) == sizeof(decltype(vec2()[0])) * 2, "vec2: unexpected size"     );
static_assert(!std::is_polymorphic<vec2>::value,                    "vec2: non-polymorphic"     );
static_assert(std::is_standard_layout<vec2>::value,                 "vec2: non-standard layout" );
static_assert(std::is_literal_type<vec2>::value,                    "vec2: non-literal"         );
static_assert(alignof(vec2) == alignof(float),                       "vec2: unexpected alignment");
// static assertions
static_assert(sizeof(mat2) == sizeof(decltype(mat2()[0])) * 2, "mat2: unexpected size"     );
static_assert(!std::is_polymorphic<mat2>::value,                    "mat2: non-polymorphic"     );
static_assert(std::is_standard_layout<mat2>::value,                 "mat2: non-standard layout" );
static_assert(std::is_literal_type<mat2>::value,                    "mat2: non-literal"         );
static_assert(alignof(mat2) == alignof(float),                       "mat2: unexpected alignment");
// static assertions
static_assert(sizeof(dvec2) == sizeof(decltype(dvec2()[0])) * 2, "dvec2: unexpected size"     );
static_assert(!std::is_polymorphic<dvec2>::value,                    "dvec2: non-polymorphic"     );
static_assert(std::is_standard_layout<dvec2>::value,                 "dvec2: non-standard layout" );
static_assert(std::is_literal_type<dvec2>::value,                    "dvec2: non-literal"         );
static_assert(alignof(dvec2) == alignof(double),                       "dvec2: unexpected alignment");
// static assertions
static_assert(sizeof(dmat2) == sizeof(decltype(dmat2()[0])) * 2, "dmat2: unexpected size"     );
static_assert(!std::is_polymorphic<dmat2>::value,                    "dmat2: non-polymorphic"     );
static_assert(std::is_standard_layout<dmat2>::value,                 "dmat2: non-standard layout" );
static_assert(std::is_literal_type<dmat2>::value,                    "dmat2: non-literal"         );
static_assert(alignof(dmat2) == alignof(double),                       "dmat2: unexpected alignment");
// static assertions
static_assert(sizeof(ivec2) == sizeof(decltype(ivec2()[0])) * 2, "ivec2: unexpected size"     );
static_assert(!std::is_polymorphic<ivec2>::value,                    "ivec2: non-polymorphic"     );
static_assert(std::is_standard_layout<ivec2>::value,                 "ivec2: non-standard layout" );
static_assert(std::is_literal_type<ivec2>::value,                    "ivec2: non-literal"         );
static_assert(alignof(ivec2) == alignof(int),                       "ivec2: unexpected alignment");
// static assertions
static_assert(sizeof(uvec2) == sizeof(decltype(uvec2()[0])) * 2, "uvec2: unexpected size"     );
static_assert(!std::is_polymorphic<uvec2>::value,                    "uvec2: non-polymorphic"     );
static_assert(std::is_standard_layout<uvec2>::value,                 "uvec2: non-standard layout" );
static_assert(std::is_literal_type<uvec2>::value,                    "uvec2: non-literal"         );
static_assert(alignof(uvec2) == alignof(uint),                       "uvec2: unexpected alignment");
// no argument constructor
// whatever constructor
vec4:: vec4(whatever_t w)   { } // scalar component constructor
vec4:: vec4(
  float x,
  float y,
  float z,
  float w
)   : __{ x, y, z, w } {
} // single component constructor
vec4:: vec4(float s)   : __{ s, s, s, s } { } // pointer initializer
vec4:: vec4(float (&p)[4])   : __{
    p[0],   p[1],   p[2],   p[3]  } { }    // component accessors
float  vec4:: x(   ) const   {
  return __[0];             // swizzles
}
float& vec4:: x(   )         {
  return __[0];
}
vec4& vec4:: x(float s)         {
  __[0] = s;
  return *this;
}
float  vec4:: y(   ) const   {
  return __[1];
}
float& vec4:: y(   )         {
  return __[1];
}
vec4& vec4:: y(float s)         {
  __[1] = s;
  return *this;
}
float  vec4:: z(   ) const   {
  return __[2];
}
float& vec4:: z(   )         {
  return __[2];
}
vec4& vec4:: z(float s)         {
  __[2] = s;
  return *this;
}
float  vec4:: w(   ) const   {
  return __[3];
}
float& vec4:: w(   )         {
  return __[3];
}
vec4& vec4:: w(float s)         {
  __[3] = s;
  return *this;
}
float  vec4:: r(   ) const   {
  return __[0];
}
float& vec4:: r(   )         {
  return __[0];
}
vec4& vec4:: r(float s)         {
  __[0] = s;
  return *this;
}
float  vec4:: g(   ) const   {
  return __[1];
}
float& vec4:: g(   )         {
  return __[1];
}
vec4& vec4:: g(float s)         {
  __[1] = s;
  return *this;
}
float  vec4:: b(   ) const   {
  return __[2];
}
float& vec4:: b(   )         {
  return __[2];
}
vec4& vec4:: b(float s)         {
  __[2] = s;
  return *this;
}
float  vec4:: a(   ) const   {
  return __[3];
}
float& vec4:: a(   )         {
  return __[3];
}
vec4& vec4:: a(float s)         {
  __[3] = s;
  return *this;
}
float  vec4:: s(   ) const   {
  return __[0];
}
float& vec4:: s(   )         {
  return __[0];
}
vec4& vec4:: s(float s)         {
  __[0] = s;
  return *this;
}
float  vec4:: t(   ) const   {
  return __[1];
}
float& vec4:: t(   )         {
  return __[1];
}
vec4& vec4:: t(float s)         {
  __[1] = s;
  return *this;
}
float  vec4:: p(   ) const   {
  return __[2];
}
float& vec4:: p(   )         {
  return __[2];
}
vec4& vec4:: p(float s)         {
  __[2] = s;
  return *this;
}
float  vec4:: q(   ) const   {
  return __[3];
}
float& vec4:: q(   )         {
  return __[3];
}
vec4& vec4:: q(float s)         {
  __[3] = s;
  return *this;
}
// data pointers
float* vec4:: data()         {
  return __;  // operators
}
const float* vec4:: data() const   {
  return __;
}
vec4 vec4::operator+(float s) const {
  return vec4(
           x() + s,
           y() + s,
           z() + s,
           w() + s
         );
}

vec4 vec4::operator+(const vec4& _) const {
  return vec4(
           x() + _.x(),
           y() + _.y(),
           z() + _.z(),
           w() + _.w()
         );
}

vec4& vec4::operator+=(float s) {
  return *this = *this + s;
}

vec4& vec4::operator+=(const vec4 v) {
  return *this = *this + v;
}

vec4 vec4::operator-(float s) const {
  return vec4(
           x() - s,
           y() - s,
           z() - s,
           w() - s
         );
}

vec4 vec4::operator-(const vec4& _) const {
  return vec4(
           x() - _.x(),
           y() - _.y(),
           z() - _.z(),
           w() - _.w()
         );
}

vec4& vec4::operator-=(float s) {
  return *this = *this - s;
}

vec4& vec4::operator-=(const vec4 v) {
  return *this = *this - v;
}

vec4 vec4::operator*(float s) const {
  return vec4(
           x() * s,
           y() * s,
           z() * s,
           w() * s
         );
}

vec4 vec4::operator*(const vec4& _) const {
  return vec4(
           x() * _.x(),
           y() * _.y(),
           z() * _.z(),
           w() * _.w()
         );
}

vec4& vec4::operator*=(float s) {
  return *this = *this * s;
}

vec4& vec4::operator*=(const vec4 v) {
  return *this = *this * v;
}

vec4 vec4::operator/(float s) const {
  return vec4(
           x() / s,
           y() / s,
           z() / s,
           w() / s
         );
}

vec4 vec4::operator/(const vec4& _) const {
  return vec4(
           x() / _.x(),
           y() / _.y(),
           z() / _.z(),
           w() / _.w()
         );
}

vec4& vec4::operator/=(float s) {
  return *this = *this / s;
}

vec4& vec4::operator/=(const vec4 v) {
  return *this = *this / v;
}

// unary +
vec4 vec4::operator+() const {
  return *this;
}

// const subscript
float vec4:: operator[](int i) const   {
  i < 0 && rmr.die("vec4.operator[]: negative index");
  i >= 4 && rmr.die("vec4.operator[]: index too large");
  return __[i];
} // mutable subscript
float& vec4:: operator[](int i)   {
  i < 0 && rmr.die("vec4.operator[]: negative index");
  i >= 4 && rmr.die("vec4.operator[]: index too large");
  return __[i];
} // iteration
const float* vec4:: begin() const   {
  return data()         ;  // length and size
}
float* vec4:: begin()         {
  return data()         ;
}
const float* vec4:: end  () const   {
  return data() + 4;
}
float* vec4:: end  ()         {
  return data() + 4;
}
size_t vec4:: size() const   {
  return 4;  // sum
}
float vec4:: sum() const   {
  return  x() +  y() +  z() +  w()  ;
} // unary -
vec4 vec4:: operator-() const   {
  return *this * -1.0;
} // equality
bool vec4:: operator==(const vec4& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  if (w() != v.w()) return false;
  return true;
}
bool vec4:: operator!=(const vec4& v) const   {
  return !(*this == v);
}
vec4 vec4::random() {
  return random(0, 1);
}

vec4 vec4::random(float max) {
  return random(0, max);
}

vec4 vec4::random(float min, float max) {
  return vec4( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

float vec4::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() + w() * w() );
}

// normalize
vec4& vec4::normalize() {
  float l = magnitude();
  l > 0 || rmr.die("vec4.normalize: zero magnitude");
  return *this /= l;
}

// extend
// hash
vec4 vec4:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 4;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    float((h >> bits * 0 & mask) / float(mask)),
    float((h >> bits * 1 & mask) / float(mask)),
    float((h >> bits * 2 & mask) / float(mask)),
    float((h >> bits * 3 & mask) / float(mask))
  };

} // from heading
// to heading
// dot
float vec4:: dot(const vec4& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z() +  w() * _.w()  ;
} // dot
// bits
vec4 vec4:: bits(int x)   {
  return vec4(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1,
           (x >> 3) & 1
         );
}
ostream& operator<<(ostream& os, const vec4& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z() << " "
         << v.w()
         << ")";
}
// no argument constructor
// whatever constructor
dvec4:: dvec4(whatever_t w)   { } // scalar component constructor
dvec4:: dvec4(
  double x,
  double y,
  double z,
  double w
)   : __{ x, y, z, w } {
} // single component constructor
dvec4:: dvec4(double s)   : __{ s, s, s, s } { } // pointer initializer
dvec4:: dvec4(double (&p)[4])   : __{
    p[0],   p[1],   p[2],   p[3]  } { }    // component accessors
double  dvec4:: x(   ) const   {
  return __[0];             // swizzles
}
double& dvec4:: x(   )         {
  return __[0];
}
dvec4& dvec4:: x(double s)         {
  __[0] = s;
  return *this;
}
double  dvec4:: y(   ) const   {
  return __[1];
}
double& dvec4:: y(   )         {
  return __[1];
}
dvec4& dvec4:: y(double s)         {
  __[1] = s;
  return *this;
}
double  dvec4:: z(   ) const   {
  return __[2];
}
double& dvec4:: z(   )         {
  return __[2];
}
dvec4& dvec4:: z(double s)         {
  __[2] = s;
  return *this;
}
double  dvec4:: w(   ) const   {
  return __[3];
}
double& dvec4:: w(   )         {
  return __[3];
}
dvec4& dvec4:: w(double s)         {
  __[3] = s;
  return *this;
}
double  dvec4:: r(   ) const   {
  return __[0];
}
double& dvec4:: r(   )         {
  return __[0];
}
dvec4& dvec4:: r(double s)         {
  __[0] = s;
  return *this;
}
double  dvec4:: g(   ) const   {
  return __[1];
}
double& dvec4:: g(   )         {
  return __[1];
}
dvec4& dvec4:: g(double s)         {
  __[1] = s;
  return *this;
}
double  dvec4:: b(   ) const   {
  return __[2];
}
double& dvec4:: b(   )         {
  return __[2];
}
dvec4& dvec4:: b(double s)         {
  __[2] = s;
  return *this;
}
double  dvec4:: a(   ) const   {
  return __[3];
}
double& dvec4:: a(   )         {
  return __[3];
}
dvec4& dvec4:: a(double s)         {
  __[3] = s;
  return *this;
}
double  dvec4:: s(   ) const   {
  return __[0];
}
double& dvec4:: s(   )         {
  return __[0];
}
dvec4& dvec4:: s(double s)         {
  __[0] = s;
  return *this;
}
double  dvec4:: t(   ) const   {
  return __[1];
}
double& dvec4:: t(   )         {
  return __[1];
}
dvec4& dvec4:: t(double s)         {
  __[1] = s;
  return *this;
}
double  dvec4:: p(   ) const   {
  return __[2];
}
double& dvec4:: p(   )         {
  return __[2];
}
dvec4& dvec4:: p(double s)         {
  __[2] = s;
  return *this;
}
double  dvec4:: q(   ) const   {
  return __[3];
}
double& dvec4:: q(   )         {
  return __[3];
}
dvec4& dvec4:: q(double s)         {
  __[3] = s;
  return *this;
}
// data pointers
double* dvec4:: data()         {
  return __;  // operators
}
const double* dvec4:: data() const   {
  return __;
}
dvec4 dvec4::operator+(double s) const {
  return dvec4(
           x() + s,
           y() + s,
           z() + s,
           w() + s
         );
}

dvec4 dvec4::operator+(const dvec4& _) const {
  return dvec4(
           x() + _.x(),
           y() + _.y(),
           z() + _.z(),
           w() + _.w()
         );
}

dvec4& dvec4::operator+=(double s) {
  return *this = *this + s;
}

dvec4& dvec4::operator+=(const dvec4 v) {
  return *this = *this + v;
}

dvec4 dvec4::operator-(double s) const {
  return dvec4(
           x() - s,
           y() - s,
           z() - s,
           w() - s
         );
}

dvec4 dvec4::operator-(const dvec4& _) const {
  return dvec4(
           x() - _.x(),
           y() - _.y(),
           z() - _.z(),
           w() - _.w()
         );
}

dvec4& dvec4::operator-=(double s) {
  return *this = *this - s;
}

dvec4& dvec4::operator-=(const dvec4 v) {
  return *this = *this - v;
}

dvec4 dvec4::operator*(double s) const {
  return dvec4(
           x() * s,
           y() * s,
           z() * s,
           w() * s
         );
}

dvec4 dvec4::operator*(const dvec4& _) const {
  return dvec4(
           x() * _.x(),
           y() * _.y(),
           z() * _.z(),
           w() * _.w()
         );
}

dvec4& dvec4::operator*=(double s) {
  return *this = *this * s;
}

dvec4& dvec4::operator*=(const dvec4 v) {
  return *this = *this * v;
}

dvec4 dvec4::operator/(double s) const {
  return dvec4(
           x() / s,
           y() / s,
           z() / s,
           w() / s
         );
}

dvec4 dvec4::operator/(const dvec4& _) const {
  return dvec4(
           x() / _.x(),
           y() / _.y(),
           z() / _.z(),
           w() / _.w()
         );
}

dvec4& dvec4::operator/=(double s) {
  return *this = *this / s;
}

dvec4& dvec4::operator/=(const dvec4 v) {
  return *this = *this / v;
}

// unary +
dvec4 dvec4::operator+() const {
  return *this;
}

// const subscript
double dvec4:: operator[](int i) const   {
  i < 0 && rmr.die("dvec4.operator[]: negative index");
  i >= 4 && rmr.die("dvec4.operator[]: index too large");
  return __[i];
} // mutable subscript
double& dvec4:: operator[](int i)   {
  i < 0 && rmr.die("dvec4.operator[]: negative index");
  i >= 4 && rmr.die("dvec4.operator[]: index too large");
  return __[i];
} // iteration
const double* dvec4:: begin() const   {
  return data()         ;  // length and size
}
double* dvec4:: begin()         {
  return data()         ;
}
const double* dvec4:: end  () const   {
  return data() + 4;
}
double* dvec4:: end  ()         {
  return data() + 4;
}
size_t dvec4:: size() const   {
  return 4;  // sum
}
double dvec4:: sum() const   {
  return  x() +  y() +  z() +  w()  ;
} // unary -
dvec4 dvec4:: operator-() const   {
  return *this * -1.0;
} // equality
bool dvec4:: operator==(const dvec4& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  if (w() != v.w()) return false;
  return true;
}
bool dvec4:: operator!=(const dvec4& v) const   {
  return !(*this == v);
}
dvec4 dvec4::random() {
  return random(0, 1);
}

dvec4 dvec4::random(double max) {
  return random(0, max);
}

dvec4 dvec4::random(double min, double max) {
  return dvec4( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

double dvec4::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() + w() * w() );
}

// normalize
dvec4& dvec4::normalize() {
  double l = magnitude();
  l > 0 || rmr.die("dvec4.normalize: zero magnitude");
  return *this /= l;
}

// extend
// hash
dvec4 dvec4:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 4;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    double((h >> bits * 0 & mask) / double(mask)),
    double((h >> bits * 1 & mask) / double(mask)),
    double((h >> bits * 2 & mask) / double(mask)),
    double((h >> bits * 3 & mask) / double(mask))
  };

} // from heading
// to heading
// dot
double dvec4:: dot(const dvec4& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z() +  w() * _.w()  ;
} // dot
// bits
dvec4 dvec4:: bits(int x)   {
  return dvec4(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1,
           (x >> 3) & 1
         );
}
ostream& operator<<(ostream& os, const dvec4& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z() << " "
         << v.w()
         << ")";
}
// no argument constructor
// whatever constructor
ivec4:: ivec4(whatever_t w)   { } // scalar component constructor
ivec4:: ivec4(
  int x,
  int y,
  int z,
  int w
)   : __{ x, y, z, w } {
} // single component constructor
ivec4:: ivec4(int s)   : __{ s, s, s, s } { } // pointer initializer
ivec4:: ivec4(int (&p)[4])   : __{
    p[0],   p[1],   p[2],   p[3]  } { }    // component accessors
int  ivec4:: x(   ) const   {
  return __[0];             // swizzles
}
int& ivec4:: x(   )         {
  return __[0];
}
ivec4& ivec4:: x(int s)         {
  __[0] = s;
  return *this;
}
int  ivec4:: y(   ) const   {
  return __[1];
}
int& ivec4:: y(   )         {
  return __[1];
}
ivec4& ivec4:: y(int s)         {
  __[1] = s;
  return *this;
}
int  ivec4:: z(   ) const   {
  return __[2];
}
int& ivec4:: z(   )         {
  return __[2];
}
ivec4& ivec4:: z(int s)         {
  __[2] = s;
  return *this;
}
int  ivec4:: w(   ) const   {
  return __[3];
}
int& ivec4:: w(   )         {
  return __[3];
}
ivec4& ivec4:: w(int s)         {
  __[3] = s;
  return *this;
}
int  ivec4:: r(   ) const   {
  return __[0];
}
int& ivec4:: r(   )         {
  return __[0];
}
ivec4& ivec4:: r(int s)         {
  __[0] = s;
  return *this;
}
int  ivec4:: g(   ) const   {
  return __[1];
}
int& ivec4:: g(   )         {
  return __[1];
}
ivec4& ivec4:: g(int s)         {
  __[1] = s;
  return *this;
}
int  ivec4:: b(   ) const   {
  return __[2];
}
int& ivec4:: b(   )         {
  return __[2];
}
ivec4& ivec4:: b(int s)         {
  __[2] = s;
  return *this;
}
int  ivec4:: a(   ) const   {
  return __[3];
}
int& ivec4:: a(   )         {
  return __[3];
}
ivec4& ivec4:: a(int s)         {
  __[3] = s;
  return *this;
}
int  ivec4:: s(   ) const   {
  return __[0];
}
int& ivec4:: s(   )         {
  return __[0];
}
ivec4& ivec4:: s(int s)         {
  __[0] = s;
  return *this;
}
int  ivec4:: t(   ) const   {
  return __[1];
}
int& ivec4:: t(   )         {
  return __[1];
}
ivec4& ivec4:: t(int s)         {
  __[1] = s;
  return *this;
}
int  ivec4:: p(   ) const   {
  return __[2];
}
int& ivec4:: p(   )         {
  return __[2];
}
ivec4& ivec4:: p(int s)         {
  __[2] = s;
  return *this;
}
int  ivec4:: q(   ) const   {
  return __[3];
}
int& ivec4:: q(   )         {
  return __[3];
}
ivec4& ivec4:: q(int s)         {
  __[3] = s;
  return *this;
}
// data pointers
int* ivec4:: data()         {
  return __;  // operators
}
const int* ivec4:: data() const   {
  return __;
}
ivec4 ivec4::operator+(int s) const {
  return ivec4(
           x() + s,
           y() + s,
           z() + s,
           w() + s
         );
}

ivec4 ivec4::operator+(const ivec4& _) const {
  return ivec4(
           x() + _.x(),
           y() + _.y(),
           z() + _.z(),
           w() + _.w()
         );
}

ivec4& ivec4::operator+=(int s) {
  return *this = *this + s;
}

ivec4& ivec4::operator+=(const ivec4 v) {
  return *this = *this + v;
}

ivec4 ivec4::operator-(int s) const {
  return ivec4(
           x() - s,
           y() - s,
           z() - s,
           w() - s
         );
}

ivec4 ivec4::operator-(const ivec4& _) const {
  return ivec4(
           x() - _.x(),
           y() - _.y(),
           z() - _.z(),
           w() - _.w()
         );
}

ivec4& ivec4::operator-=(int s) {
  return *this = *this - s;
}

ivec4& ivec4::operator-=(const ivec4 v) {
  return *this = *this - v;
}

ivec4 ivec4::operator*(int s) const {
  return ivec4(
           x() * s,
           y() * s,
           z() * s,
           w() * s
         );
}

ivec4 ivec4::operator*(const ivec4& _) const {
  return ivec4(
           x() * _.x(),
           y() * _.y(),
           z() * _.z(),
           w() * _.w()
         );
}

ivec4& ivec4::operator*=(int s) {
  return *this = *this * s;
}

ivec4& ivec4::operator*=(const ivec4 v) {
  return *this = *this * v;
}

ivec4 ivec4::operator/(int s) const {
  return ivec4(
           x() / s,
           y() / s,
           z() / s,
           w() / s
         );
}

ivec4 ivec4::operator/(const ivec4& _) const {
  return ivec4(
           x() / _.x(),
           y() / _.y(),
           z() / _.z(),
           w() / _.w()
         );
}

ivec4& ivec4::operator/=(int s) {
  return *this = *this / s;
}

ivec4& ivec4::operator/=(const ivec4 v) {
  return *this = *this / v;
}

// unary +
ivec4 ivec4::operator+() const {
  return *this;
}

// const subscript
int ivec4:: operator[](int i) const   {
  i < 0 && rmr.die("ivec4.operator[]: negative index");
  i >= 4 && rmr.die("ivec4.operator[]: index too large");
  return __[i];
} // mutable subscript
int& ivec4:: operator[](int i)   {
  i < 0 && rmr.die("ivec4.operator[]: negative index");
  i >= 4 && rmr.die("ivec4.operator[]: index too large");
  return __[i];
} // iteration
const int* ivec4:: begin() const   {
  return data()         ;  // length and size
}
int* ivec4:: begin()         {
  return data()         ;
}
const int* ivec4:: end  () const   {
  return data() + 4;
}
int* ivec4:: end  ()         {
  return data() + 4;
}
size_t ivec4:: size() const   {
  return 4;  // sum
}
int ivec4:: sum() const   {
  return  x() +  y() +  z() +  w()  ;
} // unary -
ivec4 ivec4:: operator-() const   {
  return *this * -1.0;
} // equality
bool ivec4:: operator==(const ivec4& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  if (w() != v.w()) return false;
  return true;
}
bool ivec4:: operator!=(const ivec4& v) const   {
  return !(*this == v);
}
ivec4 ivec4::random() {
  return random(0, 1);
}

ivec4 ivec4::random(int max) {
  return random(0, max);
}

ivec4 ivec4::random(int min, int max) {
  return ivec4( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

int ivec4::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() + w() * w() );
}

// normalize
ivec4& ivec4::normalize() {
  int l = magnitude();
  l > 0 || rmr.die("ivec4.normalize: zero magnitude");
  return *this /= l;
}

// extend
// hash
ivec4 ivec4:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 4;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    int((h >> bits * 0 & mask) / int(mask)),
    int((h >> bits * 1 & mask) / int(mask)),
    int((h >> bits * 2 & mask) / int(mask)),
    int((h >> bits * 3 & mask) / int(mask))
  };

} // from heading
// to heading
// dot
int ivec4:: dot(const ivec4& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z() +  w() * _.w()  ;
} // dot
// bits
ivec4 ivec4:: bits(int x)   {
  return ivec4(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1,
           (x >> 3) & 1
         );
}
ostream& operator<<(ostream& os, const ivec4& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z() << " "
         << v.w()
         << ")";
}
// no argument constructor
// whatever constructor
uvec4:: uvec4(whatever_t w)   { } // scalar component constructor
uvec4:: uvec4(
  uint x,
  uint y,
  uint z,
  uint w
)   : __{ x, y, z, w } {
} // single component constructor
uvec4:: uvec4(uint s)   : __{ s, s, s, s } { } // pointer initializer
uvec4:: uvec4(uint (&p)[4])   : __{
    p[0],   p[1],   p[2],   p[3]  } { }    // component accessors
uint  uvec4:: x(   ) const   {
  return __[0];             // swizzles
}
uint& uvec4:: x(   )         {
  return __[0];
}
uvec4& uvec4:: x(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec4:: y(   ) const   {
  return __[1];
}
uint& uvec4:: y(   )         {
  return __[1];
}
uvec4& uvec4:: y(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec4:: z(   ) const   {
  return __[2];
}
uint& uvec4:: z(   )         {
  return __[2];
}
uvec4& uvec4:: z(uint s)         {
  __[2] = s;
  return *this;
}
uint  uvec4:: w(   ) const   {
  return __[3];
}
uint& uvec4:: w(   )         {
  return __[3];
}
uvec4& uvec4:: w(uint s)         {
  __[3] = s;
  return *this;
}
uint  uvec4:: r(   ) const   {
  return __[0];
}
uint& uvec4:: r(   )         {
  return __[0];
}
uvec4& uvec4:: r(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec4:: g(   ) const   {
  return __[1];
}
uint& uvec4:: g(   )         {
  return __[1];
}
uvec4& uvec4:: g(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec4:: b(   ) const   {
  return __[2];
}
uint& uvec4:: b(   )         {
  return __[2];
}
uvec4& uvec4:: b(uint s)         {
  __[2] = s;
  return *this;
}
uint  uvec4:: a(   ) const   {
  return __[3];
}
uint& uvec4:: a(   )         {
  return __[3];
}
uvec4& uvec4:: a(uint s)         {
  __[3] = s;
  return *this;
}
uint  uvec4:: s(   ) const   {
  return __[0];
}
uint& uvec4:: s(   )         {
  return __[0];
}
uvec4& uvec4:: s(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec4:: t(   ) const   {
  return __[1];
}
uint& uvec4:: t(   )         {
  return __[1];
}
uvec4& uvec4:: t(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec4:: p(   ) const   {
  return __[2];
}
uint& uvec4:: p(   )         {
  return __[2];
}
uvec4& uvec4:: p(uint s)         {
  __[2] = s;
  return *this;
}
uint  uvec4:: q(   ) const   {
  return __[3];
}
uint& uvec4:: q(   )         {
  return __[3];
}
uvec4& uvec4:: q(uint s)         {
  __[3] = s;
  return *this;
}
// data pointers
uint* uvec4:: data()         {
  return __;  // operators
}
const uint* uvec4:: data() const   {
  return __;
}
uvec4 uvec4::operator+(uint s) const {
  return uvec4(
           x() + s,
           y() + s,
           z() + s,
           w() + s
         );
}

uvec4 uvec4::operator+(const uvec4& _) const {
  return uvec4(
           x() + _.x(),
           y() + _.y(),
           z() + _.z(),
           w() + _.w()
         );
}

uvec4& uvec4::operator+=(uint s) {
  return *this = *this + s;
}

uvec4& uvec4::operator+=(const uvec4 v) {
  return *this = *this + v;
}

uvec4 uvec4::operator-(uint s) const {
  return uvec4(
           x() - s,
           y() - s,
           z() - s,
           w() - s
         );
}

uvec4 uvec4::operator-(const uvec4& _) const {
  return uvec4(
           x() - _.x(),
           y() - _.y(),
           z() - _.z(),
           w() - _.w()
         );
}

uvec4& uvec4::operator-=(uint s) {
  return *this = *this - s;
}

uvec4& uvec4::operator-=(const uvec4 v) {
  return *this = *this - v;
}

uvec4 uvec4::operator*(uint s) const {
  return uvec4(
           x() * s,
           y() * s,
           z() * s,
           w() * s
         );
}

uvec4 uvec4::operator*(const uvec4& _) const {
  return uvec4(
           x() * _.x(),
           y() * _.y(),
           z() * _.z(),
           w() * _.w()
         );
}

uvec4& uvec4::operator*=(uint s) {
  return *this = *this * s;
}

uvec4& uvec4::operator*=(const uvec4 v) {
  return *this = *this * v;
}

uvec4 uvec4::operator/(uint s) const {
  return uvec4(
           x() / s,
           y() / s,
           z() / s,
           w() / s
         );
}

uvec4 uvec4::operator/(const uvec4& _) const {
  return uvec4(
           x() / _.x(),
           y() / _.y(),
           z() / _.z(),
           w() / _.w()
         );
}

uvec4& uvec4::operator/=(uint s) {
  return *this = *this / s;
}

uvec4& uvec4::operator/=(const uvec4 v) {
  return *this = *this / v;
}

// unary +
uvec4 uvec4::operator+() const {
  return *this;
}

// const subscript
uint uvec4:: operator[](int i) const   {
  i < 0 && rmr.die("uvec4.operator[]: negative index");
  i >= 4 && rmr.die("uvec4.operator[]: index too large");
  return __[i];
} // mutable subscript
uint& uvec4:: operator[](int i)   {
  i < 0 && rmr.die("uvec4.operator[]: negative index");
  i >= 4 && rmr.die("uvec4.operator[]: index too large");
  return __[i];
} // iteration
const uint* uvec4:: begin() const   {
  return data()         ;  // length and size
}
uint* uvec4:: begin()         {
  return data()         ;
}
const uint* uvec4:: end  () const   {
  return data() + 4;
}
uint* uvec4:: end  ()         {
  return data() + 4;
}
size_t uvec4:: size() const   {
  return 4;  // sum
}
uint uvec4:: sum() const   {
  return  x() +  y() +  z() +  w()  ;
} // unary -
// equality
bool uvec4:: operator==(const uvec4& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  if (w() != v.w()) return false;
  return true;
}
bool uvec4:: operator!=(const uvec4& v) const   {
  return !(*this == v);
}
uvec4 uvec4::random() {
  return random(0, 1);
}

uvec4 uvec4::random(uint max) {
  return random(0, max);
}

uvec4 uvec4::random(uint min, uint max) {
  return uvec4( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

uint uvec4::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() + w() * w() );
}

// normalize
uvec4& uvec4::normalize() {
  uint l = magnitude();
  l > 0 || rmr.die("uvec4.normalize: zero magnitude");
  return *this /= l;
}

// extend
// hash
uvec4 uvec4:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 4;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    uint((h >> bits * 0 & mask) / uint(mask)),
    uint((h >> bits * 1 & mask) / uint(mask)),
    uint((h >> bits * 2 & mask) / uint(mask)),
    uint((h >> bits * 3 & mask) / uint(mask))
  };

} // from heading
// to heading
// dot
uint uvec4:: dot(const uvec4& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z() +  w() * _.w()  ;
} // dot
// bits
uvec4 uvec4:: bits(int x)   {
  return uvec4(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1,
           (x >> 3) & 1
         );
}
ostream& operator<<(ostream& os, const uvec4& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z() << " "
         << v.w()
         << ")";
}
// no argument constructor
// whatever constructor
vec3:: vec3(whatever_t w)   { } // scalar component constructor
vec3:: vec3(
  float x,
  float y,
  float z
)   : __{ x, y, z } {
} // single component constructor
vec3:: vec3(float s)   : __{ s, s, s } { } // pointer initializer
vec3:: vec3(float (&p)[3])   : __{
    p[0],   p[1],   p[2]  } { }   // component accessors
float  vec3:: x(   ) const   {
  return __[0];             // swizzles
}
float& vec3:: x(   )         {
  return __[0];
}
vec3& vec3:: x(float s)         {
  __[0] = s;
  return *this;
}
float  vec3:: y(   ) const   {
  return __[1];
}
float& vec3:: y(   )         {
  return __[1];
}
vec3& vec3:: y(float s)         {
  __[1] = s;
  return *this;
}
float  vec3:: z(   ) const   {
  return __[2];
}
float& vec3:: z(   )         {
  return __[2];
}
vec3& vec3:: z(float s)         {
  __[2] = s;
  return *this;
}
float  vec3:: r(   ) const   {
  return __[0];
}
float& vec3:: r(   )         {
  return __[0];
}
vec3& vec3:: r(float s)         {
  __[0] = s;
  return *this;
}
float  vec3:: g(   ) const   {
  return __[1];
}
float& vec3:: g(   )         {
  return __[1];
}
vec3& vec3:: g(float s)         {
  __[1] = s;
  return *this;
}
float  vec3:: b(   ) const   {
  return __[2];
}
float& vec3:: b(   )         {
  return __[2];
}
vec3& vec3:: b(float s)         {
  __[2] = s;
  return *this;
}
float  vec3:: s(   ) const   {
  return __[0];
}
float& vec3:: s(   )         {
  return __[0];
}
vec3& vec3:: s(float s)         {
  __[0] = s;
  return *this;
}
float  vec3:: t(   ) const   {
  return __[1];
}
float& vec3:: t(   )         {
  return __[1];
}
vec3& vec3:: t(float s)         {
  __[1] = s;
  return *this;
}
float  vec3:: p(   ) const   {
  return __[2];
}
float& vec3:: p(   )         {
  return __[2];
}
vec3& vec3:: p(float s)         {
  __[2] = s;
  return *this;
}
// data pointers
float* vec3:: data()         {
  return __;  // operators
}
const float* vec3:: data() const   {
  return __;
}
vec3 vec3::operator+(float s) const {
  return vec3(
           x() + s,
           y() + s,
           z() + s
         );
}

vec3 vec3::operator+(const vec3& _) const {
  return vec3(
           x() + _.x(),
           y() + _.y(),
           z() + _.z()
         );
}

vec3& vec3::operator+=(float s) {
  return *this = *this + s;
}

vec3& vec3::operator+=(const vec3 v) {
  return *this = *this + v;
}

vec3 vec3::operator-(float s) const {
  return vec3(
           x() - s,
           y() - s,
           z() - s
         );
}

vec3 vec3::operator-(const vec3& _) const {
  return vec3(
           x() - _.x(),
           y() - _.y(),
           z() - _.z()
         );
}

vec3& vec3::operator-=(float s) {
  return *this = *this - s;
}

vec3& vec3::operator-=(const vec3 v) {
  return *this = *this - v;
}

vec3 vec3::operator*(float s) const {
  return vec3(
           x() * s,
           y() * s,
           z() * s
         );
}

vec3 vec3::operator*(const vec3& _) const {
  return vec3(
           x() * _.x(),
           y() * _.y(),
           z() * _.z()
         );
}

vec3& vec3::operator*=(float s) {
  return *this = *this * s;
}

vec3& vec3::operator*=(const vec3 v) {
  return *this = *this * v;
}

vec3 vec3::operator/(float s) const {
  return vec3(
           x() / s,
           y() / s,
           z() / s
         );
}

vec3 vec3::operator/(const vec3& _) const {
  return vec3(
           x() / _.x(),
           y() / _.y(),
           z() / _.z()
         );
}

vec3& vec3::operator/=(float s) {
  return *this = *this / s;
}

vec3& vec3::operator/=(const vec3 v) {
  return *this = *this / v;
}

// unary +
vec3 vec3::operator+() const {
  return *this;
}

// const subscript
float vec3:: operator[](int i) const   {
  i < 0 && rmr.die("vec3.operator[]: negative index");
  i >= 3 && rmr.die("vec3.operator[]: index too large");
  return __[i];
} // mutable subscript
float& vec3:: operator[](int i)   {
  i < 0 && rmr.die("vec3.operator[]: negative index");
  i >= 3 && rmr.die("vec3.operator[]: index too large");
  return __[i];
} // iteration
const float* vec3:: begin() const   {
  return data()         ;  // length and size
}
float* vec3:: begin()         {
  return data()         ;
}
const float* vec3:: end  () const   {
  return data() + 3;
}
float* vec3:: end  ()         {
  return data() + 3;
}
size_t vec3:: size() const   {
  return 3;  // sum
}
float vec3:: sum() const   {
  return  x() +  y() +  z()  ;
} // unary -
vec3 vec3:: operator-() const   {
  return *this * -1.0;
} // equality
bool vec3:: operator==(const vec3& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  return true;
}
bool vec3:: operator!=(const vec3& v) const   {
  return !(*this == v);
}
vec3 vec3::random() {
  return random(0, 1);
}

vec3 vec3::random(float max) {
  return random(0, max);
}

vec3 vec3::random(float min, float max) {
  return vec3( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

float vec3::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() );
}

// normalize
vec3& vec3::normalize() {
  float l = magnitude();
  l > 0 || rmr.die("vec3.normalize: zero magnitude");
  return *this /= l;
}

// extend
vec4 vec3::extend(float s) const {
  return vec4(
           x(),
           y(),
           z(),
           s
         );
}

// hash
vec3 vec3:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 3;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    float((h >> bits * 0 & mask) / float(mask)),
    float((h >> bits * 1 & mask) / float(mask)),
    float((h >> bits * 2 & mask) / float(mask))
  };

} // from heading
// to heading
// dot
float vec3:: dot(const vec3& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z()  ;
} // dot
vec3 vec3:: cross(const vec3& _)   {
  return {
    y() * _.z() - z() * _.y(),
           z() * _.x() - x() * _.z(),
           x() * _.y() - y() * _.x()
  };
} // bits
vec3 vec3:: bits(int x)   {
  return vec3(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1
         );
}
ostream& operator<<(ostream& os, const vec3& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z()
         << ")";
}
// no argument constructor
// whatever constructor
dvec3:: dvec3(whatever_t w)   { } // scalar component constructor
dvec3:: dvec3(
  double x,
  double y,
  double z
)   : __{ x, y, z } {
} // single component constructor
dvec3:: dvec3(double s)   : __{ s, s, s } { } // pointer initializer
dvec3:: dvec3(double (&p)[3])   : __{
    p[0],   p[1],   p[2]  } { }   // component accessors
double  dvec3:: x(   ) const   {
  return __[0];             // swizzles
}
double& dvec3:: x(   )         {
  return __[0];
}
dvec3& dvec3:: x(double s)         {
  __[0] = s;
  return *this;
}
double  dvec3:: y(   ) const   {
  return __[1];
}
double& dvec3:: y(   )         {
  return __[1];
}
dvec3& dvec3:: y(double s)         {
  __[1] = s;
  return *this;
}
double  dvec3:: z(   ) const   {
  return __[2];
}
double& dvec3:: z(   )         {
  return __[2];
}
dvec3& dvec3:: z(double s)         {
  __[2] = s;
  return *this;
}
double  dvec3:: r(   ) const   {
  return __[0];
}
double& dvec3:: r(   )         {
  return __[0];
}
dvec3& dvec3:: r(double s)         {
  __[0] = s;
  return *this;
}
double  dvec3:: g(   ) const   {
  return __[1];
}
double& dvec3:: g(   )         {
  return __[1];
}
dvec3& dvec3:: g(double s)         {
  __[1] = s;
  return *this;
}
double  dvec3:: b(   ) const   {
  return __[2];
}
double& dvec3:: b(   )         {
  return __[2];
}
dvec3& dvec3:: b(double s)         {
  __[2] = s;
  return *this;
}
double  dvec3:: s(   ) const   {
  return __[0];
}
double& dvec3:: s(   )         {
  return __[0];
}
dvec3& dvec3:: s(double s)         {
  __[0] = s;
  return *this;
}
double  dvec3:: t(   ) const   {
  return __[1];
}
double& dvec3:: t(   )         {
  return __[1];
}
dvec3& dvec3:: t(double s)         {
  __[1] = s;
  return *this;
}
double  dvec3:: p(   ) const   {
  return __[2];
}
double& dvec3:: p(   )         {
  return __[2];
}
dvec3& dvec3:: p(double s)         {
  __[2] = s;
  return *this;
}
// data pointers
double* dvec3:: data()         {
  return __;  // operators
}
const double* dvec3:: data() const   {
  return __;
}
dvec3 dvec3::operator+(double s) const {
  return dvec3(
           x() + s,
           y() + s,
           z() + s
         );
}

dvec3 dvec3::operator+(const dvec3& _) const {
  return dvec3(
           x() + _.x(),
           y() + _.y(),
           z() + _.z()
         );
}

dvec3& dvec3::operator+=(double s) {
  return *this = *this + s;
}

dvec3& dvec3::operator+=(const dvec3 v) {
  return *this = *this + v;
}

dvec3 dvec3::operator-(double s) const {
  return dvec3(
           x() - s,
           y() - s,
           z() - s
         );
}

dvec3 dvec3::operator-(const dvec3& _) const {
  return dvec3(
           x() - _.x(),
           y() - _.y(),
           z() - _.z()
         );
}

dvec3& dvec3::operator-=(double s) {
  return *this = *this - s;
}

dvec3& dvec3::operator-=(const dvec3 v) {
  return *this = *this - v;
}

dvec3 dvec3::operator*(double s) const {
  return dvec3(
           x() * s,
           y() * s,
           z() * s
         );
}

dvec3 dvec3::operator*(const dvec3& _) const {
  return dvec3(
           x() * _.x(),
           y() * _.y(),
           z() * _.z()
         );
}

dvec3& dvec3::operator*=(double s) {
  return *this = *this * s;
}

dvec3& dvec3::operator*=(const dvec3 v) {
  return *this = *this * v;
}

dvec3 dvec3::operator/(double s) const {
  return dvec3(
           x() / s,
           y() / s,
           z() / s
         );
}

dvec3 dvec3::operator/(const dvec3& _) const {
  return dvec3(
           x() / _.x(),
           y() / _.y(),
           z() / _.z()
         );
}

dvec3& dvec3::operator/=(double s) {
  return *this = *this / s;
}

dvec3& dvec3::operator/=(const dvec3 v) {
  return *this = *this / v;
}

// unary +
dvec3 dvec3::operator+() const {
  return *this;
}

// const subscript
double dvec3:: operator[](int i) const   {
  i < 0 && rmr.die("dvec3.operator[]: negative index");
  i >= 3 && rmr.die("dvec3.operator[]: index too large");
  return __[i];
} // mutable subscript
double& dvec3:: operator[](int i)   {
  i < 0 && rmr.die("dvec3.operator[]: negative index");
  i >= 3 && rmr.die("dvec3.operator[]: index too large");
  return __[i];
} // iteration
const double* dvec3:: begin() const   {
  return data()         ;  // length and size
}
double* dvec3:: begin()         {
  return data()         ;
}
const double* dvec3:: end  () const   {
  return data() + 3;
}
double* dvec3:: end  ()         {
  return data() + 3;
}
size_t dvec3:: size() const   {
  return 3;  // sum
}
double dvec3:: sum() const   {
  return  x() +  y() +  z()  ;
} // unary -
dvec3 dvec3:: operator-() const   {
  return *this * -1.0;
} // equality
bool dvec3:: operator==(const dvec3& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  return true;
}
bool dvec3:: operator!=(const dvec3& v) const   {
  return !(*this == v);
}
dvec3 dvec3::random() {
  return random(0, 1);
}

dvec3 dvec3::random(double max) {
  return random(0, max);
}

dvec3 dvec3::random(double min, double max) {
  return dvec3( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

double dvec3::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() );
}

// normalize
dvec3& dvec3::normalize() {
  double l = magnitude();
  l > 0 || rmr.die("dvec3.normalize: zero magnitude");
  return *this /= l;
}

// extend
dvec4 dvec3::extend(double s) const {
  return dvec4(
           x(),
           y(),
           z(),
           s
         );
}

// hash
dvec3 dvec3:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 3;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    double((h >> bits * 0 & mask) / double(mask)),
    double((h >> bits * 1 & mask) / double(mask)),
    double((h >> bits * 2 & mask) / double(mask))
  };

} // from heading
// to heading
// dot
double dvec3:: dot(const dvec3& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z()  ;
} // dot
dvec3 dvec3:: cross(const dvec3& _)   {
  return {
    y() * _.z() - z() * _.y(),
           z() * _.x() - x() * _.z(),
           x() * _.y() - y() * _.x()
  };
} // bits
dvec3 dvec3:: bits(int x)   {
  return dvec3(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1
         );
}
ostream& operator<<(ostream& os, const dvec3& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z()
         << ")";
}
// no argument constructor
// whatever constructor
ivec3:: ivec3(whatever_t w)   { } // scalar component constructor
ivec3:: ivec3(
  int x,
  int y,
  int z
)   : __{ x, y, z } {
} // single component constructor
ivec3:: ivec3(int s)   : __{ s, s, s } { } // pointer initializer
ivec3:: ivec3(int (&p)[3])   : __{
    p[0],   p[1],   p[2]  } { }   // component accessors
int  ivec3:: x(   ) const   {
  return __[0];             // swizzles
}
int& ivec3:: x(   )         {
  return __[0];
}
ivec3& ivec3:: x(int s)         {
  __[0] = s;
  return *this;
}
int  ivec3:: y(   ) const   {
  return __[1];
}
int& ivec3:: y(   )         {
  return __[1];
}
ivec3& ivec3:: y(int s)         {
  __[1] = s;
  return *this;
}
int  ivec3:: z(   ) const   {
  return __[2];
}
int& ivec3:: z(   )         {
  return __[2];
}
ivec3& ivec3:: z(int s)         {
  __[2] = s;
  return *this;
}
int  ivec3:: r(   ) const   {
  return __[0];
}
int& ivec3:: r(   )         {
  return __[0];
}
ivec3& ivec3:: r(int s)         {
  __[0] = s;
  return *this;
}
int  ivec3:: g(   ) const   {
  return __[1];
}
int& ivec3:: g(   )         {
  return __[1];
}
ivec3& ivec3:: g(int s)         {
  __[1] = s;
  return *this;
}
int  ivec3:: b(   ) const   {
  return __[2];
}
int& ivec3:: b(   )         {
  return __[2];
}
ivec3& ivec3:: b(int s)         {
  __[2] = s;
  return *this;
}
int  ivec3:: s(   ) const   {
  return __[0];
}
int& ivec3:: s(   )         {
  return __[0];
}
ivec3& ivec3:: s(int s)         {
  __[0] = s;
  return *this;
}
int  ivec3:: t(   ) const   {
  return __[1];
}
int& ivec3:: t(   )         {
  return __[1];
}
ivec3& ivec3:: t(int s)         {
  __[1] = s;
  return *this;
}
int  ivec3:: p(   ) const   {
  return __[2];
}
int& ivec3:: p(   )         {
  return __[2];
}
ivec3& ivec3:: p(int s)         {
  __[2] = s;
  return *this;
}
// data pointers
int* ivec3:: data()         {
  return __;  // operators
}
const int* ivec3:: data() const   {
  return __;
}
ivec3 ivec3::operator+(int s) const {
  return ivec3(
           x() + s,
           y() + s,
           z() + s
         );
}

ivec3 ivec3::operator+(const ivec3& _) const {
  return ivec3(
           x() + _.x(),
           y() + _.y(),
           z() + _.z()
         );
}

ivec3& ivec3::operator+=(int s) {
  return *this = *this + s;
}

ivec3& ivec3::operator+=(const ivec3 v) {
  return *this = *this + v;
}

ivec3 ivec3::operator-(int s) const {
  return ivec3(
           x() - s,
           y() - s,
           z() - s
         );
}

ivec3 ivec3::operator-(const ivec3& _) const {
  return ivec3(
           x() - _.x(),
           y() - _.y(),
           z() - _.z()
         );
}

ivec3& ivec3::operator-=(int s) {
  return *this = *this - s;
}

ivec3& ivec3::operator-=(const ivec3 v) {
  return *this = *this - v;
}

ivec3 ivec3::operator*(int s) const {
  return ivec3(
           x() * s,
           y() * s,
           z() * s
         );
}

ivec3 ivec3::operator*(const ivec3& _) const {
  return ivec3(
           x() * _.x(),
           y() * _.y(),
           z() * _.z()
         );
}

ivec3& ivec3::operator*=(int s) {
  return *this = *this * s;
}

ivec3& ivec3::operator*=(const ivec3 v) {
  return *this = *this * v;
}

ivec3 ivec3::operator/(int s) const {
  return ivec3(
           x() / s,
           y() / s,
           z() / s
         );
}

ivec3 ivec3::operator/(const ivec3& _) const {
  return ivec3(
           x() / _.x(),
           y() / _.y(),
           z() / _.z()
         );
}

ivec3& ivec3::operator/=(int s) {
  return *this = *this / s;
}

ivec3& ivec3::operator/=(const ivec3 v) {
  return *this = *this / v;
}

// unary +
ivec3 ivec3::operator+() const {
  return *this;
}

// const subscript
int ivec3:: operator[](int i) const   {
  i < 0 && rmr.die("ivec3.operator[]: negative index");
  i >= 3 && rmr.die("ivec3.operator[]: index too large");
  return __[i];
} // mutable subscript
int& ivec3:: operator[](int i)   {
  i < 0 && rmr.die("ivec3.operator[]: negative index");
  i >= 3 && rmr.die("ivec3.operator[]: index too large");
  return __[i];
} // iteration
const int* ivec3:: begin() const   {
  return data()         ;  // length and size
}
int* ivec3:: begin()         {
  return data()         ;
}
const int* ivec3:: end  () const   {
  return data() + 3;
}
int* ivec3:: end  ()         {
  return data() + 3;
}
size_t ivec3:: size() const   {
  return 3;  // sum
}
int ivec3:: sum() const   {
  return  x() +  y() +  z()  ;
} // unary -
ivec3 ivec3:: operator-() const   {
  return *this * -1.0;
} // equality
bool ivec3:: operator==(const ivec3& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  return true;
}
bool ivec3:: operator!=(const ivec3& v) const   {
  return !(*this == v);
}
ivec3 ivec3::random() {
  return random(0, 1);
}

ivec3 ivec3::random(int max) {
  return random(0, max);
}

ivec3 ivec3::random(int min, int max) {
  return ivec3( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

int ivec3::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() );
}

// normalize
ivec3& ivec3::normalize() {
  int l = magnitude();
  l > 0 || rmr.die("ivec3.normalize: zero magnitude");
  return *this /= l;
}

// extend
ivec4 ivec3::extend(int s) const {
  return ivec4(
           x(),
           y(),
           z(),
           s
         );
}

// hash
ivec3 ivec3:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 3;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    int((h >> bits * 0 & mask) / int(mask)),
    int((h >> bits * 1 & mask) / int(mask)),
    int((h >> bits * 2 & mask) / int(mask))
  };

} // from heading
// to heading
// dot
int ivec3:: dot(const ivec3& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z()  ;
} // dot
ivec3 ivec3:: cross(const ivec3& _)   {
  return {
    y() * _.z() - z() * _.y(),
           z() * _.x() - x() * _.z(),
           x() * _.y() - y() * _.x()
  };
} // bits
ivec3 ivec3:: bits(int x)   {
  return ivec3(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1
         );
}
ostream& operator<<(ostream& os, const ivec3& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z()
         << ")";
}
// no argument constructor
// whatever constructor
uvec3:: uvec3(whatever_t w)   { } // scalar component constructor
uvec3:: uvec3(
  uint x,
  uint y,
  uint z
)   : __{ x, y, z } {
} // single component constructor
uvec3:: uvec3(uint s)   : __{ s, s, s } { } // pointer initializer
uvec3:: uvec3(uint (&p)[3])   : __{
    p[0],   p[1],   p[2]  } { }   // component accessors
uint  uvec3:: x(   ) const   {
  return __[0];             // swizzles
}
uint& uvec3:: x(   )         {
  return __[0];
}
uvec3& uvec3:: x(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec3:: y(   ) const   {
  return __[1];
}
uint& uvec3:: y(   )         {
  return __[1];
}
uvec3& uvec3:: y(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec3:: z(   ) const   {
  return __[2];
}
uint& uvec3:: z(   )         {
  return __[2];
}
uvec3& uvec3:: z(uint s)         {
  __[2] = s;
  return *this;
}
uint  uvec3:: r(   ) const   {
  return __[0];
}
uint& uvec3:: r(   )         {
  return __[0];
}
uvec3& uvec3:: r(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec3:: g(   ) const   {
  return __[1];
}
uint& uvec3:: g(   )         {
  return __[1];
}
uvec3& uvec3:: g(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec3:: b(   ) const   {
  return __[2];
}
uint& uvec3:: b(   )         {
  return __[2];
}
uvec3& uvec3:: b(uint s)         {
  __[2] = s;
  return *this;
}
uint  uvec3:: s(   ) const   {
  return __[0];
}
uint& uvec3:: s(   )         {
  return __[0];
}
uvec3& uvec3:: s(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec3:: t(   ) const   {
  return __[1];
}
uint& uvec3:: t(   )         {
  return __[1];
}
uvec3& uvec3:: t(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec3:: p(   ) const   {
  return __[2];
}
uint& uvec3:: p(   )         {
  return __[2];
}
uvec3& uvec3:: p(uint s)         {
  __[2] = s;
  return *this;
}
// data pointers
uint* uvec3:: data()         {
  return __;  // operators
}
const uint* uvec3:: data() const   {
  return __;
}
uvec3 uvec3::operator+(uint s) const {
  return uvec3(
           x() + s,
           y() + s,
           z() + s
         );
}

uvec3 uvec3::operator+(const uvec3& _) const {
  return uvec3(
           x() + _.x(),
           y() + _.y(),
           z() + _.z()
         );
}

uvec3& uvec3::operator+=(uint s) {
  return *this = *this + s;
}

uvec3& uvec3::operator+=(const uvec3 v) {
  return *this = *this + v;
}

uvec3 uvec3::operator-(uint s) const {
  return uvec3(
           x() - s,
           y() - s,
           z() - s
         );
}

uvec3 uvec3::operator-(const uvec3& _) const {
  return uvec3(
           x() - _.x(),
           y() - _.y(),
           z() - _.z()
         );
}

uvec3& uvec3::operator-=(uint s) {
  return *this = *this - s;
}

uvec3& uvec3::operator-=(const uvec3 v) {
  return *this = *this - v;
}

uvec3 uvec3::operator*(uint s) const {
  return uvec3(
           x() * s,
           y() * s,
           z() * s
         );
}

uvec3 uvec3::operator*(const uvec3& _) const {
  return uvec3(
           x() * _.x(),
           y() * _.y(),
           z() * _.z()
         );
}

uvec3& uvec3::operator*=(uint s) {
  return *this = *this * s;
}

uvec3& uvec3::operator*=(const uvec3 v) {
  return *this = *this * v;
}

uvec3 uvec3::operator/(uint s) const {
  return uvec3(
           x() / s,
           y() / s,
           z() / s
         );
}

uvec3 uvec3::operator/(const uvec3& _) const {
  return uvec3(
           x() / _.x(),
           y() / _.y(),
           z() / _.z()
         );
}

uvec3& uvec3::operator/=(uint s) {
  return *this = *this / s;
}

uvec3& uvec3::operator/=(const uvec3 v) {
  return *this = *this / v;
}

// unary +
uvec3 uvec3::operator+() const {
  return *this;
}

// const subscript
uint uvec3:: operator[](int i) const   {
  i < 0 && rmr.die("uvec3.operator[]: negative index");
  i >= 3 && rmr.die("uvec3.operator[]: index too large");
  return __[i];
} // mutable subscript
uint& uvec3:: operator[](int i)   {
  i < 0 && rmr.die("uvec3.operator[]: negative index");
  i >= 3 && rmr.die("uvec3.operator[]: index too large");
  return __[i];
} // iteration
const uint* uvec3:: begin() const   {
  return data()         ;  // length and size
}
uint* uvec3:: begin()         {
  return data()         ;
}
const uint* uvec3:: end  () const   {
  return data() + 3;
}
uint* uvec3:: end  ()         {
  return data() + 3;
}
size_t uvec3:: size() const   {
  return 3;  // sum
}
uint uvec3:: sum() const   {
  return  x() +  y() +  z()  ;
} // unary -
// equality
bool uvec3:: operator==(const uvec3& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  if (z() != v.z()) return false;
  return true;
}
bool uvec3:: operator!=(const uvec3& v) const   {
  return !(*this == v);
}
uvec3 uvec3::random() {
  return random(0, 1);
}

uvec3 uvec3::random(uint max) {
  return random(0, max);
}

uvec3 uvec3::random(uint min, uint max) {
  return uvec3( rmr.random(min, max), rmr.random(min, max), rmr.random(min, max));
}

uint uvec3::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() + z() * z() );
}

// normalize
uvec3& uvec3::normalize() {
  uint l = magnitude();
  l > 0 || rmr.die("uvec3.normalize: zero magnitude");
  return *this /= l;
}

// extend
uvec4 uvec3::extend(uint s) const {
  return uvec4(
           x(),
           y(),
           z(),
           s
         );
}

// hash
uvec3 uvec3:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 3;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    uint((h >> bits * 0 & mask) / uint(mask)),
    uint((h >> bits * 1 & mask) / uint(mask)),
    uint((h >> bits * 2 & mask) / uint(mask))
  };

} // from heading
// to heading
// dot
uint uvec3:: dot(const uvec3& _)   {
  return  x() * _.x() +  y() * _.y() +  z() * _.z()  ;
} // dot
uvec3 uvec3:: cross(const uvec3& _)   {
  return {
    y() * _.z() - z() * _.y(),
           z() * _.x() - x() * _.z(),
           x() * _.y() - y() * _.x()
  };
} // bits
uvec3 uvec3:: bits(int x)   {
  return uvec3(
           (x >> 0) & 1,
           (x >> 1) & 1,
           (x >> 2) & 1
         );
}
ostream& operator<<(ostream& os, const uvec3& v) {
  return os << "("
         << v.x() << " "
         << v.y() << " "
         << v.z()
         << ")";
}
// no argument constructor
// whatever constructor
vec2:: vec2(whatever_t w)   { } // scalar component constructor
vec2:: vec2(
  float x,
  float y
)   : __{ x, y } {
} // single component constructor
vec2:: vec2(float s)   : __{ s, s } { } // pointer initializer
vec2:: vec2(float (&p)[2])   : __{
    p[0],   p[1]  } { }  // component accessors
float  vec2:: x(   ) const   {
  return __[0];             // swizzles
}
float& vec2:: x(   )         {
  return __[0];
}
vec2& vec2:: x(float s)         {
  __[0] = s;
  return *this;
}
float  vec2:: y(   ) const   {
  return __[1];
}
float& vec2:: y(   )         {
  return __[1];
}
vec2& vec2:: y(float s)         {
  __[1] = s;
  return *this;
}
float  vec2:: r(   ) const   {
  return __[0];
}
float& vec2:: r(   )         {
  return __[0];
}
vec2& vec2:: r(float s)         {
  __[0] = s;
  return *this;
}
float  vec2:: g(   ) const   {
  return __[1];
}
float& vec2:: g(   )         {
  return __[1];
}
vec2& vec2:: g(float s)         {
  __[1] = s;
  return *this;
}
float  vec2:: s(   ) const   {
  return __[0];
}
float& vec2:: s(   )         {
  return __[0];
}
vec2& vec2:: s(float s)         {
  __[0] = s;
  return *this;
}
float  vec2:: t(   ) const   {
  return __[1];
}
float& vec2:: t(   )         {
  return __[1];
}
vec2& vec2:: t(float s)         {
  __[1] = s;
  return *this;
}
// data pointers
float* vec2:: data()         {
  return __;  // operators
}
const float* vec2:: data() const   {
  return __;
}
vec2 vec2::operator+(float s) const {
  return vec2(
           x() + s,
           y() + s
         );
}

vec2 vec2::operator+(const vec2& _) const {
  return vec2(
           x() + _.x(),
           y() + _.y()
         );
}

vec2& vec2::operator+=(float s) {
  return *this = *this + s;
}

vec2& vec2::operator+=(const vec2 v) {
  return *this = *this + v;
}

vec2 vec2::operator-(float s) const {
  return vec2(
           x() - s,
           y() - s
         );
}

vec2 vec2::operator-(const vec2& _) const {
  return vec2(
           x() - _.x(),
           y() - _.y()
         );
}

vec2& vec2::operator-=(float s) {
  return *this = *this - s;
}

vec2& vec2::operator-=(const vec2 v) {
  return *this = *this - v;
}

vec2 vec2::operator*(float s) const {
  return vec2(
           x() * s,
           y() * s
         );
}

vec2 vec2::operator*(const vec2& _) const {
  return vec2(
           x() * _.x(),
           y() * _.y()
         );
}

vec2& vec2::operator*=(float s) {
  return *this = *this * s;
}

vec2& vec2::operator*=(const vec2 v) {
  return *this = *this * v;
}

vec2 vec2::operator/(float s) const {
  return vec2(
           x() / s,
           y() / s
         );
}

vec2 vec2::operator/(const vec2& _) const {
  return vec2(
           x() / _.x(),
           y() / _.y()
         );
}

vec2& vec2::operator/=(float s) {
  return *this = *this / s;
}

vec2& vec2::operator/=(const vec2 v) {
  return *this = *this / v;
}

// unary +
vec2 vec2::operator+() const {
  return *this;
}

// const subscript
float vec2:: operator[](int i) const   {
  i < 0 && rmr.die("vec2.operator[]: negative index");
  i >= 2 && rmr.die("vec2.operator[]: index too large");
  return __[i];
} // mutable subscript
float& vec2:: operator[](int i)   {
  i < 0 && rmr.die("vec2.operator[]: negative index");
  i >= 2 && rmr.die("vec2.operator[]: index too large");
  return __[i];
} // iteration
const float* vec2:: begin() const   {
  return data()         ;  // length and size
}
float* vec2:: begin()         {
  return data()         ;
}
const float* vec2:: end  () const   {
  return data() + 2;
}
float* vec2:: end  ()         {
  return data() + 2;
}
size_t vec2:: size() const   {
  return 2;  // sum
}
float vec2:: sum() const   {
  return  x() +  y()  ;
} // unary -
vec2 vec2:: operator-() const   {
  return *this * -1.0;
} // equality
bool vec2:: operator==(const vec2& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  return true;
}
bool vec2:: operator!=(const vec2& v) const   {
  return !(*this == v);
}
vec2 vec2::random() {
  return random(0, 1);
}

vec2 vec2::random(float max) {
  return random(0, max);
}

vec2 vec2::random(float min, float max) {
  return vec2( rmr.random(min, max), rmr.random(min, max));
}

float vec2::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() );
}

// normalize
vec2& vec2::normalize() {
  float l = magnitude();
  l > 0 || rmr.die("vec2.normalize: zero magnitude");
  return *this /= l;
}

// extend
vec3 vec2::extend(float s) const {
  return vec3(
           x(),
           y(),
           s
         );
}

// hash
vec2 vec2:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 2;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    float((h >> bits * 0 & mask) / float(mask)),
    float((h >> bits * 1 & mask) / float(mask))
  };

} // from heading
vec2 vec2:: heading(double angle)   {
  return vec2(rmr.cos(angle), rmr.sin(angle));
} // to heading
double vec2:: heading()   {
  return rmr.atan2(y(), x());
} // dot
float vec2:: dot(const vec2& _)   {
  return  x() * _.x() +  y() * _.y()  ;
} // dot
// bits
vec2 vec2:: bits(int x)   {
  return vec2(
           (x >> 0) & 1,
           (x >> 1) & 1
         );
}
ostream& operator<<(ostream& os, const vec2& v) {
  return os << "("
         << v.x() << " "
         << v.y()
         << ")";
}
// no argument constructor
// whatever constructor
dvec2:: dvec2(whatever_t w)   { } // scalar component constructor
dvec2:: dvec2(
  double x,
  double y
)   : __{ x, y } {
} // single component constructor
dvec2:: dvec2(double s)   : __{ s, s } { } // pointer initializer
dvec2:: dvec2(double (&p)[2])   : __{
    p[0],   p[1]  } { }  // component accessors
double  dvec2:: x(   ) const   {
  return __[0];             // swizzles
}
double& dvec2:: x(   )         {
  return __[0];
}
dvec2& dvec2:: x(double s)         {
  __[0] = s;
  return *this;
}
double  dvec2:: y(   ) const   {
  return __[1];
}
double& dvec2:: y(   )         {
  return __[1];
}
dvec2& dvec2:: y(double s)         {
  __[1] = s;
  return *this;
}
double  dvec2:: r(   ) const   {
  return __[0];
}
double& dvec2:: r(   )         {
  return __[0];
}
dvec2& dvec2:: r(double s)         {
  __[0] = s;
  return *this;
}
double  dvec2:: g(   ) const   {
  return __[1];
}
double& dvec2:: g(   )         {
  return __[1];
}
dvec2& dvec2:: g(double s)         {
  __[1] = s;
  return *this;
}
double  dvec2:: s(   ) const   {
  return __[0];
}
double& dvec2:: s(   )         {
  return __[0];
}
dvec2& dvec2:: s(double s)         {
  __[0] = s;
  return *this;
}
double  dvec2:: t(   ) const   {
  return __[1];
}
double& dvec2:: t(   )         {
  return __[1];
}
dvec2& dvec2:: t(double s)         {
  __[1] = s;
  return *this;
}
// data pointers
double* dvec2:: data()         {
  return __;  // operators
}
const double* dvec2:: data() const   {
  return __;
}
dvec2 dvec2::operator+(double s) const {
  return dvec2(
           x() + s,
           y() + s
         );
}

dvec2 dvec2::operator+(const dvec2& _) const {
  return dvec2(
           x() + _.x(),
           y() + _.y()
         );
}

dvec2& dvec2::operator+=(double s) {
  return *this = *this + s;
}

dvec2& dvec2::operator+=(const dvec2 v) {
  return *this = *this + v;
}

dvec2 dvec2::operator-(double s) const {
  return dvec2(
           x() - s,
           y() - s
         );
}

dvec2 dvec2::operator-(const dvec2& _) const {
  return dvec2(
           x() - _.x(),
           y() - _.y()
         );
}

dvec2& dvec2::operator-=(double s) {
  return *this = *this - s;
}

dvec2& dvec2::operator-=(const dvec2 v) {
  return *this = *this - v;
}

dvec2 dvec2::operator*(double s) const {
  return dvec2(
           x() * s,
           y() * s
         );
}

dvec2 dvec2::operator*(const dvec2& _) const {
  return dvec2(
           x() * _.x(),
           y() * _.y()
         );
}

dvec2& dvec2::operator*=(double s) {
  return *this = *this * s;
}

dvec2& dvec2::operator*=(const dvec2 v) {
  return *this = *this * v;
}

dvec2 dvec2::operator/(double s) const {
  return dvec2(
           x() / s,
           y() / s
         );
}

dvec2 dvec2::operator/(const dvec2& _) const {
  return dvec2(
           x() / _.x(),
           y() / _.y()
         );
}

dvec2& dvec2::operator/=(double s) {
  return *this = *this / s;
}

dvec2& dvec2::operator/=(const dvec2 v) {
  return *this = *this / v;
}

// unary +
dvec2 dvec2::operator+() const {
  return *this;
}

// const subscript
double dvec2:: operator[](int i) const   {
  i < 0 && rmr.die("dvec2.operator[]: negative index");
  i >= 2 && rmr.die("dvec2.operator[]: index too large");
  return __[i];
} // mutable subscript
double& dvec2:: operator[](int i)   {
  i < 0 && rmr.die("dvec2.operator[]: negative index");
  i >= 2 && rmr.die("dvec2.operator[]: index too large");
  return __[i];
} // iteration
const double* dvec2:: begin() const   {
  return data()         ;  // length and size
}
double* dvec2:: begin()         {
  return data()         ;
}
const double* dvec2:: end  () const   {
  return data() + 2;
}
double* dvec2:: end  ()         {
  return data() + 2;
}
size_t dvec2:: size() const   {
  return 2;  // sum
}
double dvec2:: sum() const   {
  return  x() +  y()  ;
} // unary -
dvec2 dvec2:: operator-() const   {
  return *this * -1.0;
} // equality
bool dvec2:: operator==(const dvec2& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  return true;
}
bool dvec2:: operator!=(const dvec2& v) const   {
  return !(*this == v);
}
dvec2 dvec2::random() {
  return random(0, 1);
}

dvec2 dvec2::random(double max) {
  return random(0, max);
}

dvec2 dvec2::random(double min, double max) {
  return dvec2( rmr.random(min, max), rmr.random(min, max));
}

double dvec2::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() );
}

// normalize
dvec2& dvec2::normalize() {
  double l = magnitude();
  l > 0 || rmr.die("dvec2.normalize: zero magnitude");
  return *this /= l;
}

// extend
dvec3 dvec2::extend(double s) const {
  return dvec3(
           x(),
           y(),
           s
         );
}

// hash
dvec2 dvec2:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 2;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    double((h >> bits * 0 & mask) / double(mask)),
    double((h >> bits * 1 & mask) / double(mask))
  };

} // from heading
dvec2 dvec2:: heading(double angle)   {
  return dvec2(rmr.cos(angle), rmr.sin(angle));
} // to heading
double dvec2:: heading()   {
  return rmr.atan2(y(), x());
} // dot
double dvec2:: dot(const dvec2& _)   {
  return  x() * _.x() +  y() * _.y()  ;
} // dot
// bits
dvec2 dvec2:: bits(int x)   {
  return dvec2(
           (x >> 0) & 1,
           (x >> 1) & 1
         );
}
ostream& operator<<(ostream& os, const dvec2& v) {
  return os << "("
         << v.x() << " "
         << v.y()
         << ")";
}
// no argument constructor
// whatever constructor
ivec2:: ivec2(whatever_t w)   { } // scalar component constructor
ivec2:: ivec2(
  int x,
  int y
)   : __{ x, y } {
} // single component constructor
ivec2:: ivec2(int s)   : __{ s, s } { } // pointer initializer
ivec2:: ivec2(int (&p)[2])   : __{
    p[0],   p[1]  } { }  // component accessors
int  ivec2:: x(   ) const   {
  return __[0];             // swizzles
}
int& ivec2:: x(   )         {
  return __[0];
}
ivec2& ivec2:: x(int s)         {
  __[0] = s;
  return *this;
}
int  ivec2:: y(   ) const   {
  return __[1];
}
int& ivec2:: y(   )         {
  return __[1];
}
ivec2& ivec2:: y(int s)         {
  __[1] = s;
  return *this;
}
int  ivec2:: r(   ) const   {
  return __[0];
}
int& ivec2:: r(   )         {
  return __[0];
}
ivec2& ivec2:: r(int s)         {
  __[0] = s;
  return *this;
}
int  ivec2:: g(   ) const   {
  return __[1];
}
int& ivec2:: g(   )         {
  return __[1];
}
ivec2& ivec2:: g(int s)         {
  __[1] = s;
  return *this;
}
int  ivec2:: s(   ) const   {
  return __[0];
}
int& ivec2:: s(   )         {
  return __[0];
}
ivec2& ivec2:: s(int s)         {
  __[0] = s;
  return *this;
}
int  ivec2:: t(   ) const   {
  return __[1];
}
int& ivec2:: t(   )         {
  return __[1];
}
ivec2& ivec2:: t(int s)         {
  __[1] = s;
  return *this;
}
// data pointers
int* ivec2:: data()         {
  return __;  // operators
}
const int* ivec2:: data() const   {
  return __;
}
ivec2 ivec2::operator+(int s) const {
  return ivec2(
           x() + s,
           y() + s
         );
}

ivec2 ivec2::operator+(const ivec2& _) const {
  return ivec2(
           x() + _.x(),
           y() + _.y()
         );
}

ivec2& ivec2::operator+=(int s) {
  return *this = *this + s;
}

ivec2& ivec2::operator+=(const ivec2 v) {
  return *this = *this + v;
}

ivec2 ivec2::operator-(int s) const {
  return ivec2(
           x() - s,
           y() - s
         );
}

ivec2 ivec2::operator-(const ivec2& _) const {
  return ivec2(
           x() - _.x(),
           y() - _.y()
         );
}

ivec2& ivec2::operator-=(int s) {
  return *this = *this - s;
}

ivec2& ivec2::operator-=(const ivec2 v) {
  return *this = *this - v;
}

ivec2 ivec2::operator*(int s) const {
  return ivec2(
           x() * s,
           y() * s
         );
}

ivec2 ivec2::operator*(const ivec2& _) const {
  return ivec2(
           x() * _.x(),
           y() * _.y()
         );
}

ivec2& ivec2::operator*=(int s) {
  return *this = *this * s;
}

ivec2& ivec2::operator*=(const ivec2 v) {
  return *this = *this * v;
}

ivec2 ivec2::operator/(int s) const {
  return ivec2(
           x() / s,
           y() / s
         );
}

ivec2 ivec2::operator/(const ivec2& _) const {
  return ivec2(
           x() / _.x(),
           y() / _.y()
         );
}

ivec2& ivec2::operator/=(int s) {
  return *this = *this / s;
}

ivec2& ivec2::operator/=(const ivec2 v) {
  return *this = *this / v;
}

// unary +
ivec2 ivec2::operator+() const {
  return *this;
}

// const subscript
int ivec2:: operator[](int i) const   {
  i < 0 && rmr.die("ivec2.operator[]: negative index");
  i >= 2 && rmr.die("ivec2.operator[]: index too large");
  return __[i];
} // mutable subscript
int& ivec2:: operator[](int i)   {
  i < 0 && rmr.die("ivec2.operator[]: negative index");
  i >= 2 && rmr.die("ivec2.operator[]: index too large");
  return __[i];
} // iteration
const int* ivec2:: begin() const   {
  return data()         ;  // length and size
}
int* ivec2:: begin()         {
  return data()         ;
}
const int* ivec2:: end  () const   {
  return data() + 2;
}
int* ivec2:: end  ()         {
  return data() + 2;
}
size_t ivec2:: size() const   {
  return 2;  // sum
}
int ivec2:: sum() const   {
  return  x() +  y()  ;
} // unary -
ivec2 ivec2:: operator-() const   {
  return *this * -1.0;
} // equality
bool ivec2:: operator==(const ivec2& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  return true;
}
bool ivec2:: operator!=(const ivec2& v) const   {
  return !(*this == v);
}
ivec2 ivec2::random() {
  return random(0, 1);
}

ivec2 ivec2::random(int max) {
  return random(0, max);
}

ivec2 ivec2::random(int min, int max) {
  return ivec2( rmr.random(min, max), rmr.random(min, max));
}

int ivec2::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() );
}

// normalize
ivec2& ivec2::normalize() {
  int l = magnitude();
  l > 0 || rmr.die("ivec2.normalize: zero magnitude");
  return *this /= l;
}

// extend
ivec3 ivec2::extend(int s) const {
  return ivec3(
           x(),
           y(),
           s
         );
}

// hash
ivec2 ivec2:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 2;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    int((h >> bits * 0 & mask) / int(mask)),
    int((h >> bits * 1 & mask) / int(mask))
  };

} // from heading
// to heading
// dot
int ivec2:: dot(const ivec2& _)   {
  return  x() * _.x() +  y() * _.y()  ;
} // dot
// bits
ivec2 ivec2:: bits(int x)   {
  return ivec2(
           (x >> 0) & 1,
           (x >> 1) & 1
         );
}
ostream& operator<<(ostream& os, const ivec2& v) {
  return os << "("
         << v.x() << " "
         << v.y()
         << ")";
}
// no argument constructor
// whatever constructor
uvec2:: uvec2(whatever_t w)   { } // scalar component constructor
uvec2:: uvec2(
  uint x,
  uint y
)   : __{ x, y } {
} // single component constructor
uvec2:: uvec2(uint s)   : __{ s, s } { } // pointer initializer
uvec2:: uvec2(uint (&p)[2])   : __{
    p[0],   p[1]  } { }  // component accessors
uint  uvec2:: x(   ) const   {
  return __[0];             // swizzles
}
uint& uvec2:: x(   )         {
  return __[0];
}
uvec2& uvec2:: x(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec2:: y(   ) const   {
  return __[1];
}
uint& uvec2:: y(   )         {
  return __[1];
}
uvec2& uvec2:: y(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec2:: r(   ) const   {
  return __[0];
}
uint& uvec2:: r(   )         {
  return __[0];
}
uvec2& uvec2:: r(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec2:: g(   ) const   {
  return __[1];
}
uint& uvec2:: g(   )         {
  return __[1];
}
uvec2& uvec2:: g(uint s)         {
  __[1] = s;
  return *this;
}
uint  uvec2:: s(   ) const   {
  return __[0];
}
uint& uvec2:: s(   )         {
  return __[0];
}
uvec2& uvec2:: s(uint s)         {
  __[0] = s;
  return *this;
}
uint  uvec2:: t(   ) const   {
  return __[1];
}
uint& uvec2:: t(   )         {
  return __[1];
}
uvec2& uvec2:: t(uint s)         {
  __[1] = s;
  return *this;
}
// data pointers
uint* uvec2:: data()         {
  return __;  // operators
}
const uint* uvec2:: data() const   {
  return __;
}
uvec2 uvec2::operator+(uint s) const {
  return uvec2(
           x() + s,
           y() + s
         );
}

uvec2 uvec2::operator+(const uvec2& _) const {
  return uvec2(
           x() + _.x(),
           y() + _.y()
         );
}

uvec2& uvec2::operator+=(uint s) {
  return *this = *this + s;
}

uvec2& uvec2::operator+=(const uvec2 v) {
  return *this = *this + v;
}

uvec2 uvec2::operator-(uint s) const {
  return uvec2(
           x() - s,
           y() - s
         );
}

uvec2 uvec2::operator-(const uvec2& _) const {
  return uvec2(
           x() - _.x(),
           y() - _.y()
         );
}

uvec2& uvec2::operator-=(uint s) {
  return *this = *this - s;
}

uvec2& uvec2::operator-=(const uvec2 v) {
  return *this = *this - v;
}

uvec2 uvec2::operator*(uint s) const {
  return uvec2(
           x() * s,
           y() * s
         );
}

uvec2 uvec2::operator*(const uvec2& _) const {
  return uvec2(
           x() * _.x(),
           y() * _.y()
         );
}

uvec2& uvec2::operator*=(uint s) {
  return *this = *this * s;
}

uvec2& uvec2::operator*=(const uvec2 v) {
  return *this = *this * v;
}

uvec2 uvec2::operator/(uint s) const {
  return uvec2(
           x() / s,
           y() / s
         );
}

uvec2 uvec2::operator/(const uvec2& _) const {
  return uvec2(
           x() / _.x(),
           y() / _.y()
         );
}

uvec2& uvec2::operator/=(uint s) {
  return *this = *this / s;
}

uvec2& uvec2::operator/=(const uvec2 v) {
  return *this = *this / v;
}

// unary +
uvec2 uvec2::operator+() const {
  return *this;
}

// const subscript
uint uvec2:: operator[](int i) const   {
  i < 0 && rmr.die("uvec2.operator[]: negative index");
  i >= 2 && rmr.die("uvec2.operator[]: index too large");
  return __[i];
} // mutable subscript
uint& uvec2:: operator[](int i)   {
  i < 0 && rmr.die("uvec2.operator[]: negative index");
  i >= 2 && rmr.die("uvec2.operator[]: index too large");
  return __[i];
} // iteration
const uint* uvec2:: begin() const   {
  return data()         ;  // length and size
}
uint* uvec2:: begin()         {
  return data()         ;
}
const uint* uvec2:: end  () const   {
  return data() + 2;
}
uint* uvec2:: end  ()         {
  return data() + 2;
}
size_t uvec2:: size() const   {
  return 2;  // sum
}
uint uvec2:: sum() const   {
  return  x() +  y()  ;
} // unary -
// equality
bool uvec2:: operator==(const uvec2& v) const   {
  if (x() != v.x()) return false;
  if (y() != v.y()) return false;
  return true;
}
bool uvec2:: operator!=(const uvec2& v) const   {
  return !(*this == v);
}
uvec2 uvec2::random() {
  return random(0, 1);
}

uvec2 uvec2::random(uint max) {
  return random(0, max);
}

uvec2 uvec2::random(uint min, uint max) {
  return uvec2( rmr.random(min, max), rmr.random(min, max));
}

uint uvec2::magnitude() const {
  return rmr.sqrt( x() * x() + y() * y() );
}

// normalize
uvec2& uvec2::normalize() {
  uint l = magnitude();
  l > 0 || rmr.die("uvec2.normalize: zero magnitude");
  return *this /= l;
}

// extend
uvec3 uvec2::extend(uint s) const {
  return uvec3(
           x(),
           y(),
           s
         );
}

// hash
uvec2 uvec2:: hash(hash_t h)   {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / 2;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);

  return {
    uint((h >> bits * 0 & mask) / uint(mask)),
    uint((h >> bits * 1 & mask) / uint(mask))
  };

} // from heading
// to heading
// dot
uint uvec2:: dot(const uvec2& _)   {
  return  x() * _.x() +  y() * _.y()  ;
} // dot
// bits
uvec2 uvec2:: bits(int x)   {
  return uvec2(
           (x >> 0) & 1,
           (x >> 1) & 1
         );
}
ostream& operator<<(ostream& os, const uvec2& v) {
  return os << "("
         << v.x() << " "
         << v.y()
         << ")";
}
// matrices
// no argument constructor
// whatever constructor
dmat4:: dmat4(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
dmat4:: dmat4(
  double s00,
  double s10,
  double s20,
  double s30,
  double s01,
  double s11,
  double s21,
  double s31,
  double s02,
  double s12,
  double s22,
  double s32,
  double s03,
  double s13,
  double s23,
  double s33
)   {
  __[0] = {
    s00,
    s10,
    s20,
    s30
  };
  __[1] = {
    s01,
    s11,
    s21,
    s31
  };
  __[2] = {
    s02,
    s12,
    s22,
    s32
  };
  __[3] = {
    s03,
    s13,
    s23,
    s33
  };
}
const dmat4& dmat4:: identity()   {
  static dmat4 i {
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    1
  };
  return i;
}; // data pointers
dvec4* dmat4:: data()         {
  return __;  // floats
}
const dvec4* dmat4:: data() const   {
  return __;
}
double* dmat4:: scalars()         {
  return __[0].data();
}
const double* dmat4:: scalars() const   {
  return __[0].data();
}
dvec4& dmat4:: operator[](int i)   {
  i < 0    && rmr.die("dmat4.operator[]: negative index");
  i >= 4 && rmr.die("dmat4.operator[]: index too large");
  return __[i];
}
const dvec4& dmat4:: operator[](int i) const   {
  i < 0    && rmr.die("dmat4.operator[]: negative index");
  i >= 4 && rmr.die("dmat4.operator[]: index too large");
  return __[i];
}
dmat4 dmat4:: operator*(const dmat4& m) const   {
  dmat4 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][0] += (*this)[2][0] * m[0][2];
  temp[0][0] += (*this)[3][0] * m[0][3];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[0][1] += (*this)[2][1] * m[0][2];
  temp[0][1] += (*this)[3][1] * m[0][3];
  temp[0][2] += (*this)[0][2] * m[0][0];
  temp[0][2] += (*this)[1][2] * m[0][1];
  temp[0][2] += (*this)[2][2] * m[0][2];
  temp[0][2] += (*this)[3][2] * m[0][3];
  temp[0][3] += (*this)[0][3] * m[0][0];
  temp[0][3] += (*this)[1][3] * m[0][1];
  temp[0][3] += (*this)[2][3] * m[0][2];
  temp[0][3] += (*this)[3][3] * m[0][3];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][0] += (*this)[2][0] * m[1][2];
  temp[1][0] += (*this)[3][0] * m[1][3];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  temp[1][1] += (*this)[2][1] * m[1][2];
  temp[1][1] += (*this)[3][1] * m[1][3];
  temp[1][2] += (*this)[0][2] * m[1][0];
  temp[1][2] += (*this)[1][2] * m[1][1];
  temp[1][2] += (*this)[2][2] * m[1][2];
  temp[1][2] += (*this)[3][2] * m[1][3];
  temp[1][3] += (*this)[0][3] * m[1][0];
  temp[1][3] += (*this)[1][3] * m[1][1];
  temp[1][3] += (*this)[2][3] * m[1][2];
  temp[1][3] += (*this)[3][3] * m[1][3];
  temp[2][0] += (*this)[0][0] * m[2][0];
  temp[2][0] += (*this)[1][0] * m[2][1];
  temp[2][0] += (*this)[2][0] * m[2][2];
  temp[2][0] += (*this)[3][0] * m[2][3];
  temp[2][1] += (*this)[0][1] * m[2][0];
  temp[2][1] += (*this)[1][1] * m[2][1];
  temp[2][1] += (*this)[2][1] * m[2][2];
  temp[2][1] += (*this)[3][1] * m[2][3];
  temp[2][2] += (*this)[0][2] * m[2][0];
  temp[2][2] += (*this)[1][2] * m[2][1];
  temp[2][2] += (*this)[2][2] * m[2][2];
  temp[2][2] += (*this)[3][2] * m[2][3];
  temp[2][3] += (*this)[0][3] * m[2][0];
  temp[2][3] += (*this)[1][3] * m[2][1];
  temp[2][3] += (*this)[2][3] * m[2][2];
  temp[2][3] += (*this)[3][3] * m[2][3];
  temp[3][0] += (*this)[0][0] * m[3][0];
  temp[3][0] += (*this)[1][0] * m[3][1];
  temp[3][0] += (*this)[2][0] * m[3][2];
  temp[3][0] += (*this)[3][0] * m[3][3];
  temp[3][1] += (*this)[0][1] * m[3][0];
  temp[3][1] += (*this)[1][1] * m[3][1];
  temp[3][1] += (*this)[2][1] * m[3][2];
  temp[3][1] += (*this)[3][1] * m[3][3];
  temp[3][2] += (*this)[0][2] * m[3][0];
  temp[3][2] += (*this)[1][2] * m[3][1];
  temp[3][2] += (*this)[2][2] * m[3][2];
  temp[3][2] += (*this)[3][2] * m[3][3];
  temp[3][3] += (*this)[0][3] * m[3][0];
  temp[3][3] += (*this)[1][3] * m[3][1];
  temp[3][3] += (*this)[2][3] * m[3][2];
  temp[3][3] += (*this)[3][3] * m[3][3];
  return temp;
}
dmat4& dmat4:: operator*=(const dmat4& m)   {
  return *this = *this * m;
} // translation
dmat4& dmat4:: translate(const dvec3& v)   {
  dmat4 temp = dmat4::identity();
  temp.column(4 - 1) = v.extend(1.0);
  *this *= temp;
  return *this;
}
dmat4& dmat4:: translate(double x, double y, double z)   {
  dmat4 temp = dmat4::identity();
  temp.column(4 - 1) = dvec4{
    x,
    y,
    z,
    1
  };
  *this *= temp;
  return *this;
}
dmat4& dmat4:: translate_x(double x)   {
  dvec3 v;
  v.x() = x;
  return translate(v);
}
dmat4& dmat4:: translate_y(double y)   {
  dvec3 v;
  v.y() = y;
  return translate(v);
}
dmat4& dmat4:: translate_z(double z)   {
  dvec3 v;
  v.z() = z;
  return translate(v);
} // rotate
dmat4& dmat4:: rotate_x(double angle)   {
  dvec3 v;
  v.x() = 1.0;
  return rotate(v, angle);
}
dmat4& dmat4:: rotate_y(double angle)   {
  dvec3 v;
  v.y() = 1.0;
  return rotate(v, angle);
}
dmat4& dmat4:: rotate_z(double angle)   {
  dvec3 v;
  v.z() = 1.0;
  return rotate(v, angle);
}
dmat4& dmat4:: rotate(const dvec3& v, double angle)   {
  dmat4 rotation_matrix = dmat4::from_aa(v, angle);
  *this = *this * rotation_matrix;
  return *this;
}
dmat4& dmat4:: rotate(double x, double y, double z, double angle)   {
  dmat4 rotation_matrix = dmat4::from_aa(
                            dvec3(
                              x,
                              y,
                              z
                            ),
                            angle);
  *this = *this * rotation_matrix;
  return *this;
}
dmat4 dmat4:: from_aa(const dvec3& v, double theta)   {
  float c = rmr.cos(theta);
  float d = 1 - c;
  float s = rmr.sin(theta);
  float ax = v.x();
  float ay = v.y();
  float az = v.z();

  return {
    ax * ax * d + c,
    ax * ay * d + az * s,
    ax * az * d - ay * s,
    0,
    ax * ay * d - az * s,
    ay * ay * d + c,
    ay * az * d + ax * s,
    0,
    ax * az * d + ay * s,
    ay * az * d - ax * s,
    az * az * d + c,
    0,

    0, 0, 0, 1
  };
}
const dvec4& dmat4:: column(int i) const   {
  return (*this)[i];
}
dvec4& dmat4:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(dmat4) == sizeof(double) * 4 * 4, "dmat4: unexpected size"    );
static_assert(!std::is_polymorphic<dmat4>::value,     "dmat4: non-polymorphic"    );
static_assert(std::is_standard_layout<dmat4>::value,  "dmat4: non-standard layout");
static_assert(std::is_literal_type<dmat4>::value,     "dmat4: non-literal"        );

ostream& operator<<(ostream& os, const dmat4& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << m[2][0];
  os << " ";
  os << m[3][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << m[2][1];
  os << " ";
  os << m[3][1];
  os << " ";
  os << "\n";
  os << m[0][2];
  os << " ";
  os << m[1][2];
  os << " ";
  os << m[2][2];
  os << " ";
  os << m[3][2];
  os << " ";
  os << "\n";
  os << m[0][3];
  os << " ";
  os << m[1][3];
  os << " ";
  os << m[2][3];
  os << " ";
  os << m[3][3];
  os << " ";
  os << "\n";
  return os;
}

// no argument constructor
// whatever constructor
mat4:: mat4(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
mat4:: mat4(
  float s00,
  float s10,
  float s20,
  float s30,
  float s01,
  float s11,
  float s21,
  float s31,
  float s02,
  float s12,
  float s22,
  float s32,
  float s03,
  float s13,
  float s23,
  float s33
)   {
  __[0] = {
    s00,
    s10,
    s20,
    s30
  };
  __[1] = {
    s01,
    s11,
    s21,
    s31
  };
  __[2] = {
    s02,
    s12,
    s22,
    s32
  };
  __[3] = {
    s03,
    s13,
    s23,
    s33
  };
}
const mat4& mat4:: identity()   {
  static mat4 i {
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    1
  };
  return i;
}; // data pointers
vec4* mat4:: data()         {
  return __;  // floats
}
const vec4* mat4:: data() const   {
  return __;
}
float* mat4:: scalars()         {
  return __[0].data();
}
const float* mat4:: scalars() const   {
  return __[0].data();
}
vec4& mat4:: operator[](int i)   {
  i < 0    && rmr.die("mat4.operator[]: negative index");
  i >= 4 && rmr.die("mat4.operator[]: index too large");
  return __[i];
}
const vec4& mat4:: operator[](int i) const   {
  i < 0    && rmr.die("mat4.operator[]: negative index");
  i >= 4 && rmr.die("mat4.operator[]: index too large");
  return __[i];
}
mat4 mat4:: operator*(const mat4& m) const   {
  mat4 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][0] += (*this)[2][0] * m[0][2];
  temp[0][0] += (*this)[3][0] * m[0][3];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[0][1] += (*this)[2][1] * m[0][2];
  temp[0][1] += (*this)[3][1] * m[0][3];
  temp[0][2] += (*this)[0][2] * m[0][0];
  temp[0][2] += (*this)[1][2] * m[0][1];
  temp[0][2] += (*this)[2][2] * m[0][2];
  temp[0][2] += (*this)[3][2] * m[0][3];
  temp[0][3] += (*this)[0][3] * m[0][0];
  temp[0][3] += (*this)[1][3] * m[0][1];
  temp[0][3] += (*this)[2][3] * m[0][2];
  temp[0][3] += (*this)[3][3] * m[0][3];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][0] += (*this)[2][0] * m[1][2];
  temp[1][0] += (*this)[3][0] * m[1][3];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  temp[1][1] += (*this)[2][1] * m[1][2];
  temp[1][1] += (*this)[3][1] * m[1][3];
  temp[1][2] += (*this)[0][2] * m[1][0];
  temp[1][2] += (*this)[1][2] * m[1][1];
  temp[1][2] += (*this)[2][2] * m[1][2];
  temp[1][2] += (*this)[3][2] * m[1][3];
  temp[1][3] += (*this)[0][3] * m[1][0];
  temp[1][3] += (*this)[1][3] * m[1][1];
  temp[1][3] += (*this)[2][3] * m[1][2];
  temp[1][3] += (*this)[3][3] * m[1][3];
  temp[2][0] += (*this)[0][0] * m[2][0];
  temp[2][0] += (*this)[1][0] * m[2][1];
  temp[2][0] += (*this)[2][0] * m[2][2];
  temp[2][0] += (*this)[3][0] * m[2][3];
  temp[2][1] += (*this)[0][1] * m[2][0];
  temp[2][1] += (*this)[1][1] * m[2][1];
  temp[2][1] += (*this)[2][1] * m[2][2];
  temp[2][1] += (*this)[3][1] * m[2][3];
  temp[2][2] += (*this)[0][2] * m[2][0];
  temp[2][2] += (*this)[1][2] * m[2][1];
  temp[2][2] += (*this)[2][2] * m[2][2];
  temp[2][2] += (*this)[3][2] * m[2][3];
  temp[2][3] += (*this)[0][3] * m[2][0];
  temp[2][3] += (*this)[1][3] * m[2][1];
  temp[2][3] += (*this)[2][3] * m[2][2];
  temp[2][3] += (*this)[3][3] * m[2][3];
  temp[3][0] += (*this)[0][0] * m[3][0];
  temp[3][0] += (*this)[1][0] * m[3][1];
  temp[3][0] += (*this)[2][0] * m[3][2];
  temp[3][0] += (*this)[3][0] * m[3][3];
  temp[3][1] += (*this)[0][1] * m[3][0];
  temp[3][1] += (*this)[1][1] * m[3][1];
  temp[3][1] += (*this)[2][1] * m[3][2];
  temp[3][1] += (*this)[3][1] * m[3][3];
  temp[3][2] += (*this)[0][2] * m[3][0];
  temp[3][2] += (*this)[1][2] * m[3][1];
  temp[3][2] += (*this)[2][2] * m[3][2];
  temp[3][2] += (*this)[3][2] * m[3][3];
  temp[3][3] += (*this)[0][3] * m[3][0];
  temp[3][3] += (*this)[1][3] * m[3][1];
  temp[3][3] += (*this)[2][3] * m[3][2];
  temp[3][3] += (*this)[3][3] * m[3][3];
  return temp;
}
mat4& mat4:: operator*=(const mat4& m)   {
  return *this = *this * m;
} // translation
mat4& mat4:: translate(const vec3& v)   {
  mat4 temp = mat4::identity();
  temp.column(4 - 1) = v.extend(1.0);
  *this *= temp;
  return *this;
}
mat4& mat4:: translate(float x, float y, float z)   {
  mat4 temp = mat4::identity();
  temp.column(4 - 1) = vec4{
    x,
    y,
    z,
    1
  };
  *this *= temp;
  return *this;
}
mat4& mat4:: translate_x(float x)   {
  vec3 v;
  v.x() = x;
  return translate(v);
}
mat4& mat4:: translate_y(float y)   {
  vec3 v;
  v.y() = y;
  return translate(v);
}
mat4& mat4:: translate_z(float z)   {
  vec3 v;
  v.z() = z;
  return translate(v);
} // rotate
mat4& mat4:: rotate_x(float angle)   {
  vec3 v;
  v.x() = 1.0;
  return rotate(v, angle);
}
mat4& mat4:: rotate_y(float angle)   {
  vec3 v;
  v.y() = 1.0;
  return rotate(v, angle);
}
mat4& mat4:: rotate_z(float angle)   {
  vec3 v;
  v.z() = 1.0;
  return rotate(v, angle);
}
mat4& mat4:: rotate(const vec3& v, float angle)   {
  mat4 rotation_matrix = mat4::from_aa(v, angle);
  *this = *this * rotation_matrix;
  return *this;
}
mat4& mat4:: rotate(float x, float y, float z, float angle)   {
  mat4 rotation_matrix = mat4::from_aa(
                           vec3(
                             x,
                             y,
                             z
                           ),
                           angle);
  *this = *this * rotation_matrix;
  return *this;
}
mat4 mat4:: from_aa(const vec3& v, float theta)   {
  float c = rmr.cos(theta);
  float d = 1 - c;
  float s = rmr.sin(theta);
  float ax = v.x();
  float ay = v.y();
  float az = v.z();

  return {
    ax * ax * d + c,
    ax * ay * d + az * s,
    ax * az * d - ay * s,
    0,
    ax * ay * d - az * s,
    ay * ay * d + c,
    ay * az * d + ax * s,
    0,
    ax * az * d + ay * s,
    ay * az * d - ax * s,
    az * az * d + c,
    0,

    0, 0, 0, 1
  };
}
const vec4& mat4:: column(int i) const   {
  return (*this)[i];
}
vec4& mat4:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(mat4) == sizeof(float) * 4 * 4, "mat4: unexpected size"    );
static_assert(!std::is_polymorphic<mat4>::value,     "mat4: non-polymorphic"    );
static_assert(std::is_standard_layout<mat4>::value,  "mat4: non-standard layout");
static_assert(std::is_literal_type<mat4>::value,     "mat4: non-literal"        );

ostream& operator<<(ostream& os, const mat4& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << m[2][0];
  os << " ";
  os << m[3][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << m[2][1];
  os << " ";
  os << m[3][1];
  os << " ";
  os << "\n";
  os << m[0][2];
  os << " ";
  os << m[1][2];
  os << " ";
  os << m[2][2];
  os << " ";
  os << m[3][2];
  os << " ";
  os << "\n";
  os << m[0][3];
  os << " ";
  os << m[1][3];
  os << " ";
  os << m[2][3];
  os << " ";
  os << m[3][3];
  os << " ";
  os << "\n";
  return os;
}

// no argument constructor
// whatever constructor
dmat3:: dmat3(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
dmat3:: dmat3(
  double s00,
  double s10,
  double s20,
  double s01,
  double s11,
  double s21,
  double s02,
  double s12,
  double s22
)   {
  __[0] = {
    s00,
    s10,
    s20
  };
  __[1] = {
    s01,
    s11,
    s21
  };
  __[2] = {
    s02,
    s12,
    s22
  };
}
const dmat3& dmat3:: identity()   {
  static dmat3 i {
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1
  };
  return i;
}; // data pointers
dvec3* dmat3:: data()         {
  return __;  // floats
}
const dvec3* dmat3:: data() const   {
  return __;
}
double* dmat3:: scalars()         {
  return __[0].data();
}
const double* dmat3:: scalars() const   {
  return __[0].data();
}
dvec3& dmat3:: operator[](int i)   {
  i < 0    && rmr.die("dmat3.operator[]: negative index");
  i >= 3 && rmr.die("dmat3.operator[]: index too large");
  return __[i];
}
const dvec3& dmat3:: operator[](int i) const   {
  i < 0    && rmr.die("dmat3.operator[]: negative index");
  i >= 3 && rmr.die("dmat3.operator[]: index too large");
  return __[i];
}
dmat3 dmat3:: operator*(const dmat3& m) const   {
  dmat3 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][0] += (*this)[2][0] * m[0][2];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[0][1] += (*this)[2][1] * m[0][2];
  temp[0][2] += (*this)[0][2] * m[0][0];
  temp[0][2] += (*this)[1][2] * m[0][1];
  temp[0][2] += (*this)[2][2] * m[0][2];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][0] += (*this)[2][0] * m[1][2];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  temp[1][1] += (*this)[2][1] * m[1][2];
  temp[1][2] += (*this)[0][2] * m[1][0];
  temp[1][2] += (*this)[1][2] * m[1][1];
  temp[1][2] += (*this)[2][2] * m[1][2];
  temp[2][0] += (*this)[0][0] * m[2][0];
  temp[2][0] += (*this)[1][0] * m[2][1];
  temp[2][0] += (*this)[2][0] * m[2][2];
  temp[2][1] += (*this)[0][1] * m[2][0];
  temp[2][1] += (*this)[1][1] * m[2][1];
  temp[2][1] += (*this)[2][1] * m[2][2];
  temp[2][2] += (*this)[0][2] * m[2][0];
  temp[2][2] += (*this)[1][2] * m[2][1];
  temp[2][2] += (*this)[2][2] * m[2][2];
  return temp;
}
dmat3& dmat3:: operator*=(const dmat3& m)   {
  return *this = *this * m;
} // translation
dmat3& dmat3:: translate(const dvec2& v)   {
  dmat3 temp = dmat3::identity();
  temp.column(3 - 1) = v.extend(1.0);
  *this *= temp;
  return *this;
}
dmat3& dmat3:: translate(double x, double y)   {
  dmat3 temp = dmat3::identity();
  temp.column(3 - 1) = dvec3{
    x,
    y,
    1
  };
  *this *= temp;
  return *this;
}
dmat3& dmat3:: translate_x(double x)   {
  dvec2 v;
  v.x() = x;
  return translate(v);
}
dmat3& dmat3:: translate_y(double y)   {
  dvec2 v;
  v.y() = y;
  return translate(v);
} // rotate
dmat3& dmat3:: rotate_x(double angle)   {
  dvec3 v;
  v.x() = 1.0;
  return rotate(v, angle);
}
dmat3& dmat3:: rotate_y(double angle)   {
  dvec3 v;
  v.y() = 1.0;
  return rotate(v, angle);
}
dmat3& dmat3:: rotate(const dvec3& v, double angle)   {
  dmat3 rotation_matrix = dmat3::from_aa(v, angle);
  *this = *this * rotation_matrix;
  return *this;
}
dmat3& dmat3:: rotate(double x, double y, double z, double angle)   {
  dmat3 rotation_matrix = dmat3::from_aa(
                            dvec3(
                              x,
                              y,
                              z
                            ),
                            angle);
  *this = *this * rotation_matrix;
  return *this;
}
dmat3 dmat3:: from_aa(const dvec3& v, double theta)   {
  float c = rmr.cos(theta);
  float d = 1 - c;
  float s = rmr.sin(theta);
  float ax = v.x();
  float ay = v.y();
  float az = v.z();

  return {
    ax * ax * d + c,
    ax * ay * d + az * s,
    ax * az * d - ay * s,
    ax * ay * d - az * s,
    ay * ay * d + c,
    ay * az * d + ax * s,
    ax * az * d + ay * s,
    ay * az * d - ax * s,
    az * az * d + c,
  };
}
const dvec3& dmat3:: column(int i) const   {
  return (*this)[i];
}
dvec3& dmat3:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(dmat3) == sizeof(double) * 3 * 3, "dmat3: unexpected size"    );
static_assert(!std::is_polymorphic<dmat3>::value,     "dmat3: non-polymorphic"    );
static_assert(std::is_standard_layout<dmat3>::value,  "dmat3: non-standard layout");
static_assert(std::is_literal_type<dmat3>::value,     "dmat3: non-literal"        );

ostream& operator<<(ostream& os, const dmat3& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << m[2][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << m[2][1];
  os << " ";
  os << "\n";
  os << m[0][2];
  os << " ";
  os << m[1][2];
  os << " ";
  os << m[2][2];
  os << " ";
  os << "\n";
  return os;
}

// no argument constructor
// whatever constructor
mat3:: mat3(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
mat3:: mat3(
  float s00,
  float s10,
  float s20,
  float s01,
  float s11,
  float s21,
  float s02,
  float s12,
  float s22
)   {
  __[0] = {
    s00,
    s10,
    s20
  };
  __[1] = {
    s01,
    s11,
    s21
  };
  __[2] = {
    s02,
    s12,
    s22
  };
}
const mat3& mat3:: identity()   {
  static mat3 i {
    1,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    1
  };
  return i;
}; // data pointers
vec3* mat3:: data()         {
  return __;  // floats
}
const vec3* mat3:: data() const   {
  return __;
}
float* mat3:: scalars()         {
  return __[0].data();
}
const float* mat3:: scalars() const   {
  return __[0].data();
}
vec3& mat3:: operator[](int i)   {
  i < 0    && rmr.die("mat3.operator[]: negative index");
  i >= 3 && rmr.die("mat3.operator[]: index too large");
  return __[i];
}
const vec3& mat3:: operator[](int i) const   {
  i < 0    && rmr.die("mat3.operator[]: negative index");
  i >= 3 && rmr.die("mat3.operator[]: index too large");
  return __[i];
}
mat3 mat3:: operator*(const mat3& m) const   {
  mat3 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][0] += (*this)[2][0] * m[0][2];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[0][1] += (*this)[2][1] * m[0][2];
  temp[0][2] += (*this)[0][2] * m[0][0];
  temp[0][2] += (*this)[1][2] * m[0][1];
  temp[0][2] += (*this)[2][2] * m[0][2];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][0] += (*this)[2][0] * m[1][2];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  temp[1][1] += (*this)[2][1] * m[1][2];
  temp[1][2] += (*this)[0][2] * m[1][0];
  temp[1][2] += (*this)[1][2] * m[1][1];
  temp[1][2] += (*this)[2][2] * m[1][2];
  temp[2][0] += (*this)[0][0] * m[2][0];
  temp[2][0] += (*this)[1][0] * m[2][1];
  temp[2][0] += (*this)[2][0] * m[2][2];
  temp[2][1] += (*this)[0][1] * m[2][0];
  temp[2][1] += (*this)[1][1] * m[2][1];
  temp[2][1] += (*this)[2][1] * m[2][2];
  temp[2][2] += (*this)[0][2] * m[2][0];
  temp[2][2] += (*this)[1][2] * m[2][1];
  temp[2][2] += (*this)[2][2] * m[2][2];
  return temp;
}
mat3& mat3:: operator*=(const mat3& m)   {
  return *this = *this * m;
} // translation
mat3& mat3:: translate(const vec2& v)   {
  mat3 temp = mat3::identity();
  temp.column(3 - 1) = v.extend(1.0);
  *this *= temp;
  return *this;
}
mat3& mat3:: translate(float x, float y)   {
  mat3 temp = mat3::identity();
  temp.column(3 - 1) = vec3{
    x,
    y,
    1
  };
  *this *= temp;
  return *this;
}
mat3& mat3:: translate_x(float x)   {
  vec2 v;
  v.x() = x;
  return translate(v);
}
mat3& mat3:: translate_y(float y)   {
  vec2 v;
  v.y() = y;
  return translate(v);
} // rotate
mat3& mat3:: rotate_x(float angle)   {
  vec3 v;
  v.x() = 1.0;
  return rotate(v, angle);
}
mat3& mat3:: rotate_y(float angle)   {
  vec3 v;
  v.y() = 1.0;
  return rotate(v, angle);
}
mat3& mat3:: rotate(const vec3& v, float angle)   {
  mat3 rotation_matrix = mat3::from_aa(v, angle);
  *this = *this * rotation_matrix;
  return *this;
}
mat3& mat3:: rotate(float x, float y, float z, float angle)   {
  mat3 rotation_matrix = mat3::from_aa(
                           vec3(
                             x,
                             y,
                             z
                           ),
                           angle);
  *this = *this * rotation_matrix;
  return *this;
}
mat3 mat3:: from_aa(const vec3& v, float theta)   {
  float c = rmr.cos(theta);
  float d = 1 - c;
  float s = rmr.sin(theta);
  float ax = v.x();
  float ay = v.y();
  float az = v.z();

  return {
    ax * ax * d + c,
    ax * ay * d + az * s,
    ax * az * d - ay * s,
    ax * ay * d - az * s,
    ay * ay * d + c,
    ay * az * d + ax * s,
    ax * az * d + ay * s,
    ay * az * d - ax * s,
    az * az * d + c,
  };
}
const vec3& mat3:: column(int i) const   {
  return (*this)[i];
}
vec3& mat3:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(mat3) == sizeof(float) * 3 * 3, "mat3: unexpected size"    );
static_assert(!std::is_polymorphic<mat3>::value,     "mat3: non-polymorphic"    );
static_assert(std::is_standard_layout<mat3>::value,  "mat3: non-standard layout");
static_assert(std::is_literal_type<mat3>::value,     "mat3: non-literal"        );

ostream& operator<<(ostream& os, const mat3& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << m[2][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << m[2][1];
  os << " ";
  os << "\n";
  os << m[0][2];
  os << " ";
  os << m[1][2];
  os << " ";
  os << m[2][2];
  os << " ";
  os << "\n";
  return os;
}

// no argument constructor
// whatever constructor
dmat2:: dmat2(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
dmat2:: dmat2(
  double s00,
  double s10,
  double s01,
  double s11
)   {
  __[0] = {
    s00,
    s10
  };
  __[1] = {
    s01,
    s11
  };
}
const dmat2& dmat2:: identity()   {
  static dmat2 i {
    1,
    0,
    0,
    1
  };
  return i;
}; // data pointers
dvec2* dmat2:: data()         {
  return __;  // floats
}
const dvec2* dmat2:: data() const   {
  return __;
}
double* dmat2:: scalars()         {
  return __[0].data();
}
const double* dmat2:: scalars() const   {
  return __[0].data();
}
dvec2& dmat2:: operator[](int i)   {
  i < 0    && rmr.die("dmat2.operator[]: negative index");
  i >= 2 && rmr.die("dmat2.operator[]: index too large");
  return __[i];
}
const dvec2& dmat2:: operator[](int i) const   {
  i < 0    && rmr.die("dmat2.operator[]: negative index");
  i >= 2 && rmr.die("dmat2.operator[]: index too large");
  return __[i];
}
dmat2 dmat2:: operator*(const dmat2& m) const   {
  dmat2 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  return temp;
}
dmat2& dmat2:: operator*=(const dmat2& m)   {
  return *this = *this * m;
} // translation
// rotate
// dim == 2
dmat2 dmat2:: from_angle(double theta)   {
  return dmat2(
           rmr.cos(theta), -rmr.sin(theta),
           rmr.sin(theta),  rmr.cos(theta)
         );
}
const dvec2& dmat2:: column(int i) const   {
  return (*this)[i];
}
dvec2& dmat2:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(dmat2) == sizeof(double) * 2 * 2, "dmat2: unexpected size"    );
static_assert(!std::is_polymorphic<dmat2>::value,     "dmat2: non-polymorphic"    );
static_assert(std::is_standard_layout<dmat2>::value,  "dmat2: non-standard layout");
static_assert(std::is_literal_type<dmat2>::value,     "dmat2: non-literal"        );

ostream& operator<<(ostream& os, const dmat2& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << "\n";
  return os;
}

// no argument constructor
// whatever constructor
mat2:: mat2(whatever_t w)   : __{ {rmr.whatever()}, {rmr.whatever()} } { } // component constructor
mat2:: mat2(
  float s00,
  float s10,
  float s01,
  float s11
)   {
  __[0] = {
    s00,
    s10
  };
  __[1] = {
    s01,
    s11
  };
}
const mat2& mat2:: identity()   {
  static mat2 i {
    1,
    0,
    0,
    1
  };
  return i;
}; // data pointers
vec2* mat2:: data()         {
  return __;  // floats
}
const vec2* mat2:: data() const   {
  return __;
}
float* mat2:: scalars()         {
  return __[0].data();
}
const float* mat2:: scalars() const   {
  return __[0].data();
}
vec2& mat2:: operator[](int i)   {
  i < 0    && rmr.die("mat2.operator[]: negative index");
  i >= 2 && rmr.die("mat2.operator[]: index too large");
  return __[i];
}
const vec2& mat2:: operator[](int i) const   {
  i < 0    && rmr.die("mat2.operator[]: negative index");
  i >= 2 && rmr.die("mat2.operator[]: index too large");
  return __[i];
}
mat2 mat2:: operator*(const mat2& m) const   {
  mat2 temp;
  temp[0][0] += (*this)[0][0] * m[0][0];
  temp[0][0] += (*this)[1][0] * m[0][1];
  temp[0][1] += (*this)[0][1] * m[0][0];
  temp[0][1] += (*this)[1][1] * m[0][1];
  temp[1][0] += (*this)[0][0] * m[1][0];
  temp[1][0] += (*this)[1][0] * m[1][1];
  temp[1][1] += (*this)[0][1] * m[1][0];
  temp[1][1] += (*this)[1][1] * m[1][1];
  return temp;
}
mat2& mat2:: operator*=(const mat2& m)   {
  return *this = *this * m;
} // translation
// rotate
// dim == 2
mat2 mat2:: from_angle(float theta)   {
  return mat2(
           rmr.cos(theta), -rmr.sin(theta),
           rmr.sin(theta),  rmr.cos(theta)
         );
}
const vec2& mat2:: column(int i) const   {
  return (*this)[i];
}
vec2& mat2:: column(int i)   {
  return (*this)[i];
}
static_assert(sizeof(mat2) == sizeof(float) * 2 * 2, "mat2: unexpected size"    );
static_assert(!std::is_polymorphic<mat2>::value,     "mat2: non-polymorphic"    );
static_assert(std::is_standard_layout<mat2>::value,  "mat2: non-standard layout");
static_assert(std::is_literal_type<mat2>::value,     "mat2: non-literal"        );

ostream& operator<<(ostream& os, const mat2& m) {
  os << m[0][0];
  os << " ";
  os << m[1][0];
  os << " ";
  os << "\n";
  os << m[0][1];
  os << " ";
  os << m[1][1];
  os << " ";
  os << "\n";
  return os;
}

