#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

using LL = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  const LL arr[] = {1, 3, 673, 2019};
  LL a, b, c, d;
  auto count = [](LL a, LL b, LL w) -> LL { return b / w - (a - 1) / w; };
  while (reader >> a >> b >> c >> d) {
    LL result = 0;
    for (int p = 0; p < 4; ++p) {
      for (int q = 0; q < 4; ++q) {
        if ((p | q) != 3)
          continue;
        int coef = (__builtin_popcount(p & q) & 1) ? -1 : 1;
        result += coef * count(a, b, arr[p]) * count(c, d, arr[q]);
      }
    }
    printf("%lld\n", result);
  }
}
