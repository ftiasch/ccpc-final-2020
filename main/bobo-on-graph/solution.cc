#include <bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false);
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    std::vector<std::array<int, 2>> count(n);
    // o - 0
    // b - 1
    // bobo = 1010
    std::vector<std::pair<int, int>> edges;
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      count[a][s[b] == 'b']++;
      count[b][s[a] == 'b']++;
      if (s[a] == 'o' && s[b] == 'b') {
        edges.emplace_back(a, b);
      } else if (s[b] == 'o' && s[a] == 'b') {
        edges.emplace_back(b, a);
      }
    }
    long long result = 0;
    for (auto &&e : edges) {
      result += (count[e.first][1] - 1LL) * (count[e.second][0] - 1LL);
    }
    std::cout << result << std::endl;
  }
}
