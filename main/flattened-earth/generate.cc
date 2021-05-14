#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ensure(argc > 4);
  int T = opt<int>("T");
  const int n = opt<int>("n");
  const int m = opt<int>("m");
  const int d = opt<int>("d");
  while (T--) {
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
      int a = rnd.next(1, n);
      int b = ((rnd.next(a - d, a + d) - 1) % n + n) % n + 1;
      printf("%d %d\n", a, b);
    }
  }
}
