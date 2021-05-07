#include "testlib.h"
#include <cassert>
#include <cmath>
#include <functional>
#include <queue>
#include <vector>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto max_w = std::atoi(argv[3]);
  min_n = std::max(2, min_n);
  max_n = std::max(2, max_n);
  int N = 250;
  std::vector<std::pair<int, int>> ns;
  while (N) {
    int n = rnd.next(min_n, max_n);
    int m = rnd.next(min_n, max_n);
    if (N < std::max(n, m)) {
      break;
    }
    ns.emplace_back(n, m);
    N -= std::max(n, m);
  }
  for (auto &e : ns) {
    int n = e.first;
    int m = e.second;
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j)
          putchar(' ');
        printf("%d", rnd.next(max_w));
      }
      puts("");
    }
  }
  return 0;
}
