#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  for (int n : rnd.perm(T, 1)) {
    printf("%d\n", n);
  }
}
