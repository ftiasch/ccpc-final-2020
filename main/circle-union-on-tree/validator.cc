#include "testlib.h"

#include <bits/stdc++.h>

struct DSU {
  DSU(int n) : parent(n) { std::iota(parent.begin(), parent.end(), 0); }

  int find(int u) {
    if (parent[u] != u) {
      parent[u] = find(parent[u]);
    }
    return parent[u];
  }

  bool merge(int a, int b) {
    if (find(a) == find(b)) {
      return false;
    }
    parent[find(a)] = find(b);
    return true;
  }

  std::vector<int> parent;
};

int main() {
  registerValidation();
  int sum_n = 0;
  int sum_q = 0;
  int sum_k = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 100'000);
    inf.readSpace();
    int q = inf.readInt(1, 100'000);
    inf.readEoln();
    ensure((sum_n += n) <= 100'000);
    ensure((sum_q += q) <= 100'000);
    for (int i = 0; i < n; ++i) {
      inf.readInt(1, 10'000);
      if (i + 1 < n) {
        inf.readSpace();
      } else {
        inf.readEoln();
      }
    }
    DSU dsu(n);
    for (int i = 1; i < n; ++i) {
      int a = inf.readInt(1, n) - 1;
      inf.readSpace();
      int b = inf.readInt(1, n) - 1;
      inf.readEoln();
      ensure(dsu.merge(a, b));
    }
    for (int i = 0; i < q; ++i) {
      int k = inf.readInt(1, n);
      ensure((sum_k += k) <= 200'000);
      for (int j = 0; j < k; ++j) {
        inf.readSpace();
        inf.readInt(1, n);
        inf.readSpace();
        inf.readInt(0, n - 1);
      }
      inf.readEoln();
    }
  }
  inf.readEof();
}
