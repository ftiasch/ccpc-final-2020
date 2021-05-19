#include <bits/stdc++.h>

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    std::vector<std::vector<bool>> graph(n, std::vector<bool>(n));
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      graph[a][b] = graph[b][a] = true;
    }
    long long result = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 'b') {
        for (int j = 0; j < n; ++j) {
          if (s[j] == 'o' && graph[i][j] && i != j) {
            for (int k = 0; k < n; ++k) {
              if (s[k] == 'b' && graph[j][k] && i != k && j != k) {
                for (int l = 0; l < n; ++l) {
                  result += (s[l] == 'o' && graph[k][l] && i != l && j != l &&
                             k != l);
                }
              }
            }
          }
        }
      }
    }
    std::cout << result << std::endl;
  }
}
