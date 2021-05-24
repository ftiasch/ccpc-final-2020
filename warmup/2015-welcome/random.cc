#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  while (T--) {
    if (rnd.next(0, 1)) {
      printf("%d\n", rnd.next(1, 2015));
    } else {
      printf("%d\n", rnd.next(2016, 1000000000));
    }
  }
}
