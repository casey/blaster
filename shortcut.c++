#import "shortcut.h"
#import "event.h"
#import "key.h"
#import "rmr.h"

shortcut_t::shortcut_t(const string& shortcut) {
  auto s = shortcut;
  u32 mods = 0;

  auto mod = [&](const string& prefix, u32 flag){
    if (s.find(prefix) == 0) {
      s.erase(0, prefix.length());
      mods |= flag;
    }
  };

  for(;;) {
    int l = s.length();
    mod("ctrl-",    GLFW_MOD_CONTROL);
    mod("control-", GLFW_MOD_CONTROL);
    mod("shift-",   GLFW_MOD_SHIFT  );
    mod("alt-",     GLFW_MOD_ALT    );
    mod("super-",   GLFW_MOD_SUPER  );
    mod("up-",      GLFW_MOD_UP     );
    mod("down-",    GLFW_MOD_DOWN   );
    mod("repeat-",  GLFW_MOD_REPEAT );
    if (s.length() == l) break;
  }

  if (!(mods & (GLFW_MOD_UP | GLFW_MOD_DOWN | GLFW_MOD_REPEAT))) {
    mods |= GLFW_MOD_DOWN;
  }

  u32 key;

  if      (s.length() == 1) key = rmr.upper(s[0]);
  else if (s == "tab"     ) key = GLFW_KEY_TAB;
  else if (s == "space"   ) key = GLFW_KEY_SPACE;
  else if (s == "enter"   ) key = GLFW_KEY_ENTER;
  else if (s == "return"  ) key = GLFW_KEY_ENTER;
  else if (s == "left"    ) key = GLFW_KEY_LEFT;
  else if (s == "right"   ) key = GLFW_KEY_RIGHT;
  else if (s == "up"      ) key = GLFW_KEY_UP;
  else if (s == "down"    ) key = GLFW_KEY_DOWN;
  else rmr.die("win.on: unrecognized shortcut: "s + s);

  _code = (mods << 16) | key;
}

shortcut_t::shortcut_t(const key_e& e) {
  u32 mods = 0;

  e.shift   && (mods |= GLFW_MOD_SHIFT  );
  e.control && (mods |= GLFW_MOD_CONTROL);
  e.alt     && (mods |= GLFW_MOD_ALT    );
  e.super   && (mods |= GLFW_MOD_SUPER  );
  e.up      && (mods |= GLFW_MOD_UP     );
  e.down    && (mods |= GLFW_MOD_DOWN   );
  e.repeat  && (mods |= GLFW_MOD_REPEAT );

  _code = (mods << 16) | e.key;
}

bool shortcut_t::operator==(const shortcut_t& rhs) const {
  return code() == rhs.code();
}

u32 shortcut_t::code() const {
  return _code;
}

u32 shortcut_t::mods() const {
  return code() >> 16;
}

u32 shortcut_t::key() const {
  return (code() << 16) >> 16;
}

size_t std::hash<shortcut_t>::operator()(shortcut_t const& s) const {
  return std::hash<decltype(s.code())>()(s.code());
}
