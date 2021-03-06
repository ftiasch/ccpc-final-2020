#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

const int N = 1e6 + 10;

using i64 = long long;

char s[N], t[N];
int ps[N], pt[N];
int n, m, ret[N];
bool occ[N];

void kmp(char *s, int n, int *pi) {
  pi[1] = 0;
  for (int i = 2, j = 0; i <= n; ++i) {
    while (j > 0 && s[j + 1] != s[i]) {
      j = pi[j];
    }
    pi[i] = (s[j + 1] == s[i] ? ++j : j);
  }
}

int main() {
  while (scanf("%s%s", s + 1, t + 1) == 2) {
    n = strlen(s + 1);
    m = strlen(t + 1);
    kmp(s, n, ps);
    kmp(t, n, pt);
    for (int i = 1, j = 0; i <= n; ++i) {
      occ[i] = false;
      while (j > 0 && t[j + 1] != s[i]) {
        j = pt[j];
      }
      if (t[j + 1] == s[i]) {
        ++j;
      }
      if (j == m) {
        occ[i - j + 1] = true;
        j = pt[j];
      }
    }
    int border = 0;
    for (int i = 1; i <= m; ++i) {
      while (border > 0 && s[border + 1] != t[i]) {
        border = ps[border];
      }
      if (s[border + 1] == t[i]) {
        border++;
      }
      if (border == n) {
        border = ps[border];
      }
    }
    ret[0] = 0;
    for (int i = 0; i < n; ++i) {
      if (occ[i + 1])
        ret[i] = m + i;
      else
        ret[i] = i ? ret[ps[i]] : 0;
    }
    // i64 sum = 0;
    for (int i = 0; i < n; ++i) {
      if (ret[i] == n) {
        ret[i] = ps[n];
      }
      ret[i] = std::max(ret[i], border);
      printf("%d%c", ret[i], " \n"[i + 1 == n]);
      // sum += ret[i] ^ i;
    }
    // printf("%lld\n", sum);
  }
  return 0;
}
