#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 50, "n");
    inf.readEoln();
    auto p = inf.readInts(n, 1, n, "p", 1);
    inf.readEoln();
    std::sort(p.begin(), p.end());
    ensuref(std::unique(p.begin(), p.end()) == p.end(),
            "p is not a permutation");
    ensuref((sum_n += n) <= 500, "sum of n exceeds");
  }
  inf.readEof();
}
