#import "val.h"

void val_roundtrip(const string& input) {
  auto v = val_t::parse(input);
  const string output = v.dump();

  if (input.compare(output) != 0) {
    rmr << "val_test: roundtrip failed:";
    rmr << "input: "  << input;
    rmr << "output:" << output;
    FAIL();
  }
}

TEST(val) {
  val_roundtrip("null");
  val_roundtrip("1.0");
  val_roundtrip("-1.5");
  val_roundtrip("true");
  val_roundtrip("false");
  val_roundtrip("\"hello\"");
  val_roundtrip("[1.0,2.0,3.0]");
  val_roundtrip("[[],[],[],true,false,null]");
  val_roundtrip("{}");
  val_roundtrip("{\"hello\":27.0,\"bob\":true}");
  val_roundtrip(R"({"hello":2.0,"this":[],"what":null})");
}
