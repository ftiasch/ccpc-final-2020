#include <bits/stdc++.h>

static const int MOD = 998244353;

long long solve(int n, std::vector<char> &s) {
  long long result = 0;
  for (int length = n; length >= 1; --length) {
    if (s[length - 1] == 'H') {
      result += length;
      std::reverse(s.begin(), s.begin() + length - 1);
      for (int j = 0; j < length - 1; ++j) {
        s[j] = s[j] == 'H' ? 'T' : 'H';
      }
    }
  }
  return result;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    printf("%d\n", static_cast<int>(solve(n, s) % MOD));
  }
}
