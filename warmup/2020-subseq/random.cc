#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int w = opt<int>("w");

  while (T--) {
    int n;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(1, opt<int>("maxn"));
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      int x = rnd.wnext(0, 1, w);
      printf("%d", x ? rnd.next(0, 1) * 2 : 1);
    }
    puts("");
  }
}
