#include <bits/stdc++.h>

using Graph = std::vector<std::vector<int>>;

struct Solver {
  Solver(int n_, int m_, std::vector<char> &&s_, Graph &&g_)
      : n{n_}, m{m_}, c{std::move(s_)}, g{std::move(g_)} {}

  long long solve() const {
    long long result = 0;
    for (int u = 0; u < n; ++u) {
      if (c[u] == 'o') {
        for (int v : g[u]) {
          if (c[v] == 'b') {
            int cntb = 0;
            for (int w : g[u]) {
              cntb += w != v && c[w] == 'b';
            }
            int cnto = 0;
            for (int w : g[v]) {
              cnto += w != u && c[w] == 'o';
            }
            result +=
                static_cast<long long>(cntb) * static_cast<long long>(cnto);
          }
        }
      }
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
