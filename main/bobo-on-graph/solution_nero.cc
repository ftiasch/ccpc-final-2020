#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  int n, m;
  std::string s;
  while (reader >> n >> m >> s) {
    std::vector<int> cnt(n);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
      int x, y;
      reader >> x >> y;
      --x;
      --y;
      edges.emplace_back(x, y);
      if (s[x] != s[y]) {
        ++cnt[x];
        ++cnt[y];
      }
    }
    using LL = long long;
    LL result = 0;
    for (const auto &e : edges) {
      int x = e.first;
      int y = e.second;
      if (s[x] == s[y])
        continue;
      result += LL(cnt[x] - 1) * (cnt[y] - 1);
    }
    std::cout << result << std::endl;
  }
}
