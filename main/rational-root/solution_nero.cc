#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

using LL = long long;
const int INF = 0x3f3f3f3f;
const int kN = 500000 + 5;
int n, m, k;
std::vector<int> divisors[kN];

LL clamp(LL val, LL low, LL high) { return std::max(low, std::min(val, high)); }

LL limit_power(LL a, LL b) {
  LL ret = 1;
  for (; b; b >>= 1, a = clamp(a * a, -INF, INF)) {
    if (b & 1) {
      ret = clamp(ret * a, -INF, INF);
      if (ret <= -INF || ret >= INF)
        return ret;
    }
  }
  return ret;
}

LL get_p(LL w, LL x, LL t) {
  LL pw = limit_power(x, t);
  if (pw <= -INF || pw >= INF)
    return pw;
  return w - pw;
}

LL solve() {
  if (k > 3) {
    return 0;
  }
  LL ret = 0;

  if (n == 1) {
    // (p + 1) * x == -q

    // case p == -1:
    //   q == 0: infinite roots
    //   q != 0: no roots

    // case p != -1:
    if (k == 1) {
      ret += LL(2 * m + 1) * (2 * m);
    }
    return ret;
  }

  // case q == 0.
  {
    // (x^{n-1} + p) * x == 0

    // Note: For every possible p, we have x == 0 is a root.

    // case p == 0:
    // x^n == 0
    if (k == 1) {
      ++ret;
    }
    // DUMP(ret);

    // case p != 0:
    // If x != 0, we have x^{n-1} == -p.

    std::vector<bool> mark(m + 1);
    for (int i = 1; i <= m; ++i) {
      LL w = limit_power(i, n - 1);
      if (w <= m)
        mark[w] = true;
    }

    for (int i = 1; i <= m; ++i) {

      // case p < 0:
      {
        int num = 1 + (1 + (n & 1)) * mark[i];
        if (num == k)
          ++ret;
      }

      // case p > 0:
      {
        int num = 1;
        if (n % 2 == 0 && mark[i])
          ++num;
        if (num == k)
          ++ret;
      }
    }
  }
  // DUMP(ret);

  for (LL absq = 1; absq <= m; ++absq) {
    for (int signq = -1; signq <= 1; signq += 2) {
      LL q = absq * signq;
      std::map<LL, LL> map;
      for (LL absx : divisors[absq]) {
        for (int signx = -1; signx <= 1; signx += 2) {
          LL x = absx * signx;
          LL p = get_p(-q / x, x, n - 1);
          if (p >= -m && p <= m) {
            map[p]++;
          }
        }
      }
      for (const auto &pair : map) {
        if (pair.second == k) {
          ++ret;
        }
      }
    }
  }
  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  for (int i = 1; i < kN; ++i)
    for (int j = i; j < kN; j += i)
      divisors[j].emplace_back(i);

  while (reader >> n >> m >> k) {
    printf("%lld\n", solve());
  }
}
