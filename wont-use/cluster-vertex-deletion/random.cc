#include "testlib.h"

using Edges = std::vector<std::pair<int, int>>;

Edges gen_random(int n) {
  const int clusters = opt<int>("clusters");
  std::vector<int> color(n);
  for (int i = 0; i < n; ++i) {
    color[i] = rnd.next(1, clusters);
  }
  Edges result;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (color[i] == color[j]) {
        result.emplace_back(i, j);
      }
    }
  }
  const int max_extras = opt<int>("extras");
  int extras = rnd.next(0, max_extras);
  while (extras--) {
    int a = rnd.next(0, n - 1);
    int b = rnd.next(0, n - 1);
    if (a != b) {
      result.emplace_back(a, b);
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int T = opt<int>("T");
  const int n = opt<int>("n");
  const int k = opt<int>("k");
  const std::string type = opt<std::string>("type");
  while (T--) {
    Edges edges;
    if (type == "random") {
      edges = gen_random(n);
    }
    for (auto &e : edges) {
      if (e.first > e.second) {
        e = std::make_pair(e.second, e.first);
      }
    }
    std::sort(edges.begin(), edges.end());
    edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
    shuffle(edges.begin(), edges.end());
    auto label = rnd.perm(n, 1);
    printf("%d %d %d\n", n, static_cast<int>(edges.size()), k);
    for (auto &&e : edges) {
      int a = e.first;
      int b = e.second;
      if (rnd.next(0, 1)) {
        std::swap(a, b);
      }
      printf("%d %d\n", label[a], label[b]);
    }
  }
}
