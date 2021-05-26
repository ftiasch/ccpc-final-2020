#include <bits/stdc++.h>

struct DSU {
  DSU(int n) : size(n, 1), parent(n) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  int find(int u) {
    if (parent[u] != u) {
      parent[u] = find(parent[u]);
    }
    return parent[u];
  }

  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      size[a] += size[b];
      parent[b] = a;
    }
  }

  std::vector<int> size, parent;
};

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    DSU dsu{n};
    int empties = 0;
    for (int i = 0, k; i < m; ++i) {
      scanf("%d", &k);
      int s[2];
      for (int j = 0; j < k; ++j) {
        scanf("%d", s + j);
        s[j]--;
      }
      empties += k == 0;
      if (k == 2) {
        dsu.merge(s[0], s[1]);
      }
    }
    std::vector<int> components;
    for (int i = 0; i < n; ++i) {
      if (dsu.parent[i] == i) {
        components.push_back(dsu.size[i]);
      }
    }
    std::sort(components.begin(), components.end(), std::greater<int>());
    std::cout << "n=" << n << "|m=" << m << "|empties=" << empties
              << "|count=" << components.size();
    for (size_t i = 0; i < components.size() && i < 10; ++i) {
      std::cout << ",|"[i == 0] << components[i];
    }
    std::cout << std::endl;
  }
}
