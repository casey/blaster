% set code     = not test
% set static   = 'static' if header else ''
% set explicit = 'explicit' if header else ''
% set hsc      = ';' if header else ''

% macro static_method(class_name, method_name, parameters, return_type)
  {% if header %}static {% endif %}
  {% if code   %}{{return_type}} {% endif %}
  {% if source %}{{class_name}}::{% endif %}
  {% if code   %}{{method_name}}({{parameters}}){% endif %}
  {% if header %};{% elif source %}{ {{caller()}} }{% endif %}


% endmacro

% macro method(class_name, method_name, parameters, return_type)
  {% if code   %}{{return_type}} {% endif %}
  {% if source %}{{class_name}}::{% endif %}
  {% if code   %}{{method_name}}({{parameters}}){% endif %}
  {% if header %};{% elif source %}{ {{caller()}} }{% endif %}


% endmacro

% macro const_method(class_name, method_name, parameters, return_type)
  {% if code   %}{{return_type}} {% endif %}
  {% if source %}{{class_name}}::{% endif %}
  {% if code   %}{{method_name}}({{parameters}}) const{% endif %}
  {% if header %};{% elif source %}{ {{caller()}} }{% endif %}


% endmacro

{#
% macro nice_method(signature)
  % set parsed = parse_signature(signature)
  % if parsed.static
    static
  % endif

  % if code
    {{parsed.return_type}}
  % endif

  % if source
    {{parsed.class_name}}::
  % endif

  % if code
    {{parsed.method_name}}({{parsed.parameters}})
    % if parsed.const
      const
    % endif
  % endif


  % if header
    ;
  % elif source
  {
    {{caller()}}
  }
  % endif
% endmacro
#}


% macro test_block()
% if test
{
  {{caller()}}
}

% endif

% endmacro
% if source or test
#import "vec.h"
#import "rmr.h"
% else
#import "hash.h"
% endif

// stuff common to both vectors and matrices
% for length in lengths
% for type in types
% for name in make_all_names(type, length)
% if header
// forward declarations
struct NAME;
% elif source
// static assertions
static_assert(sizeof(NAME) == sizeof(decltype(NAME()[0])) * LENGTH, "NAME: unexpected size"     );
static_assert(!std::is_polymorphic<NAME>::value,                    "NAME: non-polymorphic"     );
static_assert(std::is_standard_layout<NAME>::value,                 "NAME: non-standard layout" );
static_assert(std::is_literal_type<NAME>::value,                    "NAME: non-literal"         );
static_assert(alignof(NAME) == alignof(TYPE),                       "NAME: unexpected alignment");
% endif
% endfor
% endfor
% endfor

% for length in lengths
% for type in types

% set name            = make_vec_name(type, length)
% set next            = make_vec_name(type, length + 1)
% set qual            = '%s::' % name if source else ''
% set components      = default_nameset[0:length]
% set me              = '_' if header else '%s&' % name
% set t               = type
% set floating_point  = type == 'float' or type == 'double'
% set integral        = type == 'int' or type == 'uint'
% set boolean         = type == 'bool'
% set signed          = not (type == 'bool' or type == 'uint')
% set sum_type        = 'uint' if type == 'bool' else type
% set dot_type        = 'int' if type == 'bool' else type

% if header
struct NAME {
  using _ = NAME&;
% elif test
TEST(NAME) {
% endif

// no argument constructor
% if header
constexpr NAME() : __{ {{commas(times(length, '0'))}} } { }
% endif
% call test_block()
  NAME _;
  {% for c in components %} ASSERT(_.C() == 0.0); {% endfor %}
  {% for c in components %} _.C(1.0);             {% endfor %}
  {% for c in components %} ASSERT(_.C() == 1.0); {% endfor %}
  new (&_) NAME;
  {% for c in components %} ASSERT(_.C() == 0.0); {% endfor %}
% endcall

// whatever constructor
% if code
QUAL NAME(whatever_t w) HSC {% if source %} { } {% endif %}
% endif
% call test_block()
  T* buffer = new T[LENGTH];
  buffer[0] = 7.0;
  new (buffer) NAME(rmr.whatever());
  ASSERT(buffer[0] == 7.0);
  new (buffer) NAME(5);
  ASSERT(buffer[0] == 5.0);
% endcall

// scalar component constructor
% if code
QUAL NAME(
    % for c in components
      T C {{ ',' if not loop.last else ''}}
    % endfor
    ) HSC {% if source %} : __{ {{commas(components)}} } {
} {% endif %}
% endif
% call test_block()
  NAME _{ {% for c in components %} 7 {{',' if not loop.last else ''}} {% endfor %} };
  % for c in components
    ASSERT(_.C() == 7);
  % endfor
% endcall

// single component constructor
% if code
EXPLICIT QUAL NAME(T s) HSC {% if source %} : __{ {{commas(times(length, 's'))}} } { } {% endif %}
% else
{
  NAME _{ 100 };
  % for c in components
    ASSERT(_.C() == 100);
  % endfor
}
% endif

// pointer initializer
% if code
QUAL NAME(T (&p)[LENGTH]) HSC {% if source %} : __{ 
  {% for i in range(length) %} p[I] {{', ' if not loop.last else ''}} {% endfor %}
} { } {% endif %}
% else
{
  T p[LENGTH] = {1};
  NAME v(p);
  ASSERT(v.x() == 1);
  ASSERT(v.y() == 0);
}
% endif

// component accessors
% for full_nameset in namesets
% set nameset = full_nameset[0:length]
% for i in range(length)
% set c = nameset[i]

% if code
T  QUAL C(   ) const HSC {% if source %} { return __[I];            } {% endif %}
T& QUAL C(   )       HSC {% if source %} { return __[I];            } {% endif %}
ME QUAL C(T s)       HSC {% if source %} { __[I] = s; return *this; } {% endif %}
% else
  ASSERT(NAME().C(3).C() == 3);
% endif

% endfor
% endfor

// swizzles
% if swizzles_on
% if code

% for swizzle_length in range(2, max_length + 1)
  % for swizzle_set in swizzles(length, swizzle_length)
    % for swizzle in swizzle_set
      % set swizzle_type       = make_vec_name(type, swizzle_length)
      % set swizzle_identifier = ''.join(swizzle)
      % set proxy_name         = name + '_' + swizzle_identifier + '_swizzle_proxy'
      % set proxy_qual         = '%s::' % proxy_name if source else ''
% if crazy_swizzles
% if header
struct PROXY_NAME {
% endif
  QUAL PROXY_QUAL PROXY_NAME(NAME& victim) HSC {% if source %} : victim(victim) { } {% endif %}
  T QUAL PROXY_QUAL operator=(T rhs) HSC {% if source %} {
    % for component in swizzle
      victim.COMPONENT() = rhs;
    % endfor
    return rhs;
  } {% endif %}
  SWIZZLE_TYPE QUAL PROXY_QUAL operator=(SWIZZLE_TYPE rhs) HSC {% if source %} {
    % for i in range(swizzle_length)
      victim.{{swizzle[i]}}() = rhs.{{default_nameset[i]}}();
    % endfor
    return rhs;
  } {% endif %}
  QUAL PROXY_QUAL operator SWIZZLE_TYPE() HSC {% if source %} {
    return SWIZZLE_TYPE(
      % for c in swizzle
        victim.C() {{', ' if not loop.last else ''}}
      % endfor
    );
  } {% endif %}
% if header
private:
  NAME& victim;
};
% endif
% else
// non-crazy swizzles (aka shaq-fu swizzles)
% endif

SWIZZLE_TYPE QUAL SWIZZLE_IDENTIFIER() const HSC {% if source %} {
  return SWIZZLE_TYPE(
  % for c in swizzle
    C() {{ ', ' if not loop.last else '' }}
  % endfor
  );
} {% endif %}
% if crazy_swizzles
QUAL PROXY_NAME   QUAL {{swizzle_identifier}}_ref() HSC {% if source %} { return PROXY_NAME  (*this  ); } {% endif %}
% endif
    % endfor
  % endfor
% endfor
% else
{
  NAME _;
  _.x() =  7.0;
  _.y() = 10.0;
  {{make_vec_name(type, 2)}} yx;
  yx = _.yx();
  ASSERT(yx.x() == 10.0);
  ASSERT(yx.y() ==  7.0);
}
% endif
% endif

// data pointers
% if code
      T* QUAL data()       HSC {% if source %} { return __; } {% endif %}
const T* QUAL data() const HSC {% if source %} { return __; } {% endif %}
% else
{
  NAME _;
  _.data()[0] = 2;
  ASSERT(_.x() == 2);
}
% endif

// operators
% for op in ops
% call const_method(name, 'operator' + op, t + ' s', name)
  return NAME(
    % for c in components
      C() OP s {{ ',' if not loop.last else '' }}
    % endfor
  );
% endcall
% call const_method(name, 'operator' + op, 'const %s& _' % name, name)
  return NAME(
    % for c in components
      C() OP _.C() {{ ',' if not loop.last else '' }}
    % endfor
  );
% endcall
% call method(name, 'operator%s=' % op, type + ' s', me)
  return *this = *this OP s;
% endcall
% call method(name, 'operator%s=' % op, 'const %s v' % name, me)
  return *this = *this OP v;
% endcall
% call test_block()
  NAME _;
  _ += 2;
  ASSERT(_.x() == 2);
  _ *= 3;
  ASSERT(_.y() == 6);
% endcall
% endfor

// unary +
% call const_method(name, 'operator+', '', name)
  return *this;
% endcall
% call test_block()
  NAME _(7);
  _ = +_;
  ASSERT(_.x() == 7);
% endcall

// const subscript
% if code
T QUAL operator[](int i) const HSC {% if source %} {
  i < 0 && rmr.die("NAME.operator[]: negative index");
  i >= LENGTH && rmr.die("NAME.operator[]: index too large");
  return __[i];
} {% endif %}
% endif

// mutable subscript
% if code
T& QUAL operator[](int i) HSC {% if source %} {
  i < 0 && rmr.die("NAME.operator[]: negative index");
  i >= LENGTH && rmr.die("NAME.operator[]: index too large");
  return __[i];
} {% endif %}
% endif

// iteration
% if code
const T* QUAL begin() const HSC {% if source %} { return data()         ; } {% endif %}
      T* QUAL begin()       HSC {% if source %} { return data()         ; } {% endif %}
const T* QUAL end  () const HSC {% if source %} { return data() + LENGTH; } {% endif %}
      T* QUAL end  ()       HSC {% if source %} { return data() + LENGTH; } {% endif %}
% endif

// length and size
% if code
size_t QUAL size() const HSC {% if source %} { return LENGTH; } {% endif %}
% else
{
  NAME _;
  ASSERT(_.size  () == LENGTH);
}
% endif

// sum
% if code
SUM_TYPE QUAL sum() const HSC {% if source %} {
  return {% for c in components %} C() {{'+' if not loop.last else ''}} {% endfor %};
} {% endif %}
% else
{
  NAME _(111);
  ASSERT(_.sum() == 111 * _.size());
}
% endif

// unary -
% if signed
% if code
NAME QUAL operator-() const HSC {% if source %} {
  return *this * -1.0;
} {% endif %}
% else
{
  NAME _(7);
  _ = -_;
  ASSERT(_.x() == -7);
}
% endif
% endif

// equality
% if code
bool QUAL operator==(const NAME& v) const HSC {% if source %} {
% for c in components
  if (C() != v.C()) return false;
% endfor
  return true;
} {% endif %}
bool QUAL operator!=(const NAME& v) const HSC {% if source %} {
  return !(*this == v);
} {% endif %}
% endif
% call test_block()
  NAME a;
  NAME b;
  ASSERT(a == b);
  ASSERT(!(a != b));
  a[0]++;
  ASSERT(!(a == b));
  ASSERT(a != b);
% endcall

% call static_method(name, 'random', '', name)
  return random(0, 1);
% endcall

% call static_method(name, 'random', '%s max' % type, name)
  return random(0, max);
% endcall

% call static_method(name, 'random', '%s min, %s max' % (type, type), name)
  return {{name}}( {{ commas(times(length, 'rmr.random(min, max)')) }});
% endcall

% call const_method(name, 'magnitude', '', type)
  return rmr.sqrt({% for c in components %} C() * C() {{'+' if not loop.last else ''}}{% endfor %});
% endcall
% call test_block()
  NAME _;
  ASSERT(_.magnitude() == 0);
  _.x(1);
  ASSERT(_.magnitude() == 1);
  _.y(1);
  ASSERT(_.magnitude() == T(sqrt(2))); // probably close enough
% endcall

// normalize
% call method(name, 'normalize', '', me)
  T l = magnitude();
  l > 0 || rmr.die("NAME.normalize: zero magnitude");
  return *this /= l;
% endcall
% call test_block()
  NAME _;
  _.x() = 10;
  _.normalize();
  ASSERT(_.x() == 1);
  % for c in components[1:length]
  ASSERT(_.C() == 0.0);
  % endfor
  _.x() = 0.0;
  _.y() = 20;
  _.normalize();
  ASSERT(_.y() == 1.0);
% endcall

// extend
% if length < max_length
% call const_method(name, 'extend', type + ' s', next)
  return NEXT(
      % for c in components
        C(),
      % endfor
      s
  );
% endcall
% endif

// hash
% if code
STATIC NAME QUAL hash(hash_t h) HSC {% if source %} {
  constexpr size_t bits = (sizeof(size_t) * CHAR_BIT) / LENGTH;
  constexpr size_t mask = ((size_t(1) << (bits + 1)) - 1);
  
  return {
    % for n in range(length)
      T((h >> bits * N & mask) / T(mask)) {{ ',' if not loop.last else '' }}
    % endfor
  };

} {% endif %}
% endif

// from heading
% if length == 2 and floating_point
% if code
STATIC NAME QUAL heading(double angle) HSC {% if source %} {
  return NAME(rmr.cos(angle), rmr.sin(angle));
} {% endif %}
% endif
% endif

// to heading
% if length == 2 and floating_point
% if code
double QUAL heading() HSC {% if source %} {
  return rmr.atan2(y(), x());
} {% endif %}
% endif
% endif

// dot
% if code
DOT_TYPE QUAL dot(const NAME& _) HSC {% if source %} {
  return {% for c in components %} C() * _.C() {{'+' if not loop.last else ''}} {% endfor %};
} {% endif %}
% else
{
  NAME     a{77};
  NAME     b{88};
  DOT_TYPE d = a.dot(b);
  ASSERT(d == 77 * 88 * LENGTH);
}
% endif

// dot
% if length == 3
% if code
NAME QUAL cross(const NAME& _) HSC {% if source %} {
  return {
    y() * _.z() - z() * _.y(),
    z() * _.x() - x() * _.z(),
    x() * _.y() - y() * _.x()
  };
} {% endif %}
% else
{
  // lol testing
}
% endif
% endif

// bits
% if code
STATIC NAME QUAL bits(int x) HSC {% if source %} {
  return NAME(
    % for i in range(length)
    (x >> I) & 1 {{ ', ' if not loop.last else '' }}
    % endfor
  );
} {% endif %}
% else
{
  NAME _ = NAME::bits(1);
  ASSERT(_.x() == 1.0);
  ASSERT(_.y() == 0.0);
}
% endif


% if header
private:
  T __[LENGTH];
};

ostream& operator<<(ostream&, const NAME&);
% elif source
ostream& operator<<(ostream& os, const NAME& v) {
  return os << "("
    % for c in components
      << v.C() {{'<< " "' if not loop.last else ''}}
    % endfor
    << ")";
}
% elif test
}
% endif

% endfor
% endfor

// matrices
% for dim in lengths
% for type in fp_types
% set t                      = type
% set name                   = make_mat_name(type, dim)
% set length                 = dim * dim
% set dim_vec                = make_vec_name(type, dim)
% set sub_vec                = make_vec_name(type, dim - 1)
% set translation_vec        = make_vec_name(type, dim - 1)
% set rotation_vec           = make_vec_name(type, 3)
% set rotation_components    = default_nameset[0:3]
% set all_separate_params    = commas(times(length, type))
% set dim_separate_params    = commas(times(dim, type))
% set sub_separate_params    = commas(times(dim - 1, type))
% set rot_separate_params    = commas(times(3, type))
% set vec_components         = default_nameset[0:length]
% set translation_components = default_nameset[0:dim - 1]
% set me                     = '_' if header else '%s&' % name
% set qual                   = '%s::' % name if source else ''
% if header
struct NAME {
  using _ = NAME&;
% elif test
  TEST(NAME) {
% endif

// no argument constructor
% if header
constexpr NAME() : __{ {{commas(times(dim, '{}'))}} } { }
% endif

// whatever constructor
% if code
QUAL NAME(whatever_t w) HSC {% if source %} : __{ {{commas(times(dim, '{rmr.whatever()}'))}} } { } {% endif %}
% endif

// component constructor
% if code
QUAL NAME(
    % for col in range(dim)
      % set outer_last = loop.last
      % for row in range(dim)
        T s{{row}}{{col}} {{  ', ' if not (outer_last and loop.last) else '' }}
      % endfor
    % endfor
    ) HSC {% if source %} {
    % for col in range(dim)
    __[{{col}}] = {
      % for row in range(dim)
          s{{row}}{{col}} {{ ', ' if not loop.last else '' }}
      % endfor
    };
    % endfor
} {% endif %}
% endif

% if code
STATIC const NAME& QUAL identity() HSC {% if source %} {
  static NAME i {
    % for col in range(dim)
      % set outer_last = loop.last
      % for row in range(dim)
        {{ '1' if row == col else '0' }} {{ ', ' if not (outer_last and loop.last) else '' }}
      % endfor
    % endfor
  };
  return i;
}; {% endif %}
% endif

// data pointers
% if code
      DIM_VEC* QUAL data()       HSC {% if source %} { return __; } {% endif %}
const DIM_VEC* QUAL data() const HSC {% if source %} { return __; } {% endif %}
% endif

// floats
% if code
      T* QUAL scalars()       HSC {% if source %} { return __[0].data(); } {% endif %}
const T* QUAL scalars() const HSC {% if source %} { return __[0].data(); } {% endif %}
% endif

% if code
DIM_VEC& QUAL operator[](int i) HSC {% if source %} {
  i < 0    && rmr.die("NAME.operator[]: negative index");
  i >= DIM && rmr.die("NAME.operator[]: index too large");
  return __[i];
} {% endif %}
% endif

% if code
const DIM_VEC& QUAL operator[](int i) const HSC {% if source %} {
  i < 0    && rmr.die("NAME.operator[]: negative index");
  i >= DIM && rmr.die("NAME.operator[]: index too large");
  return __[i];
} {% endif %}
% endif

% if code
NAME QUAL operator*(const NAME& m) const HSC {% if source %} {
  NAME temp;
  % for col in range(dim)
    % for row in range(dim)
      % for inner in range(dim)
        temp[COL][ROW] += (*this)[INNER][ROW] * m[COL][INNER];
      % endfor
    % endfor
  % endfor
  return temp;
} {% endif %}
% elif test
{
  NAME a;
  NAME b;
  a * b;
}
% endif

% if code
NAME& QUAL operator*=(const NAME& m) HSC {% if source %} {
  return *this = *this * m;
} {% endif %}
% elif test
{
  NAME a;
  NAME b;
  a * b;
}
% endif

// translation
% if dim > 2
% if code
NAME& QUAL translate(const TRANSLATION_VEC& v) HSC {% if source %} {
  NAME temp = NAME::identity();
  temp.column(DIM - 1) = v.extend(1.0);
  *this *= temp;
  return *this;
} {% endif %}

NAME& QUAL translate({{make_params(t, translation_components)}}) HSC {% if source %} {
  NAME temp = NAME::identity();
  temp.column(DIM - 1) = DIM_VEC{
    % for c in translation_components
      C,
    % endfor
    1
  };
  *this *= temp;
  return *this;
} {% endif %}

% for c in translation_components
NAME& QUAL translate_C(T C) HSC {% if source %} {
  TRANSLATION_VEC v;
  v.C() = C;
  return translate(v);
} {% endif %}
% endfor
% endif
% endif

// rotate
% if code
% if dim > 2
% for c in translation_components
NAME& QUAL rotate_C(T angle) HSC {% if source %} {
  ROTATION_VEC v;
  v.C() = 1.0;
  return rotate(v, angle);
} {% endif %}
% endfor

NAME& QUAL rotate(const ROTATION_VEC& v, T angle) HSC {% if source %} {
  NAME rotation_matrix = NAME::from_aa(v, angle);
  *this = *this * rotation_matrix;
  return *this;
} {% endif %}

NAME& QUAL rotate({{make_params(t, rotation_components)}}, T angle) HSC {% if source %} {
  NAME rotation_matrix = NAME::from_aa(
      ROTATION_VEC(
        % for c in rotation_components
          C {{', ' if not loop.last else ''}}
        % endfor
      ),
      angle);
  *this = *this * rotation_matrix;
  return *this;
} {% endif %}

STATIC NAME QUAL from_aa(const ROTATION_VEC& v, T theta) HSC {% if source %} {
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
    % if dim == 4
    0,
    % endif

    ax * ay * d - az * s,
    ay * ay * d + c,
    ay * az * d + ax * s,
    % if dim == 4
    0,
    % endif

    ax * az * d + ay * s,
    ay * az * d - ax * s,
    az * az * d + c,
    % if dim == 4
    0,

    0, 0, 0, 1
    % endif
  };
} {% endif %}
% else
// dim == 2
STATIC NAME QUAL from_angle(T theta) HSC {% if source %} {
  return NAME(
    rmr.cos(theta), -rmr.sin(theta),
    rmr.sin(theta),  rmr.cos(theta)
  );
} {% endif %}
% endif
% endif


% if code
const DIM_VEC& QUAL column(int i) const HSC {% if source %} {
  return (*this)[i];
} {% endif %}
% endif

% if code
DIM_VEC& QUAL column(int i) HSC {% if source %} {
  return (*this)[i];
} {% endif %}
% endif

% if header
private:
  DIM_VEC __[DIM];
};

ostream& operator<<(ostream&, const NAME&);
% elif source
static_assert(sizeof(NAME) == sizeof(T) * DIM * DIM, "NAME: unexpected size"    );
static_assert(!std::is_polymorphic<NAME>::value,     "NAME: non-polymorphic"    );
static_assert(std::is_standard_layout<NAME>::value,  "NAME: non-standard layout");
static_assert(std::is_literal_type<NAME>::value,     "NAME: non-literal"        );

ostream& operator<<(ostream& os, const NAME& m) {
  % for row in range(dim)
  % for col in range(dim)
    os << m[COL][ROW];
    os << " ";
  % endfor
    os << "\n";
  % endfor
  return os;
}

% elif test
}
% endif
% endfor
% endfor
