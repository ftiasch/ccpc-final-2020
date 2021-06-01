#include <bits/stdc++.h>

#define pb emplace_back
#define mp make_pair
#define fi first
#define se second

using namespace std;
using ll = long long;

const int N = 5005, inf = 0x3f3f3f3f;
const int maxS = 100, maxD = 10;
const int G = 11000000;

int dp[2][maxS * 2 + 1][maxD * 2 + 1];
int tmp[maxS * 2 + 1][maxD * 2 + 1];
int sma[8][G / 9 + 5];
int op[N], n;
string s;

bool chkmin(int &x, int y) { return x > y ? (x = y, true) : false; }
inline int iabs(int x) { return x < 0 ? -x : x; }

void init() {
  int pw[8] = {0};
  memset(sma, 0x3f, sizeof(sma));
  sma[0][0] = 0;
  pw[0] = 1;
  for (int d = 1; d <= 7; ++d) {
    pw[d] = pw[d - 1] * 10;
    for (int i = 0; i <= G; i += 9) {
      for (int j = -10; j <= 10; ++j) {
        int t = i - j * (pw[d] - 1);
        if (t < 0)
          t = -t;
        if (t < G)
          chkmin(sma[d][i / 9], sma[d - 1][t / 9] + iabs(j) * d);
      }
    }
  }
}

pair<int, int> bop(int p) {
  if (p == 0)
    return mp(op[p], 10);
  auto t = bop(p - 1);
  return mp(t.fi + op[p] * t.se, t.se * 10);
}

void work() {
  memset(op, 0, sizeof(op));
  memset(dp, 0x3f, sizeof(dp));
  n = s.length();
  for (int i = 0; i < n; ++i)
    op[i] = 9 * (s[n - 1 - i] - '0');
  for (int i = 0; i < n; ++i)
    if (op[i] >= 10)
      op[i + 1] += op[i] / 10, op[i] %= 10;
  while (op[n]) {
    if (op[n] >= 10)
      op[n + 1] += op[n] / 10, op[n] %= 10;
    n++;
  }
  if (n <= 7) {
    printf("%d\n", sma[7][iabs(bop(6).fi) / 9]);
    return;
  }
  int base = 0;
  dp[n & 1][maxS][maxD] = 0;
  for (int d = n - 1; d >= 6; --d) {
    int cur = d & 1, lst = cur ^ 1;
    for (int s = -maxS; s <= maxS; ++s)
      for (int r = -maxD; r <= maxD; ++r) {
        if (dp[lst][s + maxS][r + maxD] != inf) {
          int nr = r * 10 + op[d];
          int i = (nr + maxD * 10) / 10 - maxD;
          while (nr - i * 10 <= maxD)
            --i;
          ++i;
          while (nr - i * 10 >= -maxD) {
            assert(nr - i * 10 <= maxD);
            if (s + i <= maxS && s + i >= -maxS)
              chkmin(dp[cur][s + i + maxS][nr - i * 10 + maxD],
                     dp[lst][s + maxS][r + maxD] + iabs(i) * (d + 1));
            ++i;
          }
        }
      }
    int nbase = 0, nval = inf;
    for (int s = -maxS; s <= maxS; ++s)
      for (int r = -maxD; r <= maxD; ++r)
        if (chkmin(nval, dp[cur][s + maxS][r + maxD]))
          nbase = s;
    base += nbase;
    memset(tmp, 0x3f, sizeof(tmp));
    for (int s = -maxS; s <= maxS; ++s)
      if (s - nbase >= -maxS && s - nbase <= maxS)
        memcpy(tmp[s - nbase + maxS], dp[cur][s + maxS], sizeof(dp[0][0]));
    memcpy(dp[cur], tmp, sizeof(tmp));
    memset(dp[lst], 0x3f, sizeof(dp[lst]));
  }
  int ans = inf;
  for (int s = -maxS; s <= maxS; ++s) {
    for (int r = -maxD; r <= maxD; ++r) {
      if (dp[0][s + maxS][r + maxD] != inf) {
        int t = iabs(bop(5).fi + r * 1000000 + s + base);
        if (t > G)
          continue;
        ans = min(ans, dp[0][s + maxS][r + maxD] + sma[6][t / 9]);
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  // freopen("input.txt","r",stdin);
  init();
  while (cin >> s)
    work();
  return 0;
}
