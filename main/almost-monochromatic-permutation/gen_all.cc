#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <numeric>

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
  auto n = std::atoi(argv[1]);
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      edges.emplace_back(i, j);
    }
  }
  int m = edges.size();
  std::set<std::vector<int>> all;
  for (int mask = 0; mask < (1 << m); ++mask) {
    if (mask && (mask % 2 == 0))
      continue;
    std::vector<int> vs;
    for (int i = 0; i < m; ++i)
      if (mask >> i & 1) {
        vs.push_back(edges[i].first * n + edges[i].second);
      }
    std::vector<int> repr = vs;
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    do {
      auto t = vs;
      for (size_t i = 0; i < t.size(); i++) {
        int u = p[t[i] / n], v = p[t[i] % n];
        if (u > v)
          std::swap(u, v);
        t[i] = u * n + v;
      }
      std::sort(t.begin(), t.end());
      if (t < repr)
        repr = t;
    } while (std::next_permutation(p.begin(), p.end()));
    if (all.count(repr))
      continue;
    all.insert(repr);
  }
  for (auto &e : all) {
    std::vector<std::vector<int>> g(n, std::vector<int>(n, 0));
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end());
    for (auto &x : e) {
      g[p[x / n]][p[x % n]] = 1;
      g[p[x % n]][p[x / n]] = 1;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        putchar(g[i][j] + '0');
      }
      puts("");
    }
  }
  return 0;
}
