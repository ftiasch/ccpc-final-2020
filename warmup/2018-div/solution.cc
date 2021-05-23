#include <bits/stdc++.h>

const int MOD = 998244353;

struct Fact {
  int operator()(int n) {
    for (int i = cache.size(); i <= n; ++i) {
      cache.push_back(1LL * cache[i - 1] * i % MOD);
    }
    return cache[n];
  }

  std::vector<int> cache = {1};
} fact;

int inv(int a) {
  return a == 1 ? 1 : 1LL * (MOD - MOD / a) * inv(MOD % a) % MOD;
}

int binom(int a, int b) {
  return 1LL * fact(a + b) * inv(fact(a)) % MOD * inv(fact(b)) % MOD;
}

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    int ways = (binom(n, m) + MOD - 1) % MOD;
    printf("%d\n", static_cast<int>(1LL * ways * ways % MOD));
  }
}
