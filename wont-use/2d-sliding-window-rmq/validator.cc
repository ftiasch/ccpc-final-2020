#include "testlib.h"

#include "common.h"

int main() {
  registerValidation();
  int sum_nm = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int m = inf.readInt(1, N, "m");
    inf.readSpace();
    int h = inf.readInt(1, n, "h");
    inf.readSpace();
    int w = inf.readInt(1, m, "w");
    inf.readSpace();
    inf.readInt(1, std::min(h * w, K), "k");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
      inf.readInts(m, 1, A, format("a[%d]", i + 1));
      inf.readEoln();
    }
    ensuref((sum_nm += n * m) <= N * N, "the sum of n * m exceeds");
  }
  inf.readEof();
}
