#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 1000000);
    inf.readSpace();
    inf.readInt(-n, n);
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
      inf.readInt(1, n);
      if (i + 1 < n) {
        inf.readSpace();
      } else {
        inf.readEoln();
      }
    }
    ensure((sum_n += n) <= 5000000);
  }
  inf.readEof();
}
