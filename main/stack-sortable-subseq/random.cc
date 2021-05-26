#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  while (T--) {
    const int n = has_opt("n") ? opt<int>("n") : rnd.next(1, opt<int>("maxn"));
    printf("%d\n", n);
    std::vector<int> p(n);
    if (has_opt("id")) {
      std::iota(p.begin(), p.end(), 1);
    } else {
      p = rnd.perm(n, 1);
    }
    for (int i = 0; i < n; ++i) {
      printf("%d%c", p[i], " \n"[i + 1 == n]);
    }
  }
}
