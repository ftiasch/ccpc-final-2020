#include <bits/stdc++.h>

int main() {
  int n, m, h, w, k;
  while (scanf("%d%d%d%d%d", &n, &m, &h, &w, &k) == 5) {
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &a[i][j]);
      }
    }
    std::vector<int> candidates(k);
    for (int i = 0; i + h <= n; ++i) {
      for (int j = 0; j + w <= m; ++j) {
        std::fill(candidates.begin(), candidates.end(), 0);
        for (int x = i; x < i + h; ++x) {
          for (int y = j; y < j + w; ++y) {
            int current = a[x][y];
            for (int z = 0; z < k; ++z) {
              if (candidates[z] == 0 || candidates[z] > current) {
                std::swap(candidates[z], current);
              }
            }
          }
        }
        printf("%d%c", candidates[k - 1], " \n"[j + w == m]);
      }
    }
  }
}
