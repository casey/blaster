template <typename T>
struct tree {
  using void_f = fun_t<void(T&)>;
  using pred_f = fun_t<void(T&)>;

  // turn this into count();
  static int count_children(T& t) {
    int i = 0;
    for (T& child : t) i++;
    return i;
  }

  static bool is_leaf(T& t) {
    return count_children(t) == 0;
  }

  static int depth(T& t) {
    if (t.is_root()) return 0;
    return depth(t.parent()) + 1;
  }

  static bool down(T& t, const pred_f& f) {
    if (f(t)) return true;
    for (T& child : t) if (down(t, f)) return true;
    return false;
  }

  static bool up(T& t, const pred_f& f) {
    if (f(t)       ) return true;
    if (t.is_root()) return false;
    return up(t.parent(), f);
  }

  static bool descendants(T& t, const pred_f& f) {
    for (T& child : t) if (down(child, f)) return true;
    return false;
  }

  static bool ancestors(T& t, const pred_f& f) {
    if (t.is_root()) return false;
    return up(t.parent(), f);
  }

  static bool leaves(T& t, const pred_f& f) {
    if (t.is_leaf()) return f(t);
    for (T& child : t) if (leaves(child, f)) return true;
    return false;
  }

  static bool level(uint l, T& t, const pred_f& f) {
    if (l == 0) return f(t);
    for (T& child : t) {
      if (level(l - 1, t, f)) return true;
    }
    return false;
  }

  pred_f ignore(pred_f& f) { return [&](T& _) { f(_); return false; }; }
  pred_f invert(pred_f& f) { return [&](T& _) {       return !f(_); }; }

  void each_leaf (T& t, const void_f& f) {         leaves  (t, ignore(f)); }
  bool any_leaf  (T& t, const pred_f& f) { return  leaves  (t, f        ); }
  bool all_leaves(T& t, const pred_f& f) { return !leaves  (t, invert(f)); }
  bool no_leaves (T& t, const pred_f& f) { return !any_leaf(t, f        ); }

  // any
  // all
  // none
  // each
  // collect
};
