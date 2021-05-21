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
      for (int l = 0; l < 1 << m; ++l) {
        for (int r = 0; r < 1 << m; ++r) {
          if ((r ^ g[l ^ f[r]]) == l_prime &&
              (l ^ f[r] ^ h[r ^ g[l ^ f[r]]]) == r_prime) {
            printf("%d %d\n", l, r);
          }
        }
      }
    }
  }
}
