#include "testlib.h"

int main() {
  registerValidation();
  int sum_m = 0;
  int sum_q = 0;
  while (!inf.eof()) {
    const int m = inf.readInt(1, 16, "m");
    inf.readSpace();
    const int q = inf.readInt(1, 200000, "q");
    inf.readEoln();
    inf.readInts(1 << m, 0, (1 << m) - 1, "f");
    inf.readEoln();
    inf.readInts(1 << m, 0, (1 << m) - 1, "g");
    inf.readEoln();
    inf.readInts(1 << m, 0, (1 << m) - 1, "h");
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
      inf.readInt(0, (1 << m) - 1, format("a[%d]", i));
      inf.readSpace();
      inf.readInt(0, (1 << m) - 1, format("b[%d]", i));
      inf.readEoln();
    }
    ensuref((sum_m += (1 << m)) <= 100000, "sum of m exceeds");
    ensuref((sum_q += q) <= 200000, "sum of q exceeds");
  }
  inf.readEof();
}
