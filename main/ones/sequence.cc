#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  for (int n = 1; n <= T; ++n) {
    printf("%d\n", n);
  }
}
