#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  int n, m;
  while (reader >> n >> m) {
    std::vector<std::pair<int, int>> towns(m);
    for (int i = 0; i < m; ++i) {
      int a, b;
      reader >> a >> b;
      --a;
      --b;
      if (a > b)
        std::swap(a, b);
      towns[i] = std::make_pair(a, b);
    }
    auto ok = [&](int bound) -> bool {
      std::vector<int> forbid(n + 1);
      for (const auto &pair : towns) {
        int a = pair.first;
        int b = pair.second;
        CHECK(a <= b);
        if (b - a > bound) {
          forbid[b]++;
          forbid[n]--;
          forbid[0]++;
          forbid[a]--;
        }
        if (n - 1 - b + a + 1 > bound) {
          forbid[a]++;
          forbid[b]--;
        }
      }
      for (int i = 0; i < n; ++i) {
        if (i)
          forbid[i] += forbid[i - 1];
        if (!forbid[i])
          return true;
      }
      return false;
    };
    auto solve = [&]() -> int {
      int l = 0, r = n;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (ok(mid))
          r = mid - 1;
        else
          l = mid + 1;
      }
      return r + 1;
    };
    printf("%d\n", solve());
  }
}
