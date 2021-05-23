#include "testlib.h"

const int INF = 1000000000;

int main() {
  registerValidation();
  int tests = 0;
  while (!inf.eof()) {
    tests++;
    int a = inf.readInt(1, INF);
    inf.readSpace();
    inf.readInt(a, INF);
    inf.readSpace();
    int c = inf.readInt(1, INF);
    inf.readSpace();
    inf.readInt(c, INF);
    inf.readEoln();
  }
  ensure(tests <= 100000);
  inf.readEof();
}
