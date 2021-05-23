#include <bits/stdc++.h>

const int N = 5000;
const int MOD = 998244353;

int dp[N + 1][N + 1];

int main() {
  dp[0][0] = 1;
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= N; ++j) {
      if (i) {
        (dp[i][j] += dp[i - 1][j]) %= MOD;
      }
      if (j) {
        (dp[i][j] += dp[i][j - 1]) %= MOD;
      }
    }
  }
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    int w = (dp[n][m] + MOD - 1) % MOD;
    printf("%d\n", static_cast<int>(1LL * w * w % MOD));
  }
}
