#include <bits/stdc++.h>

struct DSU {
  DSU(int n) : next(n + 1) { std::iota(next.begin(), next.end(), 0); }

  int find_next(int u) {
    while (next[u] != u) {
      next[u] = next[next[u]];
      u = next[u];
    }
    return u;
  }

  void remove(int u) { next[u] = u + 1; }

  std::vector<int> next;
};

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<std::vector<std::pair<int, int>>> events(n);
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      if (a != b) {
        if (a > b) {
          std::swap(a, b);
        }
        events[b - a].emplace_back(0, a);
        events[a + n - b].emplace_back(a + 1, b);
        if (b + 1 < n) {
          events[b - a].emplace_back(b + 1, n - 1);
        }
      }
    }
    events[0].emplace_back(0, n - 1);
    DSU dsu{n};
    int result = INT_MAX;
    for (int v = n; v--;) {
      for (auto &&r : events[v]) {
        int u = dsu.find_next(r.first);
        while (u <= r.second) {
          result = v;
          dsu.remove(u);
          u = dsu.find_next(u);
        }
      }
    }
    printf("%d\n", result);
  }
}
