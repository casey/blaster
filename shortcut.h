struct shortcut_t {
  shortcut_t(const string&);
  shortcut_t(const key_e&);
  bool operator==(const shortcut_t&) const;
  u32 code() const;
  u32 key() const;
  u32 mods() const;
private:
  u32 _code;
};

namespace std {
  template<>
  struct hash<shortcut_t> {
    size_t operator()(shortcut_t const&) const;
  };
}
