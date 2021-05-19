#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int n = opt<int>("n");
  const int m = opt<int>("m");
  while (T--) {
    printf("%d %d\n", n, m);
    printf("%s\n", rnd.next(format("[bo]{%d}", n)).c_str());
    auto edge_ids = rnd.distinct(m, n * (n - 1LL) / 2);
    std::sort(edge_ids.begin(), edge_ids.end());
    std::vector<std::pair<int, int>> edges;
    {
      int v = 0;
      long long offset = 0;
      for (auto &&edge_id : edge_ids) {
        while (edge_id - offset >= v) {
          offset += v;
          v++;
        }
        int u = edge_id - offset;
        if (rnd.next(0, 1)) {
          edges.emplace_back(u, v);
        } else {
          edges.emplace_back(v, u);
        }
      }
    }
    shuffle(edges.begin(), edges.end());
    for (auto &&e : edges) {
      printf("%d %d\n", e.first + 1, e.second + 1);
    }
  }
}
