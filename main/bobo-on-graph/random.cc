#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  // const int n = opt<int>("n");
  const int m = opt<int>("m");
  while (T--) {
    int n;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(4, opt<int>("maxn"));
    }
    std::set<std::pair<int, int>> edge_set;
    for (int _ = 0; _ < m; ++_) {
      int a = rnd.next(1, n);
      int b = rnd.next(1, n);
      if (a > b) {
        std::swap(a, b);
      }
      if (a != b) {
        edge_set.emplace(a, b);
      }
    }
    std::vector<std::pair<int, int>> edges;
    for (auto &&e : edge_set) {
      edges.emplace_back(e);
    }
    shuffle(edges.begin(), edges.end());
    printf("%d %d\n", n, static_cast<int>(edges.size()));
    printf("%s\n", rnd.next(format("[bo]{%d}", n)).c_str());
    for (auto &&e : edges) {
      if (rnd.next(0, 1)) {
        printf("%d %d\n", e.first, e.second);
      } else {
        printf("%d %d\n", e.second, e.first);
      }
    }
  }
}
