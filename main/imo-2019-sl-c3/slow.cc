#include <bits/stdc++.h>

namespace {

static const int MOD = 998244353;

long long steps(int n, const std::vector<int> &s) {
  long long result = 0;
  int heads = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 1) {
      heads++;
      result += 2 * (i + 1);
    }
  }
  return result - static_cast<long long>(heads) * heads;
}

} // namespace

int main() {
  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    std::vector<char> buffer(n + 1);
    scanf("%s", buffer.data());
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
      s[i] = buffer[i] == '1';
    }
    while (q--) {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;
      for (int i = l; i < r; ++i) {
        s[i] ^= 1;
      }
      printf("%d\n", static_cast<int>(steps(n, s) % MOD));
    }
  }
}
