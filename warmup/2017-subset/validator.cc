#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  int tests = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 2000000, "n");
    inf.readSpace();
    inf.readInt(1, 2016, "r");
    inf.readEoln();
    inf.readInts(n, 1, 2016, "a");
    inf.readEoln();
    ensuref((sum_n += n) <= 2000000, "sum of n exceeds");
    ensuref((++tests) <= 10000, "the number of test cases exceeds");
  }
  inf.readEof();
}
