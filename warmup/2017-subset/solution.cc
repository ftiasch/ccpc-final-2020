#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>

const int G = 5;
const int P = 2017;

using B = std::bitset<P - 1>;

int ord[P];

int main() {
  memset(ord, -1, sizeof(ord));
  for (int i = 0, x = 1; i < P - 1; ++i) {
    ord[x] = i;
    x = x * G % P;
  }
  int n, r;
  while (scanf("%d%d", &n, &r) == 2) {
    B result;
    result.set(0);
    for (int i = 0; i < n; ++i) {
      int a;
      scanf("%d", &a);
      assert(a != 0);
      int o = ord[a];
      result ^= (result << o) | (result >> (P - 1 - o));
    }
    result.flip(0);
    printf("%d\n", result.test(ord[r]));
  }
}
