#include <bits/stdc++.h>

using Graph = std::vector<std::vector<int>>;

struct Solver {
  Solver(int n_, int m_, std::vector<char> &&s_, Graph &&g_)
      : n{n_}, m{m_}, c{std::move(s_)}, g{std::move(g_)} {}

  long long dfs(int i, std::vector<bool> &used, int u) const {
    if (used[u] || c[u] != "bobo"[i]) {
      return 0;
    }
    if (i == 3) {
      return 1;
    }
    used[u] = true;
    long long result = 0;
    for (int v : g[u]) {
      result += dfs(i + 1, used, v);
    }
    used[u] = false;
    return result;
  }

  long long solve() const {
    long long result = 0;
    std::vector<bool> used(n);
    for (int s = 0; s < n; ++s) {
      result += dfs(0, used, s);
    }
    return result;
  }

  int n, m;
  std::vector<char> c;
  Graph g;
};

int main() {
  std::ios::sync_with_stdio(false);
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    Graph graph(n);
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    Solver solver{n, m, std::move(s), std::move(graph)};
    std::cout << solver.solve() << std::endl;
  }
}
