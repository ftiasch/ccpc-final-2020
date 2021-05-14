#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

using i64 = long long;

const int N = 1e6 + 10;

char s[N], t[N];
int pi[N];

int solve(int n, int m, int j) {
  for (int i = 1; i <= m; ++i) {
    while (j > 0 && s[j + 1] != t[i]) {
      j = pi[j];
    }
    if (s[j + 1] == t[i]) {
      ++j;
    }
    if (j == n) {
      j = pi[j];
    }
  }
  return j;
}

int main() {
  while (scanf("%s%s", s + 1, t + 1) == 2) {
    int n = strlen(s + 1);
    int m = strlen(t + 1);
    for (int i = 2, j = 0; i <= n; ++i) {
      while (j > 0 && s[j + 1] != s[i]) {
        j = pi[j];
      }
      pi[i] = (s[j + 1] == s[i] ? ++j : j);
    }
    // i64 ret = 0;
    for (int j = 0; j < n; ++j) {
      // ret += solve(n, m, j) ^ j;
      printf("%d%c", solve(n, m, j), " \n"[j + 1 == n]);
    }
    // printf("%lld\n", ret);
  }
  return 0;
}
