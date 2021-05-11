#include "testlib.h"

using Point = std::array<int, 3>;

Point gen_point(int m) {
  int x = rnd.next(-m, m);
  int y = rnd.next(-m, m);
  int z = rnd.next(-m, m);
  return {x, y, z};
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int m = opt<int>("m");
  while (T--) {
    const Point p = gen_point(m);
    const Point q = gen_point(m);
    const Point a = gen_point(m);
    Point b;
    do {
      b = gen_point(m);
    } while (a == b);
    printf("%d %d %d\n", p[0], p[1], p[2]);
    printf("%d %d %d\n", q[0], q[1], q[2]);
    printf("%d %d %d\n", a[0], a[1], a[2]);
    printf("%d %d %d\n", b[0], b[1], b[2]);
  }
}
