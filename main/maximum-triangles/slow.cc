#include <bits/stdc++.h>

namespace {

struct Point {
  int x, y;
};

Point make_polar(const Point &o, const Point &p) {
  int dx = p.x - o.x;
  int dy = p.y - o.y;
  if (dy < 0) {
    return Point{-dx, -dy};
  } else if (dy == 0) {
    return Point{std::abs(dx), 0};
  } else {
    return Point{dx, dy};
  }
}

using Long = long long;

Long det(const Point &a, const Point &b) {
  return static_cast<Long>(a.x) * static_cast<Long>(b.y) -
         static_cast<Long>(a.y) * static_cast<Long>(b.x);
}

bool operator<(const Point &a, const Point &b) { return det(a, b) > 0; }

} // namespace

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &points[i].x, &points[i].y);
    }
    int colinear = 1;
    std::vector<Point> polar(n - 1);
    for (int o = 0; o < n; ++o) {
      for (int i = 0; i < o; ++i) {
        polar[i] = make_polar(points[o], points[i]);
      }
      for (int i = o + 1; i < n; ++i) {
        polar[i - 1] = make_polar(points[o], points[i]);
      }
      std::sort(polar.begin(), polar.end());
      for (int i = 0; i < n - 1;) {
        int j = i;
        while (j < n - 1 && det(polar[i], polar[j]) == 0) {
          j++;
        }
        colinear = std::max(colinear, j - i + 1);
        i = j;
      }
    }
    printf("%d\n", std::min(n / 3, n - colinear));
  }
}
