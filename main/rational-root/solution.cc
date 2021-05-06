#include <algorithm>
#include <cstdio>
#include <vector>

using i64 = long long;

const int N = 5e5 + 10;

std::vector<int> fac[N];

i64 solve1(int m, int k) {
  if (k > 1)
    return 0;
  return i64(2) * m * (2 * m + 1);
}

i64 ipow(i64 x, int n, int m, int sign) {
  if (n % 2 == 0)
    sign = 1;
  if (x == 1)
    return x * sign;
  if (x == 2) {
    if (n < 50)
      return sign * (i64(1) << n);
    else
      return i64(1) << 50;
  }
  i64 r = 1;
  for (int i = 0; i < n; ++i) {
    r = r * x;
    if (r > m * 4)
      break;
  }
  return r * sign;
}

i64 solve(int n, int m, int k) {
  if (k > 3)
    return 0;
  fac[0].clear();
  for (int x = 1; x <= m; ++x)
    fac[0].push_back(x);
  i64 ret = 0;
  std::vector<i64> x1(m + 1), x2(m + 1);
  for (int x = 1; x <= m; ++x) {
    x1[x] = ipow(x, n - 1, m, 1);
    x2[x] = ipow(x, n - 1, m, -1);
  }
  std::vector<bool> mark(m * 2 + 1);
  std::vector<int> cnt(m * 2 + 1);
  for (int q = -m; q <= m; ++q) {
    std::vector<int> ps;
    for (auto &x : fac[std::abs(q)]) {
      i64 p1 = q / x - x1[x], p2 = -q / x - x2[x];
      if (-m <= p1 && p1 <= m)
        ps.push_back(p1);
      if (-m <= p2 && p2 <= m)
        ps.push_back(p2);
    }
    if (k == 1 && q == 0) {
      ret += 2 * m + 1;
      for (auto &p : ps) {
        ret -= !mark[p + m];
        mark[p + m] = 1;
      }
      for (auto &p : ps) {
        mark[p + m] = 0;
      }
    } else {
      for (auto &p : ps) {
        cnt[p + m]++;
        mark[p + m] = 1;
      }
      for (auto &p : ps)
        if (mark[p + m]) {
          mark[p + m] = 0;
          if (cnt[p + m] == k - (q == 0)) {
            // printf("%d %d\n", p, q);
            ++ret;
          }
          cnt[p + m] = 0;
        }
    }
  }
  return ret;
}

int main() {
  for (int i = 1; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      fac[j].push_back(i);
    }
  }
  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    i64 ret = 0;
    if (n == 1)
      ret = solve1(m, k);
    else
      ret = solve(n, m, k);
    printf("%lld\n", ret);
  }
  return 0;
}
