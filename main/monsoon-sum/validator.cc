#include "testlib.h"

static const int MOD = 998244353;

int main() {
  registerValidation();
  int sum_q = 0;
  int sum_m = 0;
  while (!inf.eof()) {
    int n = inf.readInt(2, 1000000000, "n");
    inf.readSpace();
    int x = inf.readInt(0, MOD - 1, "x");
    inf.readSpace();
    int y = inf.readInt(0, MOD - 1, "y");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();
    ensuref((sum_q += q) <= 200000, "sum of q exceeds");
    int m = 0;
    for (int i = 1; i <= q; ++i) {
      int a = inf.readInt(1, 5000, format("a[%d]", i));
      inf.readSpace();
      int b = inf.readInt(1, 5000, format("b[%d]", i));
      inf.readEoln();
      ensuref(a + b <= n, "a + b > n");
      m = std::max(m, std::max(a, b));
    }
    ensuref((sum_m += m) <= 5000, "sum of m exceeds");
  }
  inf.readEof();
}
