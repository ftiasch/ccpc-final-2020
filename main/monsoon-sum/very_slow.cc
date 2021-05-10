#include <bits/stdc++.h>

static const int MOD = 998244353;

int inv(int a) {
  return a == 1 ? 1
                : static_cast<long long>(MOD - MOD / a) * inv(MOD % a) % MOD;
}

int binom(int n, int k) {
  int numer = 1;
  int denom = 1;
  for (int i = 0; i < k; ++i) {
    numer = static_cast<long long>(numer) * (n - i) % MOD;
    denom = static_cast<long long>(denom) * (i + 1) % MOD;
  }
  return static_cast<long long>(numer) * inv(denom) % MOD;
}

int power(int a, int n) {
  int result = 1;
  while (n) {
    if (n & 1) {
      result = static_cast<long long>(result) * a % MOD;
    }
    a = static_cast<long long>(a) * a % MOD;
    n >>= 1;
  }
  return result;
}

int solve(int n, int x, int y, int a, int b) {
  int result = 0;
  for (int i = a; i <= n - b; ++i) {
    result += static_cast<long long>(power(x, i - a)) * binom(i, a) % MOD *
              power(y, n - i - b) % MOD * binom(n - i, b) % MOD;
    if (result >= MOD) {
      result -= MOD;
    }
  }
  return result;
}

int main() {
  int n, x, y, q;
  while (scanf("%d%d%d%d", &n, &x, &y, &q) == 4) {
    // int delta = (y - x) % MOD;
    // if (delta < 0) {
    //   delta += MOD;
    // }
    // for (int i = 0; i <= n; ++i) {
    //   for (int j = 0; j <= n; ++j) {
    //     printf("%10d", solve(n, x, y, i, j));
    //     if (i && j) {
    //       assert((static_cast<long long>(delta) * solve(n, x, y, i, j) +
    //               solve(n, x, y, i, j - 1)) %
    //                  MOD ==
    //              solve(n, x, y, i - 1, j));
    //     }
    //   }
    //   puts("");
    // }
    // puts("");
    while (q--) {
      int a, b;
      scanf("%d%d", &a, &b);
      printf("%d\n", solve(n, x, y, a, b));
    }
  }
}
