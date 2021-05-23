#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%d %d\n", i, j);
    }
  }
}
