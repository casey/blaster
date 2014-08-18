#import "vec.h"

struct quat {
  using _ = quat&;
  const float* data() const;
  float* data();
  quat() = delete;
  float magnitude() const;
  float x() const;
  float y() const;
  float z() const;
  float w() const;
  _ x(float);
  _ y(float);
  _ z(float);
  _ w(float);
  _ normalize();
  mat4 to_matrix() const;
  static const quat& identity();
  static quat from_aa(vec3 axis, float angle);
private:
  quat(float, float, float, float);
  vec4 __;
};

ostream& operator<<(ostream&, const quat&);
