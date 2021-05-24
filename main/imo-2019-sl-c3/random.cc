#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  // const int n = opt<int>("n");
  const int q = opt<int>("q");
  while (T--) {
    int n;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(1, opt<int>("maxn"));
    }
    printf("%d %d\n", n, q);
    printf("%s\n", rnd.next(format("[01]{%d}", n)).c_str());
    for (int _ = 0; _ < q; ++_) {
      int l = rnd.next(1, n);
      int r = rnd.next(1, n);
      if (l > r) {
        std::swap(l, r);
      }
      printf("%d %d\n", l, r);
    }
  }
}
