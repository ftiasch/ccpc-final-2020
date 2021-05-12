#include "testlib.h"

struct Point {
  static Point sample(int m) {
    int x = rnd.next(-m, m);
    int y = rnd.next(-m, m);
    int z = rnd.next(-m, m);
    return Point{x, y, z};
  }

  int x, y, z;
};

std::ostream &operator<<(std::ostream &out, const Point &p) {
  return out << p.x << " " << p.y << " " << p.z;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  const int m = opt<int>("m");
  while (T--) {
    for (int _ = 0; _ < 2; ++_) {
      do {
        Point a = Point::sample(m);
        Point b = Point::sample(m);
        if (a.x != b.x && a.y != b.y && a.z != b.z) {
          std::cout << a << "\n";
          std::cout << b << "\n";
          break;
        }
      } while (true);
    }
  }
}
