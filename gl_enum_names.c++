#import <OpenGL/gl3.h>
#import "gl_enum_names.h"

void add_enum(map<uint, string>& table, uint e, const char* name) {
  if (table.count(e)) {
    table[e] = table[e] + "|" + name;
  } else {
    table[e] = name;
  }
}

void add_enums(map<uint, string>& table) {
#define _(e) add_enum(table, e, #e)
  _(GL_INVALID_ENUM                  );
  _(GL_INVALID_VALUE                 );
  _(GL_INVALID_OPERATION             );
  _(GL_INVALID_FRAMEBUFFER_OPERATION );
  _(GL_OUT_OF_MEMORY                 );
  _(GL_NO_ERROR                      );
  _(GL_FLOAT_VEC2                    );
  _(GL_FLOAT_VEC3                    );
  _(GL_FLOAT_VEC4                    );
  _(GL_INT_VEC2                      );
  _(GL_INT_VEC3                      );
  _(GL_INT_VEC4                      );
  _(GL_BOOL                          );
  _(GL_BOOL_VEC2                     );
  _(GL_BOOL_VEC3                     );
  _(GL_BOOL_VEC4                     );
  _(GL_FLOAT_MAT2                    );
  _(GL_FLOAT_MAT3                    );
  _(GL_FLOAT_MAT4                    );
  _(GL_SAMPLER_1D                    );
  _(GL_SAMPLER_2D                    );
  _(GL_SAMPLER_3D                    );
  _(GL_SAMPLER_CUBE                  );
  _(GL_SAMPLER_1D_SHADOW             );
  _(GL_SAMPLER_2D_SHADOW             );
  _(GL_FLOAT_MAT2x3                  );
  _(GL_FLOAT_MAT2x4                  );
  _(GL_FLOAT_MAT3x2                  );
  _(GL_FLOAT_MAT3x4                  );
  _(GL_FLOAT_MAT4x2                  );
  _(GL_FLOAT_MAT4x3                  );
  _(GL_BYTE                          );
  _(GL_UNSIGNED_BYTE                 );
  _(GL_SHORT                         );
  _(GL_UNSIGNED_SHORT                );
  _(GL_INT                           );
  _(GL_UNSIGNED_INT                  );
  _(GL_FLOAT                         );
  _(GL_DOUBLE                        );
#undef _
}

map<uint, string>& gl_enum_names() {
  static map<uint, string> table;
  if (table.empty()) add_enums(table);
  return table;
}
