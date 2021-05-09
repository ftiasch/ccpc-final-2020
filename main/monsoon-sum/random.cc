#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  const int v = opt<int>("v");
  const int q = opt<int>("q");
  while (T--) {
    const int opt_m = opt<int>("m");
    const int m = has_opt("random") ? rnd.next(1, opt_m) : opt_m;
    int n = rnd.next(std::max(m, 2), v);
    int x = rnd.next(0, v);
    printf("%d %d %d\n", n, x, q);
    for (int _ = 0; _ < q; ++_) {
      int a, b;
      do {
        a = rnd.next(1, m);
        b = rnd.next(1, m);
      } while (a + b > n);
      printf("%d %d\n", a, b);
    }
  }
}
