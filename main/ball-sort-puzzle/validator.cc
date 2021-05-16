#include "testlib.h"

int main() {
  registerValidation();
  int sum_m = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(n, 200000, "m");
    inf.readEoln();
    std::vector<int> count(n);
    for (int i = 0; i < m; ++i) {
      int size = inf.readInt(0, 2);
      for (int j = 0; j < size; ++j) {
        inf.readSpace();
        count[inf.readInt(1, n) - 1]++;
      }
      inf.readEoln();
    }
    for (int i = 0; i < n; ++i) {
      ensure(count[i] == 2);
    }
    ensuref((sum_m += m) <= 200000, "sum of m exceeds");
  }
  inf.readEof();
}
