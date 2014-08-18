#import "target.h"
#import "rmr.h"

void debug_target_t::operator()(const       tick_e& e) { rmr << "debug_target: tick"      ; }
void debug_target_t::operator()(const     render_e& e) { rmr << "debug_target: render"    ; }
void debug_target_t::operator()(const       draw_e& e) { rmr << "debug_target: draw"      ; }
void debug_target_t::operator()(const       quit_e& e) { rmr << "debug_target: quit"      ; }
void debug_target_t::operator()(const     rename_e& e) { rmr << "debug_target: rename"    ; }
void debug_target_t::operator()(const     resize_e& e) { rmr << "debug_target: resize"    ; }
void debug_target_t::operator()(const       hide_e& e) { rmr << "debug_target: hide"      ; }
void debug_target_t::operator()(const       show_e& e) { rmr << "debug_target: show"      ; }
void debug_target_t::operator()(const  character_e& e) { rmr << "debug_target: character" ; }
void debug_target_t::operator()(const    mouseup_e& e) { rmr << "debug_target: mouseup"   ; }
void debug_target_t::operator()(const  mousedown_e& e) { rmr << "debug_target: mousedown" ; }
void debug_target_t::operator()(const  mousemove_e& e) { rmr << "debug_target: mousemove "; }
void debug_target_t::operator()(const mouseenter_e& e) { rmr << "debug_target: mouseenter"; }
void debug_target_t::operator()(const     scroll_e& e) { rmr << "debug_target: scroll"    ; }
void debug_target_t::operator()(const mouseleave_e& e) { rmr << "debug_target: mouseleave"; }
void debug_target_t::operator()(const    keydown_e& e) { rmr << "debug_target: keydown"   ; }
void debug_target_t::operator()(const      keyup_e& e) { rmr << "debug_target: keyup"     ; }
void debug_target_t::operator()(const  keyrepeat_e& e) { rmr << "debug_target: keyrepeat" ; }
void debug_target_t::operator()(const     verify_e& e) { rmr << "debug_target: verify"    ; }
void debug_target_t::operator()(const       push_e& e) { rmr << "debug_target: push"    ; }
