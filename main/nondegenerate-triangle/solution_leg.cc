#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct poi {
  int x, y;
  poi operator-(poi p) { return (poi){x - p.x, y - p.y}; }
  ll operator*(poi p) { return x * p.y - y * p.x; }
} a[N];
int n;
int main() {
  while (~scanf("%d", &n)) {
    rep(i, n) scanf("%d%d", &a[i].x, &a[i].y);
    srand(n + 19260817);
    int mx = 0;
    rep(tim, 100) {
      int u = rand() % n + 1, v = rand() % n + 1;
      if (u == v)
        continue;
      int now = 0;
      rep(i, n) if ((a[u] - a[i]) * (a[v] - a[i]) == 0)++ now;
      mx = max(mx, now);
    }
    int ans = 0;
    if (mx > (n - mx) * 2)
      ans = mx - (n - mx) * 2;
    else
      ans = n % 3;
    printf("%d\n", ans);
  }
  return 0;
}
