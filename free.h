[[noreturn]] bool rmr_die(const string &);
const sym_t& null_sym();

struct whatever_t { };
struct nothing_t  { };

struct noncopyable_t {
  noncopyable_t()                                = default;
  ~noncopyable_t()                               = default;
  noncopyable_t(const noncopyable_t&)            = delete;
  noncopyable_t& operator=(const noncopyable_t&) = delete;
};

struct nonexistent_t : noncopyable_t {
  nonexistent_t() = delete;
};
