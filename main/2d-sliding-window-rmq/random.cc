#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  int n = opt<int>("n");
  int m = opt<int>("m");
  int v = opt<int>("v");
  while (T--) {
    int h = has_opt("h") ? opt<int>("h") : rnd.next(1, n);
    int w = has_opt("w") ? opt<int>("w") : rnd.next(1, m);
    int k = std::min(h * w, opt<int>("k"));
    printf("%d %d %d %d %d\n", n, m, h, w, k);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%d%c", rnd.next(1, v), " \n"[j + 1 == m]);
      }
    }
  }
}
