#include <bits/stdc++.h>

const int MOD = 2019;

void count(int *cnt, int coef, int n) {
  for (int i = 0; i < MOD; ++i) {
    if (i <= n) {
      cnt[i] += ((n - i) / MOD + 1) * coef;
    }
  }
}

int main() {
  int a, b, c, d;
  while (scanf("%d%d%d%d", &a, &b, &c, &d) == 4) {
    static int x[MOD], y[MOD];
    memset(x, 0, sizeof(x));
    count(x, 1, b);
    count(x, -1, a - 1);
    memset(y, 0, sizeof(y));
    count(y, 1, d);
    count(y, -1, c - 1);
    long long result = 0;
    for (int i = 0; i < MOD; ++i) {
      for (int j = 0; j < MOD; ++j) {
        if (i * j % MOD == 0) {
          result += 1LL * x[i] * y[j];
        }
      }
    }
    std::cout << result << std::endl;
  }
}
