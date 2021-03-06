#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  while (T--) {
    int n;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(1, opt<int>("maxn"));
    }
    putchar('0' + rnd.next(1, 9));
    for (int i = 1; i < n; ++i) {
      putchar('0' + rnd.next(0, 9));
    }
    puts("");
  }
}
