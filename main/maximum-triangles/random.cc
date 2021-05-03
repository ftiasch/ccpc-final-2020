#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  int n = opt<int>("n");
  int v = opt<int>("v");
  int tv = opt<int>("vt");
  bool colinear = opt<bool>("colinear");
  while (T--) {
    std::set<std::pair<int, int>> points;
    {
      int count = rnd.next(colinear ? n - n / 3 + 1 : 0, n);
      int x = rnd.next(0, v - 1);
      for (int y : rnd.distinct(count, v)) {
        points.emplace(x, y);
      }
    }
    while (static_cast<int>(points.size()) < n) {
      int x = rnd.next(0, v - 1);
      int y = rnd.next(0, v - 1);
      points.emplace(x, y);
    }
    int tx = rnd.next(0, tv - 1);
    int ty = rnd.next(0, tv - 1);
    std::vector<std::pair<int, int>> tpoints;
    for (auto &&p : points) {
      int x = p.first;
      int y = p.second;
      tpoints.emplace_back(x * tx + v * tv - y * ty, x * ty + y * tx);
    }
    shuffle(tpoints.begin(), tpoints.end());
    printf("%d\n", n);
    bool transposed = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
      if (transposed) {
        printf("%d %d\n", tpoints[i].second, tpoints[i].first);
      } else {
        printf("%d %d\n", tpoints[i].first, tpoints[i].second);
      }
    }
  }
}
