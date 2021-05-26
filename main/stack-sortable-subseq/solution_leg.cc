#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= n; ++i)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int N = 52;
int a[N], r[N], n;
ll dp[N][N][N][N], sum[N][N][N][N];
int main() {
  while (~scanf("%d", &n)) {
    rep(i, n) scanf("%d", a + i);
    // n=50;
    // rep(i,n)a[i]=n-i+1;
    //{
    rep(i, n) r[a[i]] = i;
    rep(i, n) rep(j, n) for (int k = 0; k <= n + 1; ++k) for (int p = 0;
                                                              p <= n + 1; ++p)
        dp[i][j][k][p] = sum[i][j][k][p] = 0;
    ll ans = 0;
    rep(len, n) rep(i, n - len + 1) {
      int j = i + len - 1;
      for (int k = 1; k <= n; ++k)
        for (int p = n; p >= 1; --p) {
          if (p <= k && i <= r[k] && r[k] <= j && i <= r[p] && r[p] <= j) {
            if (r[k] == r[p])
              dp[i][j][k][p] = 1;
            else if (r[k] < r[p]) {
              for (int w = r[k] + 1; w <= j; ++w)
                if (p <= a[w] && a[w] <= k)
                  dp[i][j][k][p] += dp[r[k] + 1][j][a[w]][p];
            } else {
              for (int w = i; w < r[k]; ++w)
                if (p <= a[w] && a[w] <= k)
                  dp[i][j][k][p] += dp[i][r[k] - 1][a[w]][p] *
                                    (sum[r[k] + 1][j][k][a[w]] + 1);
            }
          }
          // printf("%d %d %d %d %lld\n",i,j,k,p,dp[i][j][k][p]);
          sum[i][j][k][p] = dp[i][j][k][p] + sum[i][j][k - 1][p] +
                            sum[i][j][k][p + 1] - sum[i][j][k - 1][p + 1];
          if (len == n)
            ans += dp[i][j][k][p];
        }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
/*
2
2 1
3
1 2 3
4
2 3 4 1
*/
