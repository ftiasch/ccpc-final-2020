#include <bits/stdc++.h>

namespace {

static const int N = 500;
static const int MOD = 998244353;

bool graph[N][N], deleted[N];

int dfs(int n, int end, int todo) {
  if (todo > 0) {
    int result = 0;
    for (int v = end; v--;) {
      deleted[v] = true;
      result += dfs(n, v, todo - 1);
      if (result >= MOD) {
        result -= MOD;
      }
      deleted[v] = false;
    }
    return result;
  }
  bool found = false;
  for (int u = 0; u < n && !found; ++u) {
    if (!deleted[u]) {
      for (int v = 0; v < n && !found; ++v) {
        if (v != u && !deleted[v] && graph[u][v]) {
          for (int w = v + 1; w < n && !found; ++w) {
            if (w != u && !deleted[w] && graph[u][w] && !graph[v][w]) {
              found = true;
            }
          }
        }
      }
    }
  }
  return !found;
}

} // namespace

int main() {
  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    for (int i = 0; i < n; ++i) {
      memset(graph[i], 0, sizeof(bool) * n);
    }
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      graph[a][b] = graph[b][a] = true;
    }
    memset(deleted, 0, sizeof(bool) * n);
    int result = dfs(n, n, k);
    printf("%d\n", result);
  }
}
