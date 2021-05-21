#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int m = opt<int>("m");
  const int q = opt<int>("q");
  while (T--) {
    printf("%d %d\n", m, q);
    for (int i = 0; i < 1 << m; ++i) {
      printf("%d%c", rnd.next(0, (1 << m) - 1), " \n"[i + 1 == (1 << m)]);
    }
    for (int i = 0; i < 1 << m; ++i) {
      printf("%d%c", rnd.next(0, (1 << m) - 1), " \n"[i + 1 == (1 << m)]);
    }
    for (int i = 0; i < 1 << m; ++i) {
      printf("%d%c", rnd.next(0, (1 << m) - 1), " \n"[i + 1 == (1 << m)]);
    }
    for (int i = 0; i < q; ++i) {
      int l = rnd.next(0, (1 << m) - 1);
      int r = rnd.next(0, (1 << m) - 1);
      printf("%d %d\n", l, r);
    }
  }
}
