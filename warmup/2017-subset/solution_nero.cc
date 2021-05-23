#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

const int MOD = 2017;
const int g = 5;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  std::vector<int> mapping(MOD, -1);
  for (int i = 0, x = 1; i < MOD - 1; ++i) {
    assert(mapping[x] == -1);
    mapping[x] = i;
    x = x * g % MOD;
  }

  int n, r;
  while (reader >> n >> r) {
    std::bitset<MOD - 1> bits;
    for (int i = 0; i < n; ++i) {
      int x;
      reader >> x;
      assert(mapping[x] != -1);
      x = mapping[x];
      bits ^= (bits << x) ^ (bits >> (MOD - 1 - x));
      bits.flip(x);
    }
    printf("%d\n", bits.test(mapping[r]));
  }
}
