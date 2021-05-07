#include "testlib.h"

#include <bits/stdc++.h>

namespace {

std::vector<int> random_tree(int n, int r) {
  std::vector<int> parent(n, -1);
  int y = r;
  for (int _ = 1; _ < n; ++_) {
    int x = rnd.next(0, n - 1);
    while (x == r || ~parent[x]) {
      y = x;
      x = rnd.next(0, n - 1);
    }
    parent[x] = y;
    y = x;
  }
  return parent;
}

struct Radius {
  Radius(int n, const std::vector<std::pair<int, int>> &edges)
      : radius(n), tree(n) {
    for (auto &&e : edges) {
      tree[e.first].push_back(e.second);
      tree[e.second].push_back(e.first);
    }
    std::vector<int> d0(n), d1(n), d2(n);
    dfs(d0, -1, 0, 0);
    int u0 = std::max_element(d0.begin(), d0.end()) - d0.begin();
    dfs(d1, -1, u0, 0);
    int u1 = std::max_element(d1.begin(), d1.end()) - d1.begin();
    dfs(d2, -1, u1, 0);
    for (int i = 0; i < n; ++i) {
      radius[i] = std::max(d1[i], d2[i]);
    }
  }

  int operator[](int i) const { return radius[i]; }

  void dfs(std::vector<int> &d, int p, int u, int du) {
    d[u] = du;
    for (int v : tree[u]) {
      if (v != p) {
        dfs(d, u, v, du + 1);
      }
    }
  }

  std::vector<int> radius;
  std::vector<std::vector<int>> tree;
};

} // namespace

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ensure(argc > 7);
  const std::string& tree_type = opt<std::string>("type");
  const int T = opt<int>("T");
  const int n = opt<int>("n");
  const int maxw = opt<int>("maxw");
  const int q = opt<int>("q");
  const int k = opt<int>("k");
  const int kw = opt<int>("kw");
  while (T--) {
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; ++i) {
      printf("%d%c", rnd.next(1, maxw), " \n"[i + 1 == n]);
    }
    std::vector<std::pair<int, int>> edges;
    if (strcmp(tree_type, "path") == 0) {
      std::vector<int> vertex(n);
      std::iota(vertex.begin(), vertex.end(), 0);
      shuffle(vertex.begin(), vertex.end());
      for (int i = 1; i < n; ++i) {
        edges.emplace_back(vertex[i - 1], vertex[i]);
      }
    } else {
      int root = rnd.next(0, n - 1);
      auto parent = random_tree(n, root);
      for (int i = 0; i < n; ++i) {
        if (i != root) {
          edges.emplace_back(parent[i], i);
        }
      }
    }
    shuffle(edges.begin(), edges.end());
    for (auto &&e : edges) {
      if (rnd.next(0, 1)) {
        printf("%d %d\n", e.first + 1, e.second + 1);
      } else {
        printf("%d %d\n", e.second + 1, e.first + 1);
      }
    }
    std::vector<int> qk(q, 1);
    for (int i = 0; i < k; ++i) {
      int index = rnd.wnext(0, q - 1, kw);
      qk[index] = std::min(qk[index] + 1, n);
    }
    shuffle(qk.begin(), qk.end());
    Radius radius(n, edges);
    for (int i = 0; i < q; ++i) {
      printf("%d", qk[i]);
      for (int j = 0; j < qk[i]; ++j) {
        int v = rnd.next(1, n);
        int d = rnd.next(0, radius[v - 1]);
        printf(" %d %d", v, d);
      }
      puts("");
    }
  }
}
