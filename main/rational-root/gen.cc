#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <numeric>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto min_m = std::atoi(argv[3]);
  auto max_m = std::atoi(argv[4]);
  auto k = std::atoi(argv[5]);
  int M = 500000;
  std::vector<int> ms;
  while (M >= min_m) {
    int m = rnd.next(min_m, std::min(max_m, M));
    ms.push_back(m);
    M -= m;
  }
  for (auto &m : ms) {
    printf("%d %d %d\n", rnd.next(min_n, max_n), m, k);
  }
  return 0;
}
