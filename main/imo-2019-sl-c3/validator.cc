#include "testlib.h"

int main() {
  registerValidation();

  int sum_n = 0;
  int sum_q = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();
    inf.readToken(format("[01]{%d}", n), "s");
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
      int l = inf.readInt(1, n, format("l[%d]", i + 1));
      inf.readSpace();
      inf.readInt(l, n, format("r[%d]", i + 1));
      inf.readEoln();
    }
    ensuref((sum_n += n) <= 200000, "the sum of n exceeds");
    ensuref((sum_q += q) <= 200000, "the sum of q exceeds");
  }

  inf.readEof();
}
