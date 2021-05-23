#include "testlib.h"

int main(int argc, char *argv[]) {
  registerValidation();
  int tests = 0;
  while (!inf.eof()) {
    inf.readInt(1, 1000000000, "n");
    inf.readEoln();
    ensuref((++tests) <= 10, "the number of tests exceeds");
  }
  inf.readEof();
}
