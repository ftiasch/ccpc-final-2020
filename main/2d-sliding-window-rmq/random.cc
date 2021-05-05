#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  int v = opt<int>("v");
  while (T--) {
    int n = has_opt("n") ? opt<int>("n") : rnd.next(1, opt<int>("maxn"));
    int m = has_opt("m") ? opt<int>("m") : rnd.next(1, opt<int>("maxn"));
    int h = has_opt("h") ? opt<int>("h") : rnd.next(1, n);
    int w = has_opt("w") ? opt<int>("w") : rnd.next(1, m);
    int k = has_opt("k") ? opt<int>("k")
                         : rnd.next(1, std::min(h * w, opt<int>("maxk")));
    printf("%d %d %d %d %d\n", n, m, h, w, k);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%d%c", rnd.next(1, v), " \n"[j + 1 == m]);
      }
    }
  }
}
