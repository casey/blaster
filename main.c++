#import "app.h"

int main(int argc, char** argv) {
  return top_t(rmr.nothing()).spawn<app_t>(argc, argv);
}
