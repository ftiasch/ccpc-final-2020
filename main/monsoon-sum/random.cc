#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  const int q = opt<int>("q");
  const int m = opt<int>("m");
  const int n = opt<int>("n");
  const int xy = opt<int>("xy");
  while (T--) {
    // int n = rnd.next(std::max(m, 2), v);
    int x = rnd.next(0, xy);
    int y = rnd.next(0, xy);
    printf("%d %d %d %d\n", rnd.next(1, n), x, y, q);
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
