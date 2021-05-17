#include "testlib.h"

#include <cstdlib>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int n = std::atoi(argv[2]);
  while (T--) {
    printf("%d %d\n", n, rnd.next(-n, n));
    for (int i = 0; i < n; ++i) {
      printf("%d%c", rnd.next(1, n), " \n"[i + 1 == n]);
    }
  }
}