#import "color.h"
#import "rmr.h"
#import "color_names.h"

using _ = hsb_t&;

hsb_t::hsb_t(float h, float s, float b, float a) : __{h, s, b, a} {}
hsb_t::hsb_t(float h, float s, float b         ) : hsb_t(h, s, b, 1.0) {}
float hsb_t::h() const { return __[0]; }
float hsb_t::s() const { return __[1]; }
float hsb_t::b() const { return __[2]; }
float hsb_t::a() const { return __[3]; }
_ hsb_t::h(float x) { __[0] = x; return *this; }
_ hsb_t::s(float x) { __[1] = x; return *this; }
_ hsb_t::b(float x) { __[2] = x; return *this; }
_ hsb_t::a(float x) { __[3] = x; return *this; }

vec4 hsb_t::rgba() const {
  float _b = rmr.clamp(b());
  float _s = rmr.clamp(s());
  float _h = rmr.angle(h());

  if (_s == 0) return {_b, _b, _b, a()};

  int sector = std::floor((_h / rmr.tau()) * 6);

  float f = _h - (sector / 5.0) * rmr.tau();
  float p = b() * ( 1 - _s );
  float q = b() * ( 1 - _s * f );
  float t = b() * ( 1 - _s * ( 1 - f ) );

  return sector == 0 ? vec4{_b,  t,  p, a()} :
         sector == 1 ? vec4{ q, _b,  p, a()} :
         sector == 2 ? vec4{ p, _b,  t, a()} :
         sector == 3 ? vec4{ p,  q, _b, a()} :
         sector == 4 ? vec4{ t,  p, _b, a()} :
                       vec4{_b,  p,  q, a()} ;
}

ostream& operator<<(ostream& os, const hsb_t& x) {
  return os << "hsb(" << x.h() << x.s() << x.b() << x.a() << ")";
}

#import "algorithm"

u8 decode_hex(char c) {
  return c >= 'A' ? (c - 'A' + 10) : (c - '0');
}

vec4 parse_hex_color(const char* z) {
  string s{z};

  s.erase(std::remove(s.begin(), s.end(), '\''), s.end());

  if (s.size() < 2) rmr.fatal() << "_color: literal too short:" << s;
  if (s[0] != '0' || s[1] != 'x') rmr.fatal() << "_color: literal not hex:" << s;
  s.erase(0, 2);

  float r;
  float g;
  float b;
  float a = 1.0f;

  switch (s.size()) {
    case 4: a = decode_hex(s[3]) / (0xF * 1.0f);
    case 3: r = decode_hex(s[0]) / (0xF * 1.0f);
            g = decode_hex(s[1]) / (0xF * 1.0f);
            b = decode_hex(s[2]) / (0xF * 1.0f);
            break;
    case 8: b = (decode_hex(s[6]) << 4 | decode_hex(s[7])) / (0xFF * 1.0f);
    case 6: r = (decode_hex(s[0]) << 4 | decode_hex(s[1])) / (0xFF * 1.0f);
            g = (decode_hex(s[2]) << 4 | decode_hex(s[3])) / (0xFF * 1.0f);
            b = (decode_hex(s[4]) << 4 | decode_hex(s[5])) / (0xFF * 1.0f);
            break;
    default: rmr.fatal() << "_color: unexpected literal length:" << s;
             exit(1);
  }
  return vec4(r, g, b, a);
}

vec4 parse_string_color(const char* b, size_t l) {
  string s{b, l};

  size_t sep = s.find(':');

  string color = sep == -1 ? s  : s.substr(0, sep);
  string alpha = sep == -1 ? "" : s.substr(sep + 1);

  vec3 rgb;

  if      (color == "random"         ) rgb = vec3::random();
  else if (color == "r"              ) rgb = vec3::random();
  else if (color_names().count(color)) rgb = color_names()[color];
  else                                 rmr.fatal() << "parse_string_color: unrecognized color:" << color;

  float a = 1.0;

  if      (alpha == ""      ) a = 1.0;
  else if (alpha == "random") a = rmr.random();
  else if (alpha == "r"     ) a = rmr.random();
  else                        rmr.fatal() << "parse_string_color: unrecognized alpha:" << alpha;

  return rgb.extend(a);
}

vec4 operator"" _c     (const char* z          ) { return parse_hex_color   (z   ); }
vec4 operator"" _color (const char* z          ) { return parse_hex_color   (z   ); }
vec4 operator"" _c     (const char* s, size_t l) { return parse_string_color(s, l); }
vec4 operator"" _color (const char* s, size_t l) { return parse_string_color(s, l); }
