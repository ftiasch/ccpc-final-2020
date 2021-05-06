#include "testlib.h"
#include <functional>
#include <set>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int sm = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 500000, "k");
    inf.readEoln();
    sm += m;
    ensuref(sm <= 500000, "sum of m <= 500000");
  }
  inf.readEof();
  return 0;
}
