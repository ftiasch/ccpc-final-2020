#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int n = opt<int>("n");
  while (T--) {
    const int r = rnd.next(1, 2016);
    printf("%d %d\n", n, r);
    for (int i = 0; i < n; ++i) {
      printf("%d%c", rnd.next(1, 2016), " \n"[i + 1 == n]);
    }
  }
}
