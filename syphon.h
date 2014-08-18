struct syphon_t {
  syphon_t(window_t&);
  ~syphon_t();

  void bind();
  void publish();
  bool has_clients();

private:
  struct data_t;
  data_t& __;
};
