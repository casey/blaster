struct val_t {
  static val_t parse(const string&);

  val_t(                         ); // null
  val_t(const char*              ); // string
  val_t(const string&            ); // string
  val_t(double                   ); // number
  val_t(bool                     ); // boolean
  val_t(const vector<val_t>&     ); // array
  val_t(init_t<val_t>            ); // array
  val_t(const map<string, val_t>&); // object
  val_t(void*                    ) = delete;

  ~val_t();
  
  bool is_null   (); void*                     as_null   (); void*                     nil();
  bool is_string (); const string&             as_string (); const string&             str();
  bool is_number (); double                    as_number (); double                    num();
  bool is_boolean(); bool                      as_boolean(); bool                      bln();
  bool is_array  (); const vector<val_t>&      as_array  (); const vector<val_t>&      ary();
  bool is_object (); const map<string, val_t>& as_object (); const map<string, val_t>& obj();

  val_t get(int);
  val_t get(const string&);
  bool  has(const string&);

  template<typename T>
  val_t get(const string& key, T otherwise) {
    return has(key) ? get(key) : val_t(otherwise);
  }

  val_t(const val_t&);
  val_t& operator=(const val_t&);
  string dump();
  explicit operator bool() const;

  struct data_t;
  data_t& __;
};

ostream& operator<<(ostream&, val_t);
