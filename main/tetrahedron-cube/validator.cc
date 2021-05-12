#include "testlib.h"

bool compare(const std::vector<int> &a, const std::vector<int> &b) {
  return a[0] != b[0] && a[1] != b[1] && a[2] != b[2];
}

int main() {
  registerValidation();

  int tests = 0;
  while (!inf.eof()) {
    std::vector<std::vector<int>> p;
    for (int i = 0; i < 4; ++i) {
      p.push_back(inf.readInts(3, -100, 100, "p[0]", 1));
      inf.readEoln();
    }
    ensuref(compare(p[0], p[1]), "p[0] & p[1] coincide");
    ensuref(compare(p[2], p[3]), "p[2] & p[3] coincide");
    ensuref((++tests) <= 100000, "number of tests exceeds");
  }
  inf.readEof();
}
