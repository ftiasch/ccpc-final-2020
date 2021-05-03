#include <bits/stdc++.h>

namespace {

const int N = 1000;
const int K = 10;

int a[N][N];

} // namespace

int main() {
  int n, m, h, w, k;
  while (scanf("%d%d%d%d%d", &n, &m, &h, &w, &k) == 5) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", a[i] + j);
      }
    }
  }
}
