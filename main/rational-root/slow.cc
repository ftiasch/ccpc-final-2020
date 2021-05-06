#include <algorithm>
#include <cstdio>
#include <vector>

using i64 = long long;

const int N = 5e5 + 10;

i64 x1[N], x2[N];
std::vector<int> fac[N];

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

int solve(int n, int p) {
  if (p == 0)
    return 0;
  int ret = 0;
  for (int x = 1; x <= std::abs(p); ++x) {
    // if (x1[x] == p) printf("%d ", x);
    // if (x2[x] == p) printf("%d ", -x);
    ret += x1[x] == p;
    ret += x2[x] == p;
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
    for (int x = 1; x <= m; ++x) {
      x1[x] = ipow(x, n - 1, m, 1);
      x2[x] = ipow(x, n - 1, m, -1);
    }
    for (int p = -m; p <= m; ++p) {
      for (int q = -m; q <= m; ++q) {
        if (n == 1) {
          ret += p != -1 && k == 1;
          continue;
        }
        // printf("p=%d q=%d: ", p, q);
        int roots = 0;
        if (q == 0) {
          // printf("0 ");
          if (n == 1)
            roots += (p != -1);
          else
            roots = 1 + solve(n - 1, -p);
        } else {
          for (auto &x : fac[std::abs(q)]) {
            // if (x1[x] + p == q / x) printf("%d ", x);
            // if (x2[x] + p == -q / x) printf("%d ", -x);
            roots += (x1[x] + p == q / x);
            roots += (x2[x] + p == -q / x);
          }
        }
        ret += roots == k;
        // puts("");
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}
