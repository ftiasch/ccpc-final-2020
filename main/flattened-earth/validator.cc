#include "testlib.h"

#include <bits/stdc++.h>

int main() {
  registerValidation();
  int sum_n = 0;
  int sum_m = 0;
  while (!inf.eof()) {
    int n = inf.readInt(2, 200000);
    inf.readSpace();
    int m = inf.readInt(1, 200000);
    inf.readEoln();
    ensure((sum_n += n) <= 200000);
    ensure((sum_m += m) <= 200000);
    for (int i = 0; i < m; ++i) {
      inf.readInt(1, n);
      inf.readSpace();
      inf.readInt(1, n);
      inf.readEoln();
    }
  }
  inf.readEof();
}
