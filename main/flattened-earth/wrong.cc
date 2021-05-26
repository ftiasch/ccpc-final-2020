#include <bits/stdc++.h>

const int N = 200000;

int a[N], b[N], order[N];

int main() {
  std::mt19937_64 gen{0};
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", a + i, b + i);
      a[i]--;
      b[i]--;
      if (a[i] > b[i]) {
        std::swap(a[i], b[i]);
      }
    }
    std::iota(order, order + n, 0);
    std::shuffle(order, order + n, gen);
    int result = n;
    for (int _ = 0; _ < std::min(n, 10000); ++_) {
      int i = order[_];
      int current_result = 0;
      for (int j = 0; j < m; ++j) {
        current_result =
            std::max(current_result,
                     a[j] < i && i <= b[j] ? n - (b[j] - a[j]) : b[j] - a[j]);
      }
      result = std::min(result, current_result);
    }
    printf("%d\n", result);
  }
}
