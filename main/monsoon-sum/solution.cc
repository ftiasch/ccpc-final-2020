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

int buffer[N + 2][N + 2], inv_fact[N + 2];

int &dp(int a, int b) { return buffer[a + 1][b + 1]; }

} // namespace

int main() {
  inv_fact[0] = inv_fact[1] = 1;
  for (int i = 2; i <= N; ++i) {
    inv_fact[i] =
        static_cast<long long>(MOD - MOD / i) * inv_fact[MOD % i] % MOD;
  }
  for (int i = 1; i <= N; ++i) {
    inv_fact[i] = static_cast<long long>(inv_fact[i - 1]) * inv_fact[i] % MOD;
  }
  int n, x, q;
  while (scanf("%d%d%d", &n, &x, &q) == 3) {
    int m = 0;
    std::vector<int> a(q), b(q);
    for (int i = 0; i < q; ++i) {
      scanf("%d%d", &a[i], &b[i]);
      m = std::max(m, std::max(a[i], b[i]));
    }
    int falling_fact = 1;
    for (int i = 0; i <= m; ++i) {
      long long binom =
          static_cast<long long>(falling_fact) * inv_fact[i] % MOD;
      dp(i, -1) = binom * power(x, n + 1 - i) % MOD;
      dp(-1, i) = binom * power(x + 1, n + 1 - i) % MOD;
      falling_fact = static_cast<long long>(falling_fact) * (n + 1 - i) % MOD;
    }
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= m; ++j) {
        dp(i, j) = (dp(i - 1, j) + MOD - dp(i, j - 1)) % MOD;
      }
    }
    for (int i = 0; i < q; ++i) {
      printf("%d\n", dp(a[i], b[i]));
    }
  }
}
