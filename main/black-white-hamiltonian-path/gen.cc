#include "testlib.h"
#include <algorithm>
#include <cassert>

// Random sample $k$ elements from $n$ elements with equal probability.
// Time Complexity: $O(k \log k)$
template <typename Int> std::vector<Int> random_subset(Int n, int k) {
  ensuref(n >= k, "random_subset failed: n >= k");
  std::set<Int> set;
  for (Int i = n - k; i < n; ++i) {
    Int p = rnd.next(static_cast<Int>(0), i);
    if (set.count(p)) {
      set.insert(i);
    } else {
      set.insert(p);
    }
  }
  std::vector<Int> result;
  for (auto elem : set) {
    result.push_back(elem);
  }
  return result;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto type = std::atoi(argv[3]);
  std::vector<int> ns;
  int N = 2000;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  if (N >= 3)
    ns.push_back(N);
  for (auto &n : ns) {
    std::vector<std::string> s(n, std::string(n, '0'));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (type != 0)
          s[i][j] = '0' + type - 1;
        else
          s[i][j] = rnd.next(2) + '0';
        s[j][i] = s[i][j];
      }
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      puts(s[i].c_str());
    }
  }
  return 0;
}
