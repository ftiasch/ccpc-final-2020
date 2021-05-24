#include <bits/stdc++.h>

int n;

void work() {
  std::vector<int> xx(n), yy(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &xx[i], &yy[i]);
  }
  int max_points = std::min(2, n);
  if (n > 1) {
    for (int k = 0; k < 50; ++k) {
      int a, b;
      do {
        a = rand() % n;
        b = rand() % n;
      } while (a == b);
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        int dxa = xx[i] - xx[a], dya = yy[i] - yy[a];
        int dxb = xx[i] - xx[b], dyb = yy[i] - yy[b];
        if (1LL * dxa * dyb == 1LL * dya * dxb) {
          ++cnt;
        }
      }
      max_points = std::max(max_points, cnt);
    }
  }
  int res = std::max(n % 3, max_points - 2 * (n - max_points));
  printf("%d\n", res);
}

int main() {
  while (~scanf("%d", &n)) {
    work();
  }
}