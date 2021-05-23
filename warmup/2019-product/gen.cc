#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int m = std::atoi(argv[2]);
  for (int _ = 0; _ < T; ++_) {
    int a = rnd.next(1, m);
    int b = rnd.next(1, m);
    int c = rnd.next(1, m);
    int d = rnd.next(1, m);
    if (a > b) {
      std::swap(a, b);
    }
    if (c > d) {
      std::swap(c, d);
    }
    printf("%d %d %d %d\n", a, b, c, d);
  }
}
