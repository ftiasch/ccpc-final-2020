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
    auto calc = [&](int broken) -> int {
      int ret = 0;
      for (const auto &pair : towns) {
        int a = pair.first;
        int b = pair.second;
        CHECK(a <= b);
        if (a <= broken && broken < b) {
          ret = std::max(ret, n - 1 - b + a + 1);
        } else {
          ret = std::max(ret, b - a);
        }
      }
      return ret;
    };
    int answer = n;
    for (int i = 0; i < n; ++i) {
      answer = std::min(answer, calc(i));
    }
    printf("%d\n", answer);
  }
}
