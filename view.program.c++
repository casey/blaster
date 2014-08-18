#import "view.program.h"

#import "sym.h"
#import "gl.h"

struct program_v::data_t {
  sym_t program;
};

program_v::program_v(const sym_t& program) : __(*new data_t{program})  {
  gl()
  .new_vbo("quad")
  .upload_ccw_quad("quad")
  ;
}

void program_v::operator()(const draw_e& e) {
  gl()
  .prepare(__.program)
  .pack({"position"}, "quad")
  .ready()
  .triangles()
  .draw_arrays()
  .done()
  ;
}
