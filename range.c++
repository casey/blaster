#import "range.h"
#import "rmr.h"

using iterator_t = range_t::iterator_t;

range_t::range_t(int max) : range_t(0, max) {}
range_t::range_t(int min, int max) : min(min), max(max) {
  if (min > max) rmr.fatal() << "range_t(): min greater than max:" << min << ">" << max;
}

iterator_t range_t::begin() const { return iterator_t(min); }
iterator_t range_t::end  () const { return iterator_t(max); }

iterator_t::iterator_t(int count) : count(count) {}

const int&  iterator_t::operator* () const                       { return count;               }
iterator_t& iterator_t::operator++()                             { count++; return *this;      }
iterator_t& iterator_t::operator+=(int n)                        { count += n; return *this;   }
bool        iterator_t::operator< (const iterator_t& that) const { return count < that.count;  }
bool        iterator_t::operator==(const iterator_t& that) const { return count == that.count; }
bool        iterator_t::operator!=(const iterator_t& that) const { return count != that.count; }
iterator_t  iterator_t::operator++(int) { count++; return iterator_t(count - 1); }
