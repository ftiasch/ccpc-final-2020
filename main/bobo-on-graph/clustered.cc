#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  const int m = opt<int>("m");
  const int w = opt<int>("w");
  std::set<std::pair<int, int>> s;
  for (int _ = 0; _ < m; ++_) {
    int u, v;
    do {
      v = rnd.wnext(1, n - 1, w);
      u = rnd.next(0, v - 1);
    } while (!s.insert(std::make_pair(u, v)).second);
  }
  std::vector<std::pair<int, int>> edges;
  for (auto &&e : s) {
    edges.push_back(e);
  }
  shuffle(edges.begin(), edges.end());
  auto vertex_label = rnd.perm(n, 1);
  printf("%d %d\n", n, m);
  printf("%s\n", rnd.next(format("[bo]{%d}", n)).c_str());
  for (auto &&e : edges) {
    int a = vertex_label[e.first];
    int b = vertex_label[e.second];
    if (rnd.next(0, 1)) {
      std::swap(a, b);
    }
    printf("%d %d\n", a, b);
  }
}
