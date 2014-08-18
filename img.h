struct pixel_t {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
};

struct img_t {
  img_t();
  img_t(size_t width, size_t height);
  img_t(const img_t&);
  img_t(img_t&&);
  ~img_t();
  size_t width()  const;
  size_t height() const;
  size_t count()  const;
  void resize(size_t width, size_t height);
  void clear();
  pixel_t& operator()(size_t x, size_t y);
  const pixel_t* data() const;
  pixel_t* data();
  const u8* bytes() const;
  u8* bytes();

  pixel_t* begin();
  pixel_t* end();
private:
  struct data_t;
  data_t& __;
};

img_t read_png(const string& file_name);
img_t read_bits(const string& file_name, int width, int height);
void write_png(const string& file_name, const u8 *pixels, int width, int height);
void write_png(const string& file_name, const img_t& img);
