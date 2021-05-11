#include "testlib.h"

static const int INF = 1e9;

int main() {
  registerValidation();
  int tests = 0;
  while (!inf.eof()) {
    static const char *NAMES = "PQAB";
    std::vector<std::vector<int>> points;
    for (int i = 0; i < 4; ++i) {
      points.push_back(inf.readInts(3, -INF, INF, std::string(NAMES[i], 1), 1));
      inf.readEoln();
    }
    bool differ = false;
    for (int i = 0; i < 3; ++i) {
      differ |= points[2][i] != points[3][i];
    }
    ensuref(differ, "A and B coincide");
    ensuref((++tests) <= 100000, "number of tests exceeds");
  }
  inf.readEof();
}
