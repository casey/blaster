#import "syphon.h"
#import "rmr.h"
#import "window.h"
#import "fmt.h"
#import "once.h"
#import "gl.h"

#import <Syphon/SyphonServer.h>

struct syphon_t::data_t {
  window_t&     window;
  SyphonServer* server = nullptr;
  bool          bound  = false;
};

syphon_t::syphon_t(window_t& window) : __(*new data_t{window}) {
  auto name = [[NSString alloc] initWithUTF8String: window.name().c_str()];

  __.server = [[SyphonServer alloc]
    initWithName: name
    context:      window.core_context()
    options:      nil
  ];

  [name release];
}

syphon_t::~syphon_t() {
  [__.server stop];
  [__.server release];
  delete &__;
}

void syphon_t::bind() {
  static once_t first;
  __.bound && rmr.die("syphon.bind: double bind");
  auto framebuffer = __.window.framebuffer_size();
  NSSize size = NSMakeSize(framebuffer.x(), framebuffer.y());
  auto status = [__.server bindToDrawFrameOfSize: size];
  if (first) __.window.gl().expect_invalid_operation();
  if (status != YES) rmr.die("syphon.bind: bindToDrawFrameOfSize failed: %"_fmt((int)status));
  __.bound = true;
}

void syphon_t::publish() {
  [__.server unbindAndPublish];
  __.bound = false;
}

bool syphon_t::has_clients() {
  return [__.server hasClients];
}
