#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int lo = opt<int>("lo");
  const int hi = opt<int>("hi");
  for (int n : rnd.perm(hi - lo + 1)) {
    printf("%d\n", lo + n);
  }
}
