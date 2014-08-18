#import "quat.h"
#import "rmr.h"

quat::quat(float x, float y, float z, float w) : __(x, y, z, w) {
}

const quat& quat::identity() {
  static quat i { 0, 0, 0, 1 };
  return i;
};

quat quat::from_aa(vec3 axis, float angle) {
  axis.normalize();
  double s = rmr.sin(angle / 2);
  return quat(axis.x() * s, axis.y() * s, axis.z() * s, rmr.cos(angle / 2));
}

float quat::magnitude() const { return __.magnitude();        }
quat& quat::normalize()       { __.normalize(); return *this; }

float quat::x() const { return __.x(); }
float quat::y() const { return __.y(); }
float quat::z() const { return __.z(); }
float quat::w() const { return __.w(); }

mat4 quat::to_matrix() const {
  float _x = x(), _y = y(), _z = z(), _w = w();
  float x2 = 2 * _x, y2 = 2 * _y, z2 = 2 * _z;
  float wx = x2 * _w;
  float wy = y2 * _w;
  float wz = z2 * _w;
  float xx = x2 * _x;
  float xy = y2 * _x;
  float xz = z2 * _x;
  float yy = y2 * _y;
  float yz = z2 * _y;
  float zz = z2 * _z;

  mat4 result;
  result[0] = {1 - (yy + zz), xy + wz,       xz - wy,       0};
  result[1] = {xy - wz,       1 - (xx + zz), yz + wx,       0};
  result[2] = {xz + wy,       yz - wx,       1 - (xx + yy), 0};
  result[3] = {0,             0,             0,             1};
  return result;
}

const float* quat::data() const { return __.data(); }
      float* quat::data()       { return __.data(); }

ostream& operator<<(ostream& os, const quat& q) {
  return os << "(" << q.x() << " " << q.y() << " " << q.z() << " " << q.w() << " " << ")";
}
