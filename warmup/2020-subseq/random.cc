#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  const int n = std::atoi(argv[2]);
  const int w = std::atoi(argv[3]);

  while (T--) {
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      int x = rnd.wnext(0, 1, w);
      printf("%d", x ? rnd.next(0, 1) * 2 : 1);
    }
    puts("");
  }
}
