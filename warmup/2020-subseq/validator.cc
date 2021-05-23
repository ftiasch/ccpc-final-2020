#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 200000);
    inf.readEoln();
    inf.readToken(format("[012]{%d}", n));
    inf.readEoln();
    ensure((sum_n += n) <= 200000);
  }
  inf.readEof();
}
