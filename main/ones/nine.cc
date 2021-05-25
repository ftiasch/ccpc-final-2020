#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  for (int i = 0; i < n; ++i) {
    putchar('9');
  }
  puts("");
}
