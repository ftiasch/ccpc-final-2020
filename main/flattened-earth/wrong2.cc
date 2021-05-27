#include <bits/stdc++.h>

const int N = 200000;

int a[N], b[N], order[N];

int main() {
  std::mt19937_64 gen{0};
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    int result = 0;
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      int len = std::abs(a - b);
      result = std::max(result, std::min(len, n - len));
    }
    printf("%d\n", result);
  }
}
