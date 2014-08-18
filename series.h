template<typename T>
struct series_t {
  struct entry_t {
    double time;
    T  value;
  };

  double max_age;
  list<entry_t> data;

  typename list<entry_t>::iterator begin() { return data.begin(); };
  typename list<entry_t>::iterator end  () { return data.end  (); };

  series_t(double age) : max_age(age) {}

  series_t& update() {
    while(!data.empty()) {
      auto age = rmr.now() - data.front().time;
      if (age < max_age) break;
      data.pop_front();
    }
    return *this;
  }

  series_t& operator<<(T x) {
    data.push_back({rmr.now(), x});
    return *this;
  }

  T sum() {
    update();
    T s{};
    for (auto& r : data) {
      s += r.value;
    }
    return s;
  }

  T mean() {
    return T(sum()) / data.size();
  }
};
