#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

template <typename T> inline void minify(T &a, T b) {
  if (a > b)
    a = b;
}

const int INF = 0x3f3f3f3f;

template <int kN> struct KM {
  int lv[kN], rv[kN], la[kN], ra[kN], left[kN], G[kN][kN], n, m;
  bool expath(int u) {
    lv[u] = 1;
    for (int i = 0; i < m; i++)
      if (!rv[i] && la[u] + ra[i] == G[u][i]) {
        rv[i] = 1;
        if (left[i] == -1 || expath(left[i]))
          return left[i] = u, true;
      }
    return false;
  }
  void init() {
    for (int i = 0; i < kN; i++)
      for (int j = 0; j < kN; j++)
        G[i][j] = -INF;
  }
  int km(int _n, int _m) {
    n = _n;
    m = _m;
    memset(left, -1, sizeof(left));
    for (int i = 0; i < n; i++) {
      la[i] = -INF;
      for (int j = 0; j < m; j++)
        la[i] = std::max(la[i], G[i][j]);
    }
    for (int i = 0; i < m; i++)
      ra[i] = 0;
    for (int u = 0; u < n; u++) {
      for (int i = 0; i < n; i++)
        lv[i] = 0;
      for (int i = 0; i < m; i++)
        rv[i] = 0;
      while (!expath(u)) {
        int d = INF;
        for (int i = 0; i < n; i++)
          if (lv[i])
            for (int j = 0; j < m; j++)
              if (!rv[j])
                d = std::min(d, la[i] + ra[j] - G[i][j]);
        for (int i = 0; i < n; i++)
          if (lv[i])
            la[i] -= d, lv[i] = 0;
        for (int i = 0; i < m; i++)
          if (rv[i])
            ra[i] += d, rv[i] = 0;
      }
    }
    int ret = 0;
    for (int i = 0; i < m; i++)
      if (left[i] != -1)
        ret += G[left[i]][i];
    return ret;
  }
};

int n, m;

KM<500> km;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n >> m) {
    const int N = std::max(n, m);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int w = 0;
        if (i < n && j < m) {
          reader >> w;
        }
        km.G[i][j] = w;
      }
    }
    int best = km.km(N, N);
    std::vector<std::vector<int>> graph(N + N, std::vector<int>(N + N, INF));
    for (int i = 0; i < graph.size(); ++i)
      graph[i][i] = 0;
    for (int u = 0; u < N; ++u) {
      for (int v = 0; v < N; ++v) {
        if (km.left[v] != u)
          minify(graph[u][v + N], -km.G[u][v]);
        else
          minify(graph[v + N][u], km.G[u][v]);
      }
    }
    for (int k = 0; k < graph.size(); ++k)
      for (int i = 0; i < graph.size(); ++i)
        for (int j = 0; j < graph.size(); ++j)
          minify(graph[i][j], graph[i][k] + graph[k][j]);
    std::vector<std::vector<int>> result(n, std::vector<int>(m));
    for (int j = 0; j < m; ++j) {
      for (int i = 0; i < n; ++i) {
        result[i][j] = -best + graph[j + N][i];
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%d%c", -result[i][j], " \n"[j + 1 == m]);
      }
    }
  }
}
