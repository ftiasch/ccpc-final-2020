#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  int m, q;
  while (reader >> m >> q) {
    std::vector<int> f(1 << m);
    for (int i = 0; i < f.size(); ++i)
      reader >> f[i];
    std::vector<int> g(1 << m);
    for (int i = 0; i < g.size(); ++i)
      reader >> g[i];
    std::vector<int> h(1 << m);
    for (int i = 0; i < h.size(); ++i)
      reader >> h[i];
    while (q--) {
      int xx, yy;
      reader >> xx >> yy;
      int t = yy ^ h[xx];
      int y = xx ^ g[t];
      int x = t ^ f[y];
      printf("%d %d\n", x, y);
    }
  }
}
