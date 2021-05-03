#include <bits/stdc++.h>

namespace {

static const int ITERATIONS = 20;

struct Point {
  int x, y;
};

Point operator-(const Point &a, const Point &b) {
  return Point{a.x - b.x, a.y - b.y};
}

using Long = long long;

Long det(const Point &a, const Point &b) {
  return static_cast<Long>(a.x) * static_cast<Long>(b.y) -
         static_cast<Long>(a.y) * static_cast<Long>(b.x);
}

} // namespace

int main() {
  std::mt19937_64 gen{0};
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &p[i].x, &p[i].y);
    }
    int result = 0;
    if (n > 1) {
      int colinear = 0;
      for (int _ = 0; _ < ITERATIONS; ++_) {
        int x, y;
        do {
          x = gen() % n;
          y = gen() % n;
        } while (x == y);
        int count = 0;
        for (int i = 0; i < n; ++i) {
          count += det(p[i] - p[x], p[i] - p[y]) == 0;
        }
        colinear = std::max(colinear, count);
      }
      result = std::min(n / 3, n - colinear);
    }
    printf("%d\n", result);
  }
}
