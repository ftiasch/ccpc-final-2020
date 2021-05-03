#include <bits/stdc++.h>

namespace {

using Long = long long;

struct Point {
  int x, y;
};

bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

Point operator-(const Point &a, const Point &b) {
  return Point{a.x - b.x, a.y - b.y};
}

Long det(const Point &a, const Point &b) {
  return static_cast<Long>(a.x) * static_cast<Long>(b.y) -
         static_cast<Long>(a.y) * static_cast<Long>(b.x);
}

static bool ok(const Point &a, const Point &b, const Point &c) {
  return det(b - a, c - a) != 0;
}

struct Solver {
  Solver(int n_, std::vector<Point> &&p_) : n{n_}, p{std::move(p_)}, used(n) {
    dfs(0, n, 0);
  }

  void dfs(int first, int unused, int formed) {
    if (formed + (unused / 3) >= result) {
      result = std::max(result, formed);
      if (first < n) {
        if (used[first]) {
          dfs(first + 1, unused, formed);
        } else {
          dfs(first + 1, unused - 1, formed);
          for (int j = first + 1; j < n; ++j) {
            if (!used[j]) {
              for (int k = j + 1; k < n; ++k) {
                if (!used[k] && ok(p[first], p[j], p[k])) {
                  used[j] = used[k] = true;
                  dfs(first + 1, unused - 3, formed + 1);
                  used[j] = used[k] = false;
                }
              }
            }
          }
        }
      }
    }
  }

  int n, result = 0;
  std::vector<Point> p;
  std::vector<bool> used;
};

} // namespace

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &p[i].x, &p[i].y);
    }
    Solver solver{n, std::move(p)};
    printf("%d\n", solver.result);
  }
}
