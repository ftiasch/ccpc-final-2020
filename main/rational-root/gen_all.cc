#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <numeric>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto max_m = std::atoi(argv[1]);
  auto k = std::atoi(argv[2]);
  for (int n = 1; n <= max_m; ++n) {
    for (int m = 1; m <= max_m; ++m) {
      printf("%d %d %d\n", n, m, k);
    }
  }
  return 0;
}
