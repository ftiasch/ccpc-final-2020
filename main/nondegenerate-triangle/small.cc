#include "testlib.h"

#include <bits/stdc++.h>

using HyperEdge = std::tuple<int, int, int>;

struct Point {
  int x, y;
};

Point operator-(const Point &a, const Point &b) {
  return Point{a.x - b.x, a.y - b.y};
}

long long det(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int n = opt<int>("n");
  const int m = opt<int>("m");
  std::set<std::vector<HyperEdge>> found_hyper_graph;
  while (T--) {
    std::vector<Point> points;
    for (auto &&e : rnd.distinct(n, m * m)) {
      points.push_back(Point{e / m, e % m});
    }
    // std::sort(points.begin(), points.end());
    std::vector<HyperEdge> hyper_graph;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          if (det(points[j] - points[i], points[k] - points[j]) == 0) {
            hyper_graph.emplace_back(i, j, k);
          }
        }
      }
    }
    std::vector<HyperEdge> min_repr = hyper_graph;
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    do {
      std::vector<HyperEdge> new_repr;
      for (auto &&h : hyper_graph) {
        int a, b, c;
        std::tie(a, b, c) = h;
        a = perm[a];
        b = perm[b];
        c = perm[c];
        if (b > c) {
          std::swap(b, c);
        }
        if (a > b) {
          std::swap(a, b);
        }
        if (b > c) {
          std::swap(b, c);
        }
        new_repr.emplace_back(a, b, c);
      }
      std::sort(new_repr.begin(), new_repr.end());
      min_repr = std::min(min_repr, new_repr);
    } while (std::next_permutation(perm.begin(), perm.end()));
    if (found_hyper_graph.insert(min_repr).second) {
      printf("%d\n", n);
      shuffle(points.begin(), points.end());
      for (int i = 0; i < n; ++i) {
        printf("%d %d\n", points[i].x, points[i].y);
      }
      // fprintf(stderr, "hyper graph = ");
      // for (auto &&h : min_repr) {
      //   int a, b, c;
      //   std::tie(a, b, c) = h;
      //   fprintf(stderr, "{%d, %d, %d}, ", a, b, c);
      // }
      // fprintf(stderr, "\n");
    }
  }
  fprintf(stderr, "cases %d\n", static_cast<int>(found_hyper_graph.size()));
}
