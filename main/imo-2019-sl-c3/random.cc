#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  int n = opt<int>("n");
  while (T--) {
    printf("%d\n", n);
    printf("%s\n", rnd.next(format("[HT]{%d}", n)).c_str());
  }
}
