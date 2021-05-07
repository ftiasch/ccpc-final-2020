#include "testlib.h"
#include <functional>
#include <set>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int snm = 0, cnt = 0;
  while (!inf.eof()) {
    int n = inf.readInt(2, 250, "n");
    inf.readSpace();
    int m = inf.readInt(2, 250, "m");
    inf.readEoln();
    snm += std::max(n, m);
    ensuref(snm <= 250, "sum of max(n, m) <= 250");
    // if (n > 200 || m > 200) {
    //   cnt += 1;
    // }
    // ensuref(cnt <= 3, "number large case <= 3");
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j) {
          inf.readSpace();
        }
        inf.readInt(0, 1000000, format("w[%d][%d]", i + 1, j + 1));
      }
      inf.readEoln();
    }
  }
  inf.readEof();
  return 0;
}
