#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    for (int j = 0; j < n; ++j) {
      int result = 0;
      int max = 0;
      for (int i = j; i >= 0; --i) {
        max = std::max(max, a[i]);
        result += (max - (j - i + 1) >= m);
      }
      printf("%d%c", result, " \n"[j + 1 == n]);
    }
  }
}