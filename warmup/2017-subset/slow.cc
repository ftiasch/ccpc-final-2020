#include <cstdio>
#include <vector>

const int P = 2017;

int main() {
  int n, r;
  while (scanf("%d%d", &n, &r) == 2) {
    std::vector<int> ways(P);
    ways.at(1) = 1;
    for (int _ = 0; _ < n; ++_) {
      int a;
      scanf("%d", &a);
      auto new_ways = ways;
      for (int i = 0; i < P; ++i) {
        new_ways.at(i * a % P) ^= ways.at(i);
      }
      ways.swap(new_ways);
    }
    ways.at(1) ^= 1;
    printf("%d\n", ways.at(r));
  }
}
