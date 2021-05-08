#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int n = std::atoi(argv[2]);
  while (T--) {
    putchar('0' + rnd.next(1, 9));
    for (int i = 1; i < n; ++i) {
      putchar('0' + rnd.next(0, 9));
    }
    puts("");
  }
}
