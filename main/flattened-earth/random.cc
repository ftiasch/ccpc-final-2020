#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  while (T--) {
    int n, m;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(2, opt<int>("maxn"));
    }
    if (has_opt("m")) {
      m = opt<int>("m");
    } else {
      m = rnd.next(1, opt<int>("maxm"));
    }
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
      int a, b;
      if (has_opt("maxlen")) {
        int length = rnd.next(0, opt<int>("maxlen"));
        a = rnd.next(0, n - 1) + 1;
        b = (a - 1 + length) % n + 1;
      } else {
        a = rnd.next(1, n);
        b = rnd.next(1, n);
      }
      printf("%d %d\n", a, b);
    }
  }
}
