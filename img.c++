#import "img.h"
#import "rmr.h"
#import "fmt.h"

struct img_t::data_t {
  size_t width   = 0;
  size_t height  = 0;
  u8*    storage = 0;
};

img_t::img_t() : img_t(0, 0) {
}

img_t::img_t(size_t width, size_t height) : __(*new data_t) {
  resize(width, height);
}

img_t::img_t(img_t&& x) : __(*new data_t{x.width(), x.height(), x.bytes()}) {
  x.__.width   = 0;
  x.__.height  = 0;
  x.__.storage = nullptr;
}

img_t::img_t(const img_t& x) : img_t(x.width(), x.height()) {
  for (int i = 0; i < x.width() * x.height(); i++) {
    data()[i] = x.data()[i];
  }
}

img_t::~img_t() {
  delete[]  __.storage;
  delete   &__;
}

pixel_t* img_t::begin() {
  return data();
}

pixel_t* img_t::end() {
  return data() + width() * height();
}

size_t img_t::height() const { return __.height;          }
size_t img_t::width()  const { return __.width;           }
size_t img_t::count()  const { return width() * height(); }

void img_t::resize(size_t w, size_t h) {
  if (width() == w && h == height()) return;
  delete[] __.storage;
  __.width   = w;
  __.height  = h;
  __.storage = w * h == 0 ? nullptr : new u8[w * h * 4];
}

void img_t::clear() {
  for (int i = 0; i < count() * 4; i++) {
    bytes()[i] = 0;
  }
}

const pixel_t* img_t::data() const  { return (pixel_t*)__.storage; }
pixel_t*       img_t::data()        { return (pixel_t*)__.storage; }
const u8*      img_t::bytes() const { return           __.storage; }
u8*            img_t::bytes()       { return           __.storage; }

pixel_t& img_t::operator()(size_t x, size_t y) {
  x < width () || rmr.die("img_t.operator(): x out of bounds");
  y < height() || rmr.die("img_t.operator(): y out of bounds");
  return *(data() + x + width() * y);
}

#import <png.h>

static_assert(std::is_same<png_byte, u8>::value, "png_byte is not u8");

img_t read_png(const string& file_name) {
  u8 header[8];

  FILE *fp = fopen(file_name.c_str(), "rb");
  if (!fp) rmr.die("[read_png_file] File % could not be opened for reading"_fmt(file_name));
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) rmr.die("[read_png_file] File % is not recognized as a PNG file"_fmt(file_name));

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) rmr.die("[read_png_file] png_create_read_struct failed");

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) rmr.die("[read_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[read_png_file] Error during init_io");

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  int number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[read_png_file] Error during read_image");

  png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

  img_t img(width, height);

  if (color_type != PNG_COLOR_TYPE_RGBA) rmr.die("read_png: color type not RGBA");
  if (bit_depth  != 8                  ) rmr.die("read_png: bit depth not 8");

  for (int y = 0; y < height; y++) row_pointers[height - y - 1] = img.bytes() + y * png_get_rowbytes(png_ptr, info_ptr);

  png_read_image(png_ptr, row_pointers);

  fclose(fp);

  return img;
}

img_t read_bits(const string& file_name, int width, int height) {
  auto bin = rmr.slurp(file_name);
  img_t img(width, height);
  u8* p = img.bytes();
  for (int i = 0; i < bin.length(); i++) {
    char c = bin[i];
    for (int position = 0; position < 8; position++) {
      p[0] = p[1] = p[2] = (c & (1 << position)) ? 255 : 0;
      p[3] = 255;
      p += 4;
    }
  }
  return img;
}

void write_png(const string& file_name, const img_t& img) {
  write_png(file_name, img.bytes(), img.width(), img.height());
}

void write_png(const string& file_name, const u8 *pixels, int width, int height) {
  png_structp png_ptr;
  png_infop info_ptr;

  FILE *fp = fopen(file_name.c_str(), "wb");
  if (!fp) rmr.die("[write_png] File %s could not be opened for writing"_fmt % file_name);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) rmr.die("[write_png] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) rmr.die("[write_png] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[write_png] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[write_png] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
      8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[write_png] Error during writing bytes");

  png_byte *row_pointers[height];

  for(int i = 0; i < height; i++) {
      row_pointers[height - 1 - i] = const_cast<u8*>(pixels + i * width * 4);
  }

  png_write_image(png_ptr, row_pointers);

  /* end write */
  if (setjmp(png_jmpbuf(png_ptr))) rmr.die("[write_png] Error during end of write");

  png_write_end(png_ptr, NULL);

  fclose(fp);
}
