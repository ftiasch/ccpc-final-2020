#include "testlib.h"

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int sn = 0;
  while (!inf.eof()) {
    int n = inf.readInt(3, 2000, "n");
    inf.readEoln();
    sn += n;
    ensuref(sn <= 2000, "sum of all n <= 2000");
    std::vector<std::string> c(n);
    for (int i = 0; i < n; ++i) {
      c[i] = inf.readToken(format("[01]{%d,%d}", n, n), format("c[%d]", i + 1));
      inf.readEoln();
    }
    for (int i = 0; i < n; ++i) {
      ensuref(c[i][i] == '0', "c_{i,i}=0");
      for (int j = 0; j < n; ++j) {
        ensuref(c[i][j] == c[j][i], "c_{i,j}=c_{j,i}");
      }
    }
  }
  inf.readEof();
  return 0;
}
