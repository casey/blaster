
#import "hash.h"
// stuff common to both vectors and matrices
// forward declarations
struct vec4;
// forward declarations
struct mat4;
// forward declarations
struct dvec4;
// forward declarations
struct dmat4;
// forward declarations
struct ivec4;
// forward declarations
struct uvec4;
// forward declarations
struct vec3;
// forward declarations
struct mat3;
// forward declarations
struct dvec3;
// forward declarations
struct dmat3;
// forward declarations
struct ivec3;
// forward declarations
struct uvec3;
// forward declarations
struct vec2;
// forward declarations
struct mat2;
// forward declarations
struct dvec2;
// forward declarations
struct dmat2;
// forward declarations
struct ivec2;
// forward declarations
struct uvec2;
struct vec4 {
  using _ = vec4&;
  // no argument constructor
  constexpr vec4() : __{ 0, 0, 0, 0 } { }
  // whatever constructor
  vec4(whatever_t w) ; // scalar component constructor
  vec4(
    float x,
    float y,
    float z,
    float w
  ) ; // single component constructor
  explicit  vec4(float s) ; // pointer initializer
  vec4(float (&p)[4]) ; // component accessors
  float   x(   ) const ;
  float&  x(   )       ;
  _  x(float s)       ;
  float   y(   ) const ;
  float&  y(   )       ;
  _  y(float s)       ;
  float   z(   ) const ;
  float&  z(   )       ;
  _  z(float s)       ;
  float   w(   ) const ;
  float&  w(   )       ;
  _  w(float s)       ;
  float   r(   ) const ;
  float&  r(   )       ;
  _  r(float s)       ;
  float   g(   ) const ;
  float&  g(   )       ;
  _  g(float s)       ;
  float   b(   ) const ;
  float&  b(   )       ;
  _  b(float s)       ;
  float   a(   ) const ;
  float&  a(   )       ;
  _  a(float s)       ;
  float   s(   ) const ;
  float&  s(   )       ;
  _  s(float s)       ;
  float   t(   ) const ;
  float&  t(   )       ;
  _  t(float s)       ;
  float   p(   ) const ;
  float&  p(   )       ;
  _  p(float s)       ;
  float   q(   ) const ;
  float&  q(   )       ;
  _  q(float s)       ; // swizzles
  // data pointers
  float*  data()       ;
  const float*  data() const ; // operators
  vec4 operator+(float s) const;

  vec4 operator+(const vec4& _) const;

  _ operator+=(float s);

  _ operator+=(const vec4 v);

  vec4 operator-(float s) const;

  vec4 operator-(const vec4& _) const;

  _ operator-=(float s);

  _ operator-=(const vec4 v);

  vec4 operator*(float s) const;

  vec4 operator*(const vec4& _) const;

  _ operator*=(float s);

  _ operator*=(const vec4 v);

  vec4 operator/(float s) const;

  vec4 operator/(const vec4& _) const;

  _ operator/=(float s);

  _ operator/=(const vec4 v);

  // unary +
  vec4 operator+() const;

  // const subscript
  float  operator[](int i) const ; // mutable subscript
  float&  operator[](int i) ; // iteration
  const float*  begin() const ;
  float*  begin()       ;
  const float*  end  () const ;
  float*  end  ()       ; // length and size
  size_t  size() const ; // sum
  float  sum() const ; // unary -
  vec4  operator-() const ; // equality
  bool  operator==(const vec4& v) const ;
  bool  operator!=(const vec4& v) const ;
  static vec4 random();

  static vec4 random(float max);

  static vec4 random(float min, float max);

  float magnitude() const;

  // normalize
  _ normalize();

  // extend
  // hash
  static vec4  hash(hash_t h) ; // from heading
  // to heading
  // dot
  float  dot(const vec4& _) ; // dot
  // bits
  static vec4  bits(int x) ;
private:
  float __[4];
};

ostream& operator<<(ostream&, const vec4&);
struct dvec4 {
  using _ = dvec4&;
  // no argument constructor
  constexpr dvec4() : __{ 0, 0, 0, 0 } { }
  // whatever constructor
  dvec4(whatever_t w) ; // scalar component constructor
  dvec4(
    double x,
    double y,
    double z,
    double w
  ) ; // single component constructor
  explicit  dvec4(double s) ; // pointer initializer
  dvec4(double (&p)[4]) ; // component accessors
  double   x(   ) const ;
  double&  x(   )       ;
  _  x(double s)       ;
  double   y(   ) const ;
  double&  y(   )       ;
  _  y(double s)       ;
  double   z(   ) const ;
  double&  z(   )       ;
  _  z(double s)       ;
  double   w(   ) const ;
  double&  w(   )       ;
  _  w(double s)       ;
  double   r(   ) const ;
  double&  r(   )       ;
  _  r(double s)       ;
  double   g(   ) const ;
  double&  g(   )       ;
  _  g(double s)       ;
  double   b(   ) const ;
  double&  b(   )       ;
  _  b(double s)       ;
  double   a(   ) const ;
  double&  a(   )       ;
  _  a(double s)       ;
  double   s(   ) const ;
  double&  s(   )       ;
  _  s(double s)       ;
  double   t(   ) const ;
  double&  t(   )       ;
  _  t(double s)       ;
  double   p(   ) const ;
  double&  p(   )       ;
  _  p(double s)       ;
  double   q(   ) const ;
  double&  q(   )       ;
  _  q(double s)       ; // swizzles
  // data pointers
  double*  data()       ;
  const double*  data() const ; // operators
  dvec4 operator+(double s) const;

  dvec4 operator+(const dvec4& _) const;

  _ operator+=(double s);

  _ operator+=(const dvec4 v);

  dvec4 operator-(double s) const;

  dvec4 operator-(const dvec4& _) const;

  _ operator-=(double s);

  _ operator-=(const dvec4 v);

  dvec4 operator*(double s) const;

  dvec4 operator*(const dvec4& _) const;

  _ operator*=(double s);

  _ operator*=(const dvec4 v);

  dvec4 operator/(double s) const;

  dvec4 operator/(const dvec4& _) const;

  _ operator/=(double s);

  _ operator/=(const dvec4 v);

  // unary +
  dvec4 operator+() const;

  // const subscript
  double  operator[](int i) const ; // mutable subscript
  double&  operator[](int i) ; // iteration
  const double*  begin() const ;
  double*  begin()       ;
  const double*  end  () const ;
  double*  end  ()       ; // length and size
  size_t  size() const ; // sum
  double  sum() const ; // unary -
  dvec4  operator-() const ; // equality
  bool  operator==(const dvec4& v) const ;
  bool  operator!=(const dvec4& v) const ;
  static dvec4 random();

  static dvec4 random(double max);

  static dvec4 random(double min, double max);

  double magnitude() const;

  // normalize
  _ normalize();

  // extend
  // hash
  static dvec4  hash(hash_t h) ; // from heading
  // to heading
  // dot
  double  dot(const dvec4& _) ; // dot
  // bits
  static dvec4  bits(int x) ;
private:
  double __[4];
};

ostream& operator<<(ostream&, const dvec4&);
struct ivec4 {
  using _ = ivec4&;
  // no argument constructor
  constexpr ivec4() : __{ 0, 0, 0, 0 } { }
  // whatever constructor
  ivec4(whatever_t w) ; // scalar component constructor
  ivec4(
    int x,
    int y,
    int z,
    int w
  ) ; // single component constructor
  explicit  ivec4(int s) ; // pointer initializer
  ivec4(int (&p)[4]) ; // component accessors
  int   x(   ) const ;
  int&  x(   )       ;
  _  x(int s)       ;
  int   y(   ) const ;
  int&  y(   )       ;
  _  y(int s)       ;
  int   z(   ) const ;
  int&  z(   )       ;
  _  z(int s)       ;
  int   w(   ) const ;
  int&  w(   )       ;
  _  w(int s)       ;
  int   r(   ) const ;
  int&  r(   )       ;
  _  r(int s)       ;
  int   g(   ) const ;
  int&  g(   )       ;
  _  g(int s)       ;
  int   b(   ) const ;
  int&  b(   )       ;
  _  b(int s)       ;
  int   a(   ) const ;
  int&  a(   )       ;
  _  a(int s)       ;
  int   s(   ) const ;
  int&  s(   )       ;
  _  s(int s)       ;
  int   t(   ) const ;
  int&  t(   )       ;
  _  t(int s)       ;
  int   p(   ) const ;
  int&  p(   )       ;
  _  p(int s)       ;
  int   q(   ) const ;
  int&  q(   )       ;
  _  q(int s)       ; // swizzles
  // data pointers
  int*  data()       ;
  const int*  data() const ; // operators
  ivec4 operator+(int s) const;

  ivec4 operator+(const ivec4& _) const;

  _ operator+=(int s);

  _ operator+=(const ivec4 v);

  ivec4 operator-(int s) const;

  ivec4 operator-(const ivec4& _) const;

  _ operator-=(int s);

  _ operator-=(const ivec4 v);

  ivec4 operator*(int s) const;

  ivec4 operator*(const ivec4& _) const;

  _ operator*=(int s);

  _ operator*=(const ivec4 v);

  ivec4 operator/(int s) const;

  ivec4 operator/(const ivec4& _) const;

  _ operator/=(int s);

  _ operator/=(const ivec4 v);

  // unary +
  ivec4 operator+() const;

  // const subscript
  int  operator[](int i) const ; // mutable subscript
  int&  operator[](int i) ; // iteration
  const int*  begin() const ;
  int*  begin()       ;
  const int*  end  () const ;
  int*  end  ()       ; // length and size
  size_t  size() const ; // sum
  int  sum() const ; // unary -
  ivec4  operator-() const ; // equality
  bool  operator==(const ivec4& v) const ;
  bool  operator!=(const ivec4& v) const ;
  static ivec4 random();

  static ivec4 random(int max);

  static ivec4 random(int min, int max);

  int magnitude() const;

  // normalize
  _ normalize();

  // extend
  // hash
  static ivec4  hash(hash_t h) ; // from heading
  // to heading
  // dot
  int  dot(const ivec4& _) ; // dot
  // bits
  static ivec4  bits(int x) ;
private:
  int __[4];
};

ostream& operator<<(ostream&, const ivec4&);
struct uvec4 {
  using _ = uvec4&;
  // no argument constructor
  constexpr uvec4() : __{ 0, 0, 0, 0 } { }
  // whatever constructor
  uvec4(whatever_t w) ; // scalar component constructor
  uvec4(
    uint x,
    uint y,
    uint z,
    uint w
  ) ; // single component constructor
  explicit  uvec4(uint s) ; // pointer initializer
  uvec4(uint (&p)[4]) ; // component accessors
  uint   x(   ) const ;
  uint&  x(   )       ;
  _  x(uint s)       ;
  uint   y(   ) const ;
  uint&  y(   )       ;
  _  y(uint s)       ;
  uint   z(   ) const ;
  uint&  z(   )       ;
  _  z(uint s)       ;
  uint   w(   ) const ;
  uint&  w(   )       ;
  _  w(uint s)       ;
  uint   r(   ) const ;
  uint&  r(   )       ;
  _  r(uint s)       ;
  uint   g(   ) const ;
  uint&  g(   )       ;
  _  g(uint s)       ;
  uint   b(   ) const ;
  uint&  b(   )       ;
  _  b(uint s)       ;
  uint   a(   ) const ;
  uint&  a(   )       ;
  _  a(uint s)       ;
  uint   s(   ) const ;
  uint&  s(   )       ;
  _  s(uint s)       ;
  uint   t(   ) const ;
  uint&  t(   )       ;
  _  t(uint s)       ;
  uint   p(   ) const ;
  uint&  p(   )       ;
  _  p(uint s)       ;
  uint   q(   ) const ;
  uint&  q(   )       ;
  _  q(uint s)       ; // swizzles
  // data pointers
  uint*  data()       ;
  const uint*  data() const ; // operators
  uvec4 operator+(uint s) const;

  uvec4 operator+(const uvec4& _) const;

  _ operator+=(uint s);

  _ operator+=(const uvec4 v);

  uvec4 operator-(uint s) const;

  uvec4 operator-(const uvec4& _) const;

  _ operator-=(uint s);

  _ operator-=(const uvec4 v);

  uvec4 operator*(uint s) const;

  uvec4 operator*(const uvec4& _) const;

  _ operator*=(uint s);

  _ operator*=(const uvec4 v);

  uvec4 operator/(uint s) const;

  uvec4 operator/(const uvec4& _) const;

  _ operator/=(uint s);

  _ operator/=(const uvec4 v);

  // unary +
  uvec4 operator+() const;

  // const subscript
  uint  operator[](int i) const ; // mutable subscript
  uint&  operator[](int i) ; // iteration
  const uint*  begin() const ;
  uint*  begin()       ;
  const uint*  end  () const ;
  uint*  end  ()       ; // length and size
  size_t  size() const ; // sum
  uint  sum() const ; // unary -
  // equality
  bool  operator==(const uvec4& v) const ;
  bool  operator!=(const uvec4& v) const ;
  static uvec4 random();

  static uvec4 random(uint max);

  static uvec4 random(uint min, uint max);

  uint magnitude() const;

  // normalize
  _ normalize();

  // extend
  // hash
  static uvec4  hash(hash_t h) ; // from heading
  // to heading
  // dot
  uint  dot(const uvec4& _) ; // dot
  // bits
  static uvec4  bits(int x) ;
private:
  uint __[4];
};

ostream& operator<<(ostream&, const uvec4&);
struct vec3 {
  using _ = vec3&;
  // no argument constructor
  constexpr vec3() : __{ 0, 0, 0 } { }
  // whatever constructor
  vec3(whatever_t w) ; // scalar component constructor
  vec3(
    float x,
    float y,
    float z
  ) ; // single component constructor
  explicit  vec3(float s) ; // pointer initializer
  vec3(float (&p)[3]) ; // component accessors
  float   x(   ) const ;
  float&  x(   )       ;
  _  x(float s)       ;
  float   y(   ) const ;
  float&  y(   )       ;
  _  y(float s)       ;
  float   z(   ) const ;
  float&  z(   )       ;
  _  z(float s)       ;
  float   r(   ) const ;
  float&  r(   )       ;
  _  r(float s)       ;
  float   g(   ) const ;
  float&  g(   )       ;
  _  g(float s)       ;
  float   b(   ) const ;
  float&  b(   )       ;
  _  b(float s)       ;
  float   s(   ) const ;
  float&  s(   )       ;
  _  s(float s)       ;
  float   t(   ) const ;
  float&  t(   )       ;
  _  t(float s)       ;
  float   p(   ) const ;
  float&  p(   )       ;
  _  p(float s)       ; // swizzles
  // data pointers
  float*  data()       ;
  const float*  data() const ; // operators
  vec3 operator+(float s) const;

  vec3 operator+(const vec3& _) const;

  _ operator+=(float s);

  _ operator+=(const vec3 v);

  vec3 operator-(float s) const;

  vec3 operator-(const vec3& _) const;

  _ operator-=(float s);

  _ operator-=(const vec3 v);

  vec3 operator*(float s) const;

  vec3 operator*(const vec3& _) const;

  _ operator*=(float s);

  _ operator*=(const vec3 v);

  vec3 operator/(float s) const;

  vec3 operator/(const vec3& _) const;

  _ operator/=(float s);

  _ operator/=(const vec3 v);

  // unary +
  vec3 operator+() const;

  // const subscript
  float  operator[](int i) const ; // mutable subscript
  float&  operator[](int i) ; // iteration
  const float*  begin() const ;
  float*  begin()       ;
  const float*  end  () const ;
  float*  end  ()       ; // length and size
  size_t  size() const ; // sum
  float  sum() const ; // unary -
  vec3  operator-() const ; // equality
  bool  operator==(const vec3& v) const ;
  bool  operator!=(const vec3& v) const ;
  static vec3 random();

  static vec3 random(float max);

  static vec3 random(float min, float max);

  float magnitude() const;

  // normalize
  _ normalize();

  // extend
  vec4 extend(float s) const;

  // hash
  static vec3  hash(hash_t h) ; // from heading
  // to heading
  // dot
  float  dot(const vec3& _) ; // dot
  vec3  cross(const vec3& _) ; // bits
  static vec3  bits(int x) ;
private:
  float __[3];
};

ostream& operator<<(ostream&, const vec3&);
struct dvec3 {
  using _ = dvec3&;
  // no argument constructor
  constexpr dvec3() : __{ 0, 0, 0 } { }
  // whatever constructor
  dvec3(whatever_t w) ; // scalar component constructor
  dvec3(
    double x,
    double y,
    double z
  ) ; // single component constructor
  explicit  dvec3(double s) ; // pointer initializer
  dvec3(double (&p)[3]) ; // component accessors
  double   x(   ) const ;
  double&  x(   )       ;
  _  x(double s)       ;
  double   y(   ) const ;
  double&  y(   )       ;
  _  y(double s)       ;
  double   z(   ) const ;
  double&  z(   )       ;
  _  z(double s)       ;
  double   r(   ) const ;
  double&  r(   )       ;
  _  r(double s)       ;
  double   g(   ) const ;
  double&  g(   )       ;
  _  g(double s)       ;
  double   b(   ) const ;
  double&  b(   )       ;
  _  b(double s)       ;
  double   s(   ) const ;
  double&  s(   )       ;
  _  s(double s)       ;
  double   t(   ) const ;
  double&  t(   )       ;
  _  t(double s)       ;
  double   p(   ) const ;
  double&  p(   )       ;
  _  p(double s)       ; // swizzles
  // data pointers
  double*  data()       ;
  const double*  data() const ; // operators
  dvec3 operator+(double s) const;

  dvec3 operator+(const dvec3& _) const;

  _ operator+=(double s);

  _ operator+=(const dvec3 v);

  dvec3 operator-(double s) const;

  dvec3 operator-(const dvec3& _) const;

  _ operator-=(double s);

  _ operator-=(const dvec3 v);

  dvec3 operator*(double s) const;

  dvec3 operator*(const dvec3& _) const;

  _ operator*=(double s);

  _ operator*=(const dvec3 v);

  dvec3 operator/(double s) const;

  dvec3 operator/(const dvec3& _) const;

  _ operator/=(double s);

  _ operator/=(const dvec3 v);

  // unary +
  dvec3 operator+() const;

  // const subscript
  double  operator[](int i) const ; // mutable subscript
  double&  operator[](int i) ; // iteration
  const double*  begin() const ;
  double*  begin()       ;
  const double*  end  () const ;
  double*  end  ()       ; // length and size
  size_t  size() const ; // sum
  double  sum() const ; // unary -
  dvec3  operator-() const ; // equality
  bool  operator==(const dvec3& v) const ;
  bool  operator!=(const dvec3& v) const ;
  static dvec3 random();

  static dvec3 random(double max);

  static dvec3 random(double min, double max);

  double magnitude() const;

  // normalize
  _ normalize();

  // extend
  dvec4 extend(double s) const;

  // hash
  static dvec3  hash(hash_t h) ; // from heading
  // to heading
  // dot
  double  dot(const dvec3& _) ; // dot
  dvec3  cross(const dvec3& _) ; // bits
  static dvec3  bits(int x) ;
private:
  double __[3];
};

ostream& operator<<(ostream&, const dvec3&);
struct ivec3 {
  using _ = ivec3&;
  // no argument constructor
  constexpr ivec3() : __{ 0, 0, 0 } { }
  // whatever constructor
  ivec3(whatever_t w) ; // scalar component constructor
  ivec3(
    int x,
    int y,
    int z
  ) ; // single component constructor
  explicit  ivec3(int s) ; // pointer initializer
  ivec3(int (&p)[3]) ; // component accessors
  int   x(   ) const ;
  int&  x(   )       ;
  _  x(int s)       ;
  int   y(   ) const ;
  int&  y(   )       ;
  _  y(int s)       ;
  int   z(   ) const ;
  int&  z(   )       ;
  _  z(int s)       ;
  int   r(   ) const ;
  int&  r(   )       ;
  _  r(int s)       ;
  int   g(   ) const ;
  int&  g(   )       ;
  _  g(int s)       ;
  int   b(   ) const ;
  int&  b(   )       ;
  _  b(int s)       ;
  int   s(   ) const ;
  int&  s(   )       ;
  _  s(int s)       ;
  int   t(   ) const ;
  int&  t(   )       ;
  _  t(int s)       ;
  int   p(   ) const ;
  int&  p(   )       ;
  _  p(int s)       ; // swizzles
  // data pointers
  int*  data()       ;
  const int*  data() const ; // operators
  ivec3 operator+(int s) const;

  ivec3 operator+(const ivec3& _) const;

  _ operator+=(int s);

  _ operator+=(const ivec3 v);

  ivec3 operator-(int s) const;

  ivec3 operator-(const ivec3& _) const;

  _ operator-=(int s);

  _ operator-=(const ivec3 v);

  ivec3 operator*(int s) const;

  ivec3 operator*(const ivec3& _) const;

  _ operator*=(int s);

  _ operator*=(const ivec3 v);

  ivec3 operator/(int s) const;

  ivec3 operator/(const ivec3& _) const;

  _ operator/=(int s);

  _ operator/=(const ivec3 v);

  // unary +
  ivec3 operator+() const;

  // const subscript
  int  operator[](int i) const ; // mutable subscript
  int&  operator[](int i) ; // iteration
  const int*  begin() const ;
  int*  begin()       ;
  const int*  end  () const ;
  int*  end  ()       ; // length and size
  size_t  size() const ; // sum
  int  sum() const ; // unary -
  ivec3  operator-() const ; // equality
  bool  operator==(const ivec3& v) const ;
  bool  operator!=(const ivec3& v) const ;
  static ivec3 random();

  static ivec3 random(int max);

  static ivec3 random(int min, int max);

  int magnitude() const;

  // normalize
  _ normalize();

  // extend
  ivec4 extend(int s) const;

  // hash
  static ivec3  hash(hash_t h) ; // from heading
  // to heading
  // dot
  int  dot(const ivec3& _) ; // dot
  ivec3  cross(const ivec3& _) ; // bits
  static ivec3  bits(int x) ;
private:
  int __[3];
};

ostream& operator<<(ostream&, const ivec3&);
struct uvec3 {
  using _ = uvec3&;
  // no argument constructor
  constexpr uvec3() : __{ 0, 0, 0 } { }
  // whatever constructor
  uvec3(whatever_t w) ; // scalar component constructor
  uvec3(
    uint x,
    uint y,
    uint z
  ) ; // single component constructor
  explicit  uvec3(uint s) ; // pointer initializer
  uvec3(uint (&p)[3]) ; // component accessors
  uint   x(   ) const ;
  uint&  x(   )       ;
  _  x(uint s)       ;
  uint   y(   ) const ;
  uint&  y(   )       ;
  _  y(uint s)       ;
  uint   z(   ) const ;
  uint&  z(   )       ;
  _  z(uint s)       ;
  uint   r(   ) const ;
  uint&  r(   )       ;
  _  r(uint s)       ;
  uint   g(   ) const ;
  uint&  g(   )       ;
  _  g(uint s)       ;
  uint   b(   ) const ;
  uint&  b(   )       ;
  _  b(uint s)       ;
  uint   s(   ) const ;
  uint&  s(   )       ;
  _  s(uint s)       ;
  uint   t(   ) const ;
  uint&  t(   )       ;
  _  t(uint s)       ;
  uint   p(   ) const ;
  uint&  p(   )       ;
  _  p(uint s)       ; // swizzles
  // data pointers
  uint*  data()       ;
  const uint*  data() const ; // operators
  uvec3 operator+(uint s) const;

  uvec3 operator+(const uvec3& _) const;

  _ operator+=(uint s);

  _ operator+=(const uvec3 v);

  uvec3 operator-(uint s) const;

  uvec3 operator-(const uvec3& _) const;

  _ operator-=(uint s);

  _ operator-=(const uvec3 v);

  uvec3 operator*(uint s) const;

  uvec3 operator*(const uvec3& _) const;

  _ operator*=(uint s);

  _ operator*=(const uvec3 v);

  uvec3 operator/(uint s) const;

  uvec3 operator/(const uvec3& _) const;

  _ operator/=(uint s);

  _ operator/=(const uvec3 v);

  // unary +
  uvec3 operator+() const;

  // const subscript
  uint  operator[](int i) const ; // mutable subscript
  uint&  operator[](int i) ; // iteration
  const uint*  begin() const ;
  uint*  begin()       ;
  const uint*  end  () const ;
  uint*  end  ()       ; // length and size
  size_t  size() const ; // sum
  uint  sum() const ; // unary -
  // equality
  bool  operator==(const uvec3& v) const ;
  bool  operator!=(const uvec3& v) const ;
  static uvec3 random();

  static uvec3 random(uint max);

  static uvec3 random(uint min, uint max);

  uint magnitude() const;

  // normalize
  _ normalize();

  // extend
  uvec4 extend(uint s) const;

  // hash
  static uvec3  hash(hash_t h) ; // from heading
  // to heading
  // dot
  uint  dot(const uvec3& _) ; // dot
  uvec3  cross(const uvec3& _) ; // bits
  static uvec3  bits(int x) ;
private:
  uint __[3];
};

ostream& operator<<(ostream&, const uvec3&);
struct vec2 {
  using _ = vec2&;
  // no argument constructor
  constexpr vec2() : __{ 0, 0 } { }
  // whatever constructor
  vec2(whatever_t w) ; // scalar component constructor
  vec2(
    float x,
    float y
  ) ; // single component constructor
  explicit  vec2(float s) ; // pointer initializer
  vec2(float (&p)[2]) ; // component accessors
  float   x(   ) const ;
  float&  x(   )       ;
  _  x(float s)       ;
  float   y(   ) const ;
  float&  y(   )       ;
  _  y(float s)       ;
  float   r(   ) const ;
  float&  r(   )       ;
  _  r(float s)       ;
  float   g(   ) const ;
  float&  g(   )       ;
  _  g(float s)       ;
  float   s(   ) const ;
  float&  s(   )       ;
  _  s(float s)       ;
  float   t(   ) const ;
  float&  t(   )       ;
  _  t(float s)       ; // swizzles
  // data pointers
  float*  data()       ;
  const float*  data() const ; // operators
  vec2 operator+(float s) const;

  vec2 operator+(const vec2& _) const;

  _ operator+=(float s);

  _ operator+=(const vec2 v);

  vec2 operator-(float s) const;

  vec2 operator-(const vec2& _) const;

  _ operator-=(float s);

  _ operator-=(const vec2 v);

  vec2 operator*(float s) const;

  vec2 operator*(const vec2& _) const;

  _ operator*=(float s);

  _ operator*=(const vec2 v);

  vec2 operator/(float s) const;

  vec2 operator/(const vec2& _) const;

  _ operator/=(float s);

  _ operator/=(const vec2 v);

  // unary +
  vec2 operator+() const;

  // const subscript
  float  operator[](int i) const ; // mutable subscript
  float&  operator[](int i) ; // iteration
  const float*  begin() const ;
  float*  begin()       ;
  const float*  end  () const ;
  float*  end  ()       ; // length and size
  size_t  size() const ; // sum
  float  sum() const ; // unary -
  vec2  operator-() const ; // equality
  bool  operator==(const vec2& v) const ;
  bool  operator!=(const vec2& v) const ;
  static vec2 random();

  static vec2 random(float max);

  static vec2 random(float min, float max);

  float magnitude() const;

  // normalize
  _ normalize();

  // extend
  vec3 extend(float s) const;

  // hash
  static vec2  hash(hash_t h) ; // from heading
  static vec2  heading(double angle) ; // to heading
  double  heading() ; // dot
  float  dot(const vec2& _) ; // dot
  // bits
  static vec2  bits(int x) ;
private:
  float __[2];
};

ostream& operator<<(ostream&, const vec2&);
struct dvec2 {
  using _ = dvec2&;
  // no argument constructor
  constexpr dvec2() : __{ 0, 0 } { }
  // whatever constructor
  dvec2(whatever_t w) ; // scalar component constructor
  dvec2(
    double x,
    double y
  ) ; // single component constructor
  explicit  dvec2(double s) ; // pointer initializer
  dvec2(double (&p)[2]) ; // component accessors
  double   x(   ) const ;
  double&  x(   )       ;
  _  x(double s)       ;
  double   y(   ) const ;
  double&  y(   )       ;
  _  y(double s)       ;
  double   r(   ) const ;
  double&  r(   )       ;
  _  r(double s)       ;
  double   g(   ) const ;
  double&  g(   )       ;
  _  g(double s)       ;
  double   s(   ) const ;
  double&  s(   )       ;
  _  s(double s)       ;
  double   t(   ) const ;
  double&  t(   )       ;
  _  t(double s)       ; // swizzles
  // data pointers
  double*  data()       ;
  const double*  data() const ; // operators
  dvec2 operator+(double s) const;

  dvec2 operator+(const dvec2& _) const;

  _ operator+=(double s);

  _ operator+=(const dvec2 v);

  dvec2 operator-(double s) const;

  dvec2 operator-(const dvec2& _) const;

  _ operator-=(double s);

  _ operator-=(const dvec2 v);

  dvec2 operator*(double s) const;

  dvec2 operator*(const dvec2& _) const;

  _ operator*=(double s);

  _ operator*=(const dvec2 v);

  dvec2 operator/(double s) const;

  dvec2 operator/(const dvec2& _) const;

  _ operator/=(double s);

  _ operator/=(const dvec2 v);

  // unary +
  dvec2 operator+() const;

  // const subscript
  double  operator[](int i) const ; // mutable subscript
  double&  operator[](int i) ; // iteration
  const double*  begin() const ;
  double*  begin()       ;
  const double*  end  () const ;
  double*  end  ()       ; // length and size
  size_t  size() const ; // sum
  double  sum() const ; // unary -
  dvec2  operator-() const ; // equality
  bool  operator==(const dvec2& v) const ;
  bool  operator!=(const dvec2& v) const ;
  static dvec2 random();

  static dvec2 random(double max);

  static dvec2 random(double min, double max);

  double magnitude() const;

  // normalize
  _ normalize();

  // extend
  dvec3 extend(double s) const;

  // hash
  static dvec2  hash(hash_t h) ; // from heading
  static dvec2  heading(double angle) ; // to heading
  double  heading() ; // dot
  double  dot(const dvec2& _) ; // dot
  // bits
  static dvec2  bits(int x) ;
private:
  double __[2];
};

ostream& operator<<(ostream&, const dvec2&);
struct ivec2 {
  using _ = ivec2&;
  // no argument constructor
  constexpr ivec2() : __{ 0, 0 } { }
  // whatever constructor
  ivec2(whatever_t w) ; // scalar component constructor
  ivec2(
    int x,
    int y
  ) ; // single component constructor
  explicit  ivec2(int s) ; // pointer initializer
  ivec2(int (&p)[2]) ; // component accessors
  int   x(   ) const ;
  int&  x(   )       ;
  _  x(int s)       ;
  int   y(   ) const ;
  int&  y(   )       ;
  _  y(int s)       ;
  int   r(   ) const ;
  int&  r(   )       ;
  _  r(int s)       ;
  int   g(   ) const ;
  int&  g(   )       ;
  _  g(int s)       ;
  int   s(   ) const ;
  int&  s(   )       ;
  _  s(int s)       ;
  int   t(   ) const ;
  int&  t(   )       ;
  _  t(int s)       ; // swizzles
  // data pointers
  int*  data()       ;
  const int*  data() const ; // operators
  ivec2 operator+(int s) const;

  ivec2 operator+(const ivec2& _) const;

  _ operator+=(int s);

  _ operator+=(const ivec2 v);

  ivec2 operator-(int s) const;

  ivec2 operator-(const ivec2& _) const;

  _ operator-=(int s);

  _ operator-=(const ivec2 v);

  ivec2 operator*(int s) const;

  ivec2 operator*(const ivec2& _) const;

  _ operator*=(int s);

  _ operator*=(const ivec2 v);

  ivec2 operator/(int s) const;

  ivec2 operator/(const ivec2& _) const;

  _ operator/=(int s);

  _ operator/=(const ivec2 v);

  // unary +
  ivec2 operator+() const;

  // const subscript
  int  operator[](int i) const ; // mutable subscript
  int&  operator[](int i) ; // iteration
  const int*  begin() const ;
  int*  begin()       ;
  const int*  end  () const ;
  int*  end  ()       ; // length and size
  size_t  size() const ; // sum
  int  sum() const ; // unary -
  ivec2  operator-() const ; // equality
  bool  operator==(const ivec2& v) const ;
  bool  operator!=(const ivec2& v) const ;
  static ivec2 random();

  static ivec2 random(int max);

  static ivec2 random(int min, int max);

  int magnitude() const;

  // normalize
  _ normalize();

  // extend
  ivec3 extend(int s) const;

  // hash
  static ivec2  hash(hash_t h) ; // from heading
  // to heading
  // dot
  int  dot(const ivec2& _) ; // dot
  // bits
  static ivec2  bits(int x) ;
private:
  int __[2];
};

ostream& operator<<(ostream&, const ivec2&);
struct uvec2 {
  using _ = uvec2&;
  // no argument constructor
  constexpr uvec2() : __{ 0, 0 } { }
  // whatever constructor
  uvec2(whatever_t w) ; // scalar component constructor
  uvec2(
    uint x,
    uint y
  ) ; // single component constructor
  explicit  uvec2(uint s) ; // pointer initializer
  uvec2(uint (&p)[2]) ; // component accessors
  uint   x(   ) const ;
  uint&  x(   )       ;
  _  x(uint s)       ;
  uint   y(   ) const ;
  uint&  y(   )       ;
  _  y(uint s)       ;
  uint   r(   ) const ;
  uint&  r(   )       ;
  _  r(uint s)       ;
  uint   g(   ) const ;
  uint&  g(   )       ;
  _  g(uint s)       ;
  uint   s(   ) const ;
  uint&  s(   )       ;
  _  s(uint s)       ;
  uint   t(   ) const ;
  uint&  t(   )       ;
  _  t(uint s)       ; // swizzles
  // data pointers
  uint*  data()       ;
  const uint*  data() const ; // operators
  uvec2 operator+(uint s) const;

  uvec2 operator+(const uvec2& _) const;

  _ operator+=(uint s);

  _ operator+=(const uvec2 v);

  uvec2 operator-(uint s) const;

  uvec2 operator-(const uvec2& _) const;

  _ operator-=(uint s);

  _ operator-=(const uvec2 v);

  uvec2 operator*(uint s) const;

  uvec2 operator*(const uvec2& _) const;

  _ operator*=(uint s);

  _ operator*=(const uvec2 v);

  uvec2 operator/(uint s) const;

  uvec2 operator/(const uvec2& _) const;

  _ operator/=(uint s);

  _ operator/=(const uvec2 v);

  // unary +
  uvec2 operator+() const;

  // const subscript
  uint  operator[](int i) const ; // mutable subscript
  uint&  operator[](int i) ; // iteration
  const uint*  begin() const ;
  uint*  begin()       ;
  const uint*  end  () const ;
  uint*  end  ()       ; // length and size
  size_t  size() const ; // sum
  uint  sum() const ; // unary -
  // equality
  bool  operator==(const uvec2& v) const ;
  bool  operator!=(const uvec2& v) const ;
  static uvec2 random();

  static uvec2 random(uint max);

  static uvec2 random(uint min, uint max);

  uint magnitude() const;

  // normalize
  _ normalize();

  // extend
  uvec3 extend(uint s) const;

  // hash
  static uvec2  hash(hash_t h) ; // from heading
  // to heading
  // dot
  uint  dot(const uvec2& _) ; // dot
  // bits
  static uvec2  bits(int x) ;
private:
  uint __[2];
};

ostream& operator<<(ostream&, const uvec2&);
// matrices
struct dmat4 {
  using _ = dmat4&;
  // no argument constructor
  constexpr dmat4() : __{ {}, {}, {}, {} } { }
  // whatever constructor
  dmat4(whatever_t w) ; // component constructor
  dmat4(
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
  ) ;
  static const dmat4&  identity() ; // data pointers
  dvec4*  data()       ;
  const dvec4*  data() const ; // floats
  double*  scalars()       ;
  const double*  scalars() const ;
  dvec4&  operator[](int i) ;
  const dvec4&  operator[](int i) const ;
  dmat4  operator*(const dmat4& m) const ;
  dmat4&  operator*=(const dmat4& m) ; // translation
  dmat4&  translate(const dvec3& v) ;
  dmat4&  translate(double x, double y, double z) ;
  dmat4&  translate_x(double x) ;
  dmat4&  translate_y(double y) ;
  dmat4&  translate_z(double z) ; // rotate
  dmat4&  rotate_x(double angle) ;
  dmat4&  rotate_y(double angle) ;
  dmat4&  rotate_z(double angle) ;
  dmat4&  rotate(const dvec3& v, double angle) ;
  dmat4&  rotate(double x, double y, double z, double angle) ;
  static dmat4  from_aa(const dvec3& v, double theta) ;
  const dvec4&  column(int i) const ;
  dvec4&  column(int i) ;
private:
  dvec4 __[4];
};

ostream& operator<<(ostream&, const dmat4&);
struct mat4 {
  using _ = mat4&;
  // no argument constructor
  constexpr mat4() : __{ {}, {}, {}, {} } { }
  // whatever constructor
  mat4(whatever_t w) ; // component constructor
  mat4(
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
  ) ;
  static const mat4&  identity() ; // data pointers
  vec4*  data()       ;
  const vec4*  data() const ; // floats
  float*  scalars()       ;
  const float*  scalars() const ;
  vec4&  operator[](int i) ;
  const vec4&  operator[](int i) const ;
  mat4  operator*(const mat4& m) const ;
  mat4&  operator*=(const mat4& m) ; // translation
  mat4&  translate(const vec3& v) ;
  mat4&  translate(float x, float y, float z) ;
  mat4&  translate_x(float x) ;
  mat4&  translate_y(float y) ;
  mat4&  translate_z(float z) ; // rotate
  mat4&  rotate_x(float angle) ;
  mat4&  rotate_y(float angle) ;
  mat4&  rotate_z(float angle) ;
  mat4&  rotate(const vec3& v, float angle) ;
  mat4&  rotate(float x, float y, float z, float angle) ;
  static mat4  from_aa(const vec3& v, float theta) ;
  const vec4&  column(int i) const ;
  vec4&  column(int i) ;
private:
  vec4 __[4];
};

ostream& operator<<(ostream&, const mat4&);
struct dmat3 {
  using _ = dmat3&;
  // no argument constructor
  constexpr dmat3() : __{ {}, {}, {} } { }
  // whatever constructor
  dmat3(whatever_t w) ; // component constructor
  dmat3(
    double s00,
    double s10,
    double s20,
    double s01,
    double s11,
    double s21,
    double s02,
    double s12,
    double s22
  ) ;
  static const dmat3&  identity() ; // data pointers
  dvec3*  data()       ;
  const dvec3*  data() const ; // floats
  double*  scalars()       ;
  const double*  scalars() const ;
  dvec3&  operator[](int i) ;
  const dvec3&  operator[](int i) const ;
  dmat3  operator*(const dmat3& m) const ;
  dmat3&  operator*=(const dmat3& m) ; // translation
  dmat3&  translate(const dvec2& v) ;
  dmat3&  translate(double x, double y) ;
  dmat3&  translate_x(double x) ;
  dmat3&  translate_y(double y) ; // rotate
  dmat3&  rotate_x(double angle) ;
  dmat3&  rotate_y(double angle) ;
  dmat3&  rotate(const dvec3& v, double angle) ;
  dmat3&  rotate(double x, double y, double z, double angle) ;
  static dmat3  from_aa(const dvec3& v, double theta) ;
  const dvec3&  column(int i) const ;
  dvec3&  column(int i) ;
private:
  dvec3 __[3];
};

ostream& operator<<(ostream&, const dmat3&);
struct mat3 {
  using _ = mat3&;
  // no argument constructor
  constexpr mat3() : __{ {}, {}, {} } { }
  // whatever constructor
  mat3(whatever_t w) ; // component constructor
  mat3(
    float s00,
    float s10,
    float s20,
    float s01,
    float s11,
    float s21,
    float s02,
    float s12,
    float s22
  ) ;
  static const mat3&  identity() ; // data pointers
  vec3*  data()       ;
  const vec3*  data() const ; // floats
  float*  scalars()       ;
  const float*  scalars() const ;
  vec3&  operator[](int i) ;
  const vec3&  operator[](int i) const ;
  mat3  operator*(const mat3& m) const ;
  mat3&  operator*=(const mat3& m) ; // translation
  mat3&  translate(const vec2& v) ;
  mat3&  translate(float x, float y) ;
  mat3&  translate_x(float x) ;
  mat3&  translate_y(float y) ; // rotate
  mat3&  rotate_x(float angle) ;
  mat3&  rotate_y(float angle) ;
  mat3&  rotate(const vec3& v, float angle) ;
  mat3&  rotate(float x, float y, float z, float angle) ;
  static mat3  from_aa(const vec3& v, float theta) ;
  const vec3&  column(int i) const ;
  vec3&  column(int i) ;
private:
  vec3 __[3];
};

ostream& operator<<(ostream&, const mat3&);
struct dmat2 {
  using _ = dmat2&;
  // no argument constructor
  constexpr dmat2() : __{ {}, {} } { }
  // whatever constructor
  dmat2(whatever_t w) ; // component constructor
  dmat2(
    double s00,
    double s10,
    double s01,
    double s11
  ) ;
  static const dmat2&  identity() ; // data pointers
  dvec2*  data()       ;
  const dvec2*  data() const ; // floats
  double*  scalars()       ;
  const double*  scalars() const ;
  dvec2&  operator[](int i) ;
  const dvec2&  operator[](int i) const ;
  dmat2  operator*(const dmat2& m) const ;
  dmat2&  operator*=(const dmat2& m) ; // translation
  // rotate
  // dim == 2
  static dmat2  from_angle(double theta) ;
  const dvec2&  column(int i) const ;
  dvec2&  column(int i) ;
private:
  dvec2 __[2];
};

ostream& operator<<(ostream&, const dmat2&);
struct mat2 {
  using _ = mat2&;
  // no argument constructor
  constexpr mat2() : __{ {}, {} } { }
  // whatever constructor
  mat2(whatever_t w) ; // component constructor
  mat2(
    float s00,
    float s10,
    float s01,
    float s11
  ) ;
  static const mat2&  identity() ; // data pointers
  vec2*  data()       ;
  const vec2*  data() const ; // floats
  float*  scalars()       ;
  const float*  scalars() const ;
  vec2&  operator[](int i) ;
  const vec2&  operator[](int i) const ;
  mat2  operator*(const mat2& m) const ;
  mat2&  operator*=(const mat2& m) ; // translation
  // rotate
  // dim == 2
  static mat2  from_angle(float theta) ;
  const vec2&  column(int i) const ;
  vec2&  column(int i) ;
private:
  vec2 __[2];
};

ostream& operator<<(ostream&, const mat2&);

