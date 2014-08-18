enum struct gizmo_t {
  cell0,  cell1,  cell2,  cell3,  cell4,  cell5,  cell6,  cell7,
  cell8,  cell9,  cell10, cell11, cell12, cell13, cell14, cell15,
  cell16, cell17, cell18, cell19, cell20, cell21, cell22, cell23,
  cell24, cell25, cell26, cell27, cell28, cell29, cell30, cell31,
  cell32, cell33, cell34, cell35, cell36, cell37, cell38, cell39,
  cell40, cell41, cell42, cell43, cell44, cell45, cell46, cell47,
  cell48, cell49, cell50, cell51, cell52, cell53, cell54, cell55,
  cell56, cell57, cell58, cell59, cell60, cell61, cell62, cell63,

  button0,  button1,  button2,  button3,  button4,  button5,  button6,  button7,
  button8,  button9,  button10, button11, button12, button13, button14, button15,
  button16, button17, button18, button19, button20, button21, button22, button23,
  button24, button25, button26, button27, button28, button29, button30, button31,
  button32, button33, button34, button35, button36, button37, button38, button39,
  button40, button41, button42, button43, button44, button45, button46, button47,
  button48, button49, button50, button51, button52, button53, button54, button55,
  button56, button57, button58, button59, button60, button61, button62, button63,

  knob0,  knob1,  knob2,  knob3,  knob4,  knob5,  knob6,  knob7, knob8,  knob9,  knob10,

  slider,

  cell_first   = cell0,
  cell_last    = cell63,
  button_first = button0,
  button_last  = button63,
  knob_first   = knob0,
  knob_last    = knob10,

  down  = button60,
  left  = button61,
  up    = button62,
  right = button63
};

struct $gizmo {
  $gizmo(gizmo_t _) : _(_) { }
  gizmo_t _;

  static constexpr int   cell_count = 1 + (int)gizmo_t::  cell_last - (int)gizmo_t::  cell_first;
  static constexpr int button_count = 1 + (int)gizmo_t::button_last - (int)gizmo_t::button_first;
  static constexpr int   knob_count = 1 + (int)gizmo_t::  knob_last - (int)gizmo_t::  knob_first;

  static constexpr int count = cell_count + button_count + knob_count + 1;

  const char* type  () const;
  const char* name  () const;
  bool        cell  () const;
  bool        button() const;
  bool        knob  () const;
  bool        slider() const;
  int         number() const;
};

inline $gizmo $(gizmo_t gizmo) { return $gizmo(gizmo); }

ostream& operator<<(ostream&, const $gizmo&);
