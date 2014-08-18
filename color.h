#import "vec.h"

struct hsb_t {
  using _ = hsb_t&;
  hsb_t(float h, float s, float b, float a);
  hsb_t(float h, float s, float b);
  vec4 rgba() const;
  float h() const;
  float s() const;
  float b() const;
  float a() const;
  _ h(float);
  _ s(float);
  _ b(float);
  _ a(float);
private:
  float __[4];
};

ostream& operator<<(ostream&, const hsb_t&);

vec4 operator"" _c     (const char*);
vec4 operator"" _color (const char*);
vec4 operator"" _c     (const char*, size_t);
vec4 operator"" _color (const char*, size_t);
