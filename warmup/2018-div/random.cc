#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int maxn = opt<int>("n");
  while (T--) {
    int n = rnd.next(1, maxn);
    int m = rnd.next(1, maxn);
    printf("%d %d\n", n, m);
  }
}
