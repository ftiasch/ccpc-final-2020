#include <bits/stdc++.h>

#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

namespace {

using LL = long long;

const int kN = 50 + 5;
int n;
int a[kN];

LL f[kN][kN][kN][kN];
bool vis[kN][kN];

void calc(int l, int r) {
  if (l > r || vis[l][r])
    return;
  vis[l][r] = true;
  memset(f[l][r], 0, sizeof(f[l][r]));
  for (int m = l; m <= r; ++m) {
    f[l][r][m][m]++;
    calc(l, m - 1);
    calc(m + 1, r);

    if (l <= m - 1) {
      for (int low = l; low <= m - 1; ++low) {
        for (int high = l; high <= m - 1; ++high)
          if (a[high] < a[m]) {
            f[l][r][low][m] += f[l][m - 1][low][high];
          }
      }
    }
    if (m + 1 <= r) {
      for (int low = m + 1; low <= r; ++low) {
        for (int high = m + 1; high <= r; ++high)
          if (a[high] < a[m]) {
            f[l][r][low][m] += f[m + 1][r][low][high];
          }
      }
    }
    if (l <= m - 1 && m + 1 <= r) {
      static int right[kN];
      memset(right, 0, sizeof(right));
      for (int low = m + 1; low <= r; ++low) {
        for (int high = m + 1; high <= r; ++high)
          if (a[high] < a[m]) {
            right[a[low]] += f[m + 1][r][low][high];
          }
      }
      for (int i = n; i >= 0; --i) {
        right[i] += right[i + 1];
      }
      for (int low = l; low <= m - 1; ++low) {
        for (int high = l; high <= m - 1; ++high)
          if (a[high] < a[m]) {
            f[l][r][low][m] += f[l][m - 1][low][high] * right[a[high] + 1];
          }
      }
    }
  }
}

LL solve() {
  memset(vis, false, sizeof(vis));
  calc(0, n - 1);
  LL ret = 0;
  for (int low = 0; low < n; ++low) {
    for (int high = 0; high < n; ++high) {
      ret += f[0][n - 1][low][high];
    }
  }

  return ret;
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n) {
    for (int i = 0; i < n; ++i) {
      reader >> a[i];
    }
    printf("%lld\n", solve());
  }
}
