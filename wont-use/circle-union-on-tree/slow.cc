#include <bits/stdc++.h>

struct Solver {
  Solver(int n_) : n(n_), w(n), tree(n) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &w[i]);
    }
    for (int i = 1, a, b; i < n; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      tree[a].push_back(b);
      tree[b].push_back(a);
    }
  }

  void dfs(std::vector<bool> &marked, int p, int u, int d) {
    marked[u] = true;
    if (d) {
      for (int v : tree[u]) {
        if (v != p) {
          dfs(marked, u, v, d - 1);
        }
      }
    }
  }

  int solve(int i) {
    int k;
    scanf("%d", &k);
    std::vector<bool> marked(n);
    while (k--) {
      int v, d;
      scanf("%d%d", &v, &d);
      v--;
      dfs(marked, -1, v, d);
    }
    int result = 0;
    for (int i = 0; i < n; ++i) {
      if (marked[i]) {
        result += w[i];
      }
    }
    return result;
  }

  int n;
  std::vector<int> w;
  std::vector<std::vector<int>> tree;
};

int main() {
  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    Solver solver(n);
    for (int i = 0; i < q; ++i) {
      printf("%d\n", solver.solve(i));
    }
  }
}
