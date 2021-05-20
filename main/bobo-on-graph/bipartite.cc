#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n0 = opt<int>("n0");
  const int n1 = opt<int>("n1");
  const int n = n0 + n1;
  const long long product =
      static_cast<long long>(n0) * static_cast<long long>(n1);
  const int m = std::min(opt<long long>("m"), product);
  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    putchar("bo"[i < n0]);
  }
  puts("");
  for (auto &&e : rnd.distinct(m, product)) {
    printf("%d %d\n", static_cast<int>(e % n0 + 1),
           static_cast<int>(n0 + e / n0 + 1));
  }
}
