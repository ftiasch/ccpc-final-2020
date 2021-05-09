#include "testlib.h"

int main() {
  registerValidation();

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
  }

  inf.readEof();
}
