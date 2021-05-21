#include <bits/stdc++.h>

int main() {
  int m, q;
  while (scanf("%d%d", &m, &q) == 2) {
    std::vector<int> f(1 << m), g(1 << m), h(1 << m);
    for (int i = 0; i < 1 << m; ++i) {
      scanf("%d", &f[i]);
    }
    for (int i = 0; i < 1 << m; ++i) {
      scanf("%d", &g[i]);
    }
    for (int i = 0; i < 1 << m; ++i) {
      scanf("%d", &h[i]);
    }
    while (q--) {
      int l_prime, r_prime;
      scanf("%d%d", &l_prime, &r_prime);
      int l_xor_fr = r_prime ^ h[l_prime];
      int r = l_prime ^ g[l_xor_fr];
      int l = l_xor_fr ^ f[r];
      printf("%d %d\n", l, r);
    }
  }
}
