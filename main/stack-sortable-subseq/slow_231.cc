#include <bits/stdc++.h>

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
    }
    long long result = 0;
    std::vector<int> a;
    a.reserve(n);
    for (uint64_t mask = 1; mask < 1ULL << n; ++mask) {
      a.clear();
      for (int i = 0; i < n; ++i) {
        if (mask >> i & 1) {
          a.push_back(p[i]);
        }
      }
      bool ok = true;
      int m = a.size();
      for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
          for (int k = j + 1; k < m; ++k) {
            ok &= !(a[k] < a[i] && a[i] < a[j]);
          }
        }
      }
      result += ok;
    }
    std::cout << result << std::endl;
  }
}
