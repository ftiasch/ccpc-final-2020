#include <bits/stdc++.h>

namespace {

static const int N = 5000;
static const int MOD = 998244353;

int power(int a, int n) {
  if (n < 0) {
    return 0;
  }
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

int inverse(int a) { return power(a, MOD - 2); }

int buffer[N + 2][N + 2];

int &dp(int a, int b) { return buffer[a + 1][b + 1]; }

} // namespace

int main() {
  int n, x, y, q;
  while (scanf("%d%d%d%d", &n, &x, &y, &q) == 4) {
    int m = 0;
    std::vector<int> a(q), b(q);
    for (int i = 0; i < q; ++i) {
      scanf("%d%d", &a[i], &b[i]);
      m = std::max(m, std::max(a[i], b[i]));
    }

    if (x == y) {
      int binom = 1;
      for (int k = 0; k <= m + m; ++k) {
        binom = static_cast<long long>(binom) * (n + 1 - k) % MOD *
                inverse(k + 1) % MOD;
        int result = static_cast<long long>(power(x, n - k)) * binom % MOD;
        for (int i = std::max(0, k - m); i <= m && i <= k; ++i) {
          dp(i, k - i) = result;
        }
      }
    } else {
      int binom = 1;
      for (int i = 0; i <= m; ++i) {
        dp(i, -1) = static_cast<long long>(binom) * power(x, n + 1 - i) % MOD;
        dp(-1, i) = static_cast<long long>(binom) * power(y, n + 1 - i) % MOD;
        binom = static_cast<long long>(binom) * (n + 1 - i) % MOD *
                inverse(i + 1) % MOD;
      }
      int delta = y + MOD - x;
      if (delta >= MOD) {
        delta -= MOD;
      }
      int inv_delta = inverse(delta);
      for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
          dp(i, j) = static_cast<long long>(inv_delta) *
                     (dp(i - 1, j) + MOD - dp(i, j - 1)) % MOD;
        }
      }
    }
    for (int i = 0; i < q; ++i) {
      printf("%d\n", dp(a[i], b[i]));
    }
  }
}
