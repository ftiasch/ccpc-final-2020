#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int n = std::atoi(argv[2]);
  int num_asc = std::atoi(argv[3]);
  int sqrtn = sqrt(n);
  while (T--) {
    printf("%d %d\n", n, rnd.next(-sqrtn, sqrtn));
    std::vector<int> ascs;
    for (int i = 0; i < num_asc; ++i) {
      ascs.push_back(rnd.next(2, n));
    }
    std::sort(ascs.begin(), ascs.end());
    std::vector<int> gaps(num_asc + 1);
    for (int i = num_asc; i < n; ++i) {
      gaps[rnd.next(0, num_asc)]++;
    }
    std::vector<int> a;
    int ub = n;
    for (int i = 0; i <= num_asc; ++i) {
      if (i) {
        int x = ascs[num_asc - i];
        a.push_back(x);
        ub = x;
      }
      for (int _ = 0; _ < gaps[i]; ++_) {
        a.push_back(rnd.next(1, ub - 1));
      }
    }
    for (int i = 0; i < n; ++i) {
      printf("%d%c", a[i], " \n"[i + 1 == n]);
    }
  }
}
