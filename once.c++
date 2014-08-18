#include "once.h"

once_t::once_t() : triggered(false) {};
  
once_t::operator bool() {
  if (triggered) return false;
  triggered = true;
  return true;
}
