#include "testlib.h"

#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  const int offset = opt<int>("offset");
  const int count = opt<int>("count");
  std::vector<int> perm(n);
  std::iota(perm.begin(), perm.end(), 1);
  for (int i = 0; i < offset; ++i) {
    std::next_permutation(perm.begin(), perm.end());
  }
  for (int i = 0; i < count; ++i) {
    printf("%d\n", n);
    for (int j = 0; j < n; ++j) {
      printf("%d%c", perm[j], " \n"[j + 1 == n]);
    }
    if (!std::next_permutation(perm.begin(), perm.end())) {
      break;
    }
  }
}
