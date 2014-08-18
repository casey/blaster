#import "timer.h"

timer_t::timer_t() {
  reset();
}

double timer_t::elapsed() {
  auto end = std::chrono::system_clock::now();
  auto dur = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
  return dur.count();
}

u64 timer_t::ms() {
  auto end = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

u64 timer_t::ns() {
  auto end = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

u64 timer_t::us() {
  auto end = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void timer_t::reset() {
  start = std::chrono::system_clock::now();
}
