#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

template <int kN, typename T> struct CostFlow {
  const T inf = std::numeric_limits<T>::max();
  int s, t, head[kN], etot, prevv[kN], preve[kN], inq[kN], que[kN], qf, qe;
  T dis[kN];
  struct Edge {
    int v, next;
    T cap, cost;
  } g[601000];
  void init() {
    memset(head, -1, sizeof(head));
    etot = 0;
  }
  void add_edge(int u, int v, T cap, T cost) {
    g[etot].v = v;
    g[etot].cap = cap;
    g[etot].cost = cost;
    g[etot].next = head[u];
    head[u] = etot++;
    g[etot].v = u;
    g[etot].cap = 0;
    g[etot].cost = -cost;
    g[etot].next = head[v];
    head[v] = etot++;
  }
  void spfa(int source) {
    for (int i = 0; i < kN; i++)
      dis[i] = inf;
    dis[source] = 0;
    qf = qe = 0;
    que[qe++] = source;
    while (qf != qe) {
      int u = que[qf++];
      inq[u] = 0;
      if (qf == kN)
        qf = 0;
      for (int i = head[u]; i != -1; i = g[i].next) {
        Edge &e = g[i];
        if (e.cap && dis[e.v] > dis[u] + e.cost) {
          dis[e.v] = dis[u] + e.cost;
          prevv[e.v] = u;
          preve[e.v] = i;
          if (!inq[e.v]) {
            que[qe++] = e.v;
            if (qe == kN)
              qe = 0;
            inq[e.v] = 1;
          }
        }
      }
    }
  }
  void mcmf(int _s, int _t, T &cost, T &flow) {
    s = _s;
    t = _t;
    cost = flow = 0;
    while (true) {
      spfa(_s);
      if (dis[t] == inf)
        break;
      T f = inf;

      for (int u = t; u != s; u = prevv[u])
        f = std::min(f, g[preve[u]].cap);
      cost += f * dis[t];
      flow += f;
      for (int u = t; u != s; u = prevv[u])
        g[preve[u]].cap -= f, g[preve[u] ^ 1].cap += f;
    }
  }
};

using Flow = CostFlow<1002, int>;
const int _s = 1000;
const int _t = 1001;

Flow f;
int n, m;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n >> m) {
    const int N = std::max(n, m);
    f.init();
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int w = 0;
        if (i < n && j < m) {
          reader >> w;
        }
        f.add_edge(i, j + N, 1, -w);
      }
    }
    for (int i = 0; i < N; ++i) {
      f.add_edge(_s, i, 1, 0);
      f.add_edge(i + N, _t, 1, 0);
    }
    int cost, flow;
    f.mcmf(_s, _t, cost, flow);
    CHECK(flow == N);
    std::vector<std::vector<int>> result(n, std::vector<int>(m));
    for (int j = 0; j < m; ++j) {
      f.spfa(j + N);
      for (int i = 0; i < n; ++i) {
        result[i][j] = cost + f.dis[i];
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%d%c", -result[i][j], " \n"[j + 1 == m]);
      }
    }
  }
}
