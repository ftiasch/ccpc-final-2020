#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

namespace {

template <typename T, typename U> inline void enlarge(T &a, U b) {
  if (a < b)
    a = b;
}

using LL = long long;
const int kN = 100000 + 5;
const int MAGIC = 256;
const int NUM_MAGIC = (kN + MAGIC - 1) / MAGIC * 10;

struct Edge {
  int u, v;
};

std::string to_string(const Edge &e) {
  return std::string("Edge{") + std::to_string(e.u) + ", " +
         std::to_string(e.v) + "}";
}

template <typename T, typename U, int N> struct TreeT {
  T start[N + 1];
  U v[N << 1];
  T n;
  T m = 0;

  std::pair<T, U> tree_buffer[N << 1];

  void init(T n) {
    this->n = n;
    clear();
  }

  void clear() {
    memset(start, 0, sizeof(T) * (n + 1));
    m = 0;
  }

  void add_edge(T x, const U &y) {
    ++start[x];
    tree_buffer[m].first = x;
    tree_buffer[m++].second = y;
  }

  void make() {
    for (T i = 0; i < n; ++i) {
      start[i + 1] += start[i];
    }
    for (int i = 0; i < m; ++i) {
      v[--start[tree_buffer[i].first]] = tree_buffer[i].second;
    }
  }
};

using OriginalTree = TreeT<int, int, kN>;
using Tree = TreeT<int16_t, int16_t, MAGIC << 1>;

OriginalTree original_tree;
int16_t weight[kN];

int n, m;
int result[kN];

struct Borders {
  int a[2] = {-1, -1};

  int operator[](int index) const { return a[index]; }

  int size() const { return (a[0] != -1) + (a[1] != -1); }

  void recv(const Borders &other) {
    CHECK(a[1] == -1 && other.a[1] == -1);
    if (a[0] == -1)
      a[0] = other.a[0];
  }

  void emplace_back(int u) { a[a[0] != -1] = u; }

  bool empty() const { return a[0] == -1; }
};

struct Cluster {
  Borders borders;
  std::vector<Edge> E;
  int id = -1;

  bool can_merge_with(const Cluster &other) const {
    return borders.size() + other.borders.size() <= 1 &&
           (E.size() < MAGIC || E.size() + other.E.size() < 2 * MAGIC);
  }

  void recv(Cluster &other) {
    if (other.E.size() > E.size()) {
      std::swap(other.E, E);
    }
    borders.recv(std::move(other.borders));
    std::move(other.E.begin(), other.E.end(), std::back_inserter(E));
  }
};

void swap(Cluster &lhs, Cluster &rhs) {
  std::swap(lhs.borders, rhs.borders);
  std::swap(lhs.E, rhs.E);
  std::swap(lhs.id, rhs.id);
}

bool operator<(const Cluster &lhs, const Cluster &rhs) {
  if (lhs.borders.size() != rhs.borders.size()) {
    return lhs.borders.size() > rhs.borders.size();
  }
  return lhs.E.size() < rhs.E.size();
}

std::vector<Cluster> clusters;

void decompose(int u, int fa, const OriginalTree &tree) {
  static std::vector<Cluster> holded_clusters;
  int cnt_borders = 0;
  int h = holded_clusters.size();
  for (int i = tree.start[u]; i < tree.start[u + 1]; ++i) {
    int v = tree.v[i];
    if (v == fa)
      continue;
    decompose(v, u, tree);
    int hh = holded_clusters.size();
    cnt_borders += holded_clusters[hh - 1].borders.size();
    holded_clusters[hh - 1].E.emplace_back(Edge{.u = u, .v = v});
  }
  int hh = holded_clusters.size();
  if (h == hh) {
    holded_clusters.emplace_back();
    return;
  }
  {
    std::sort(holded_clusters.begin() + h, holded_clusters.begin() + hh);
    int ww = h;
    while (ww < hh && holded_clusters[ww].borders.size() == 1)
      ++ww;
    for (int i = ww, j = h; i < hh; ++i) {
      while (j < ww && !holded_clusters[j].can_merge_with(holded_clusters[i]))
        ++j;
      if (j < ww && holded_clusters[j].can_merge_with(holded_clusters[i])) {
        holded_clusters[j].recv(holded_clusters[i]);
      } else {
        holded_clusters[ww++] = holded_clusters[i];
      }
    }
    hh = ww;
    holded_clusters.resize(hh);
  }
  if (fa != -1 && cnt_borders <= 1 && hh <= h + 1 &&
      holded_clusters[hh - 1].E.size() < MAGIC) {
    CHECK(h + 1 == hh);
    return;
  }
  int keeped = -1;
  for (int i = h; i < hh; ++i) {
    Cluster &cluster = holded_clusters[i];
    if (cluster.borders.empty()) {
      if (fa != -1 && keeped == -1 && cluster.E.size() < MAGIC) {
        keeped = i;
      } else {
        cluster.borders.emplace_back(cluster.E[cluster.E.size() / 2].v);
      }
    }
    cluster.borders.emplace_back(u);
  }
  if (keeped != -1) {
    std::swap(holded_clusters[h], holded_clusters[keeped]);
    ++h;
  }
  std::move(holded_clusters.begin() + h, holded_clusters.end(),
            std::back_inserter(clusters));
  holded_clusters.resize(h);
  if (keeped == -1) {
    holded_clusters.emplace_back();
    holded_clusters.back().borders.emplace_back(u);
  }
}

struct Hash {
  int16_t table[kN];
  int relative_points[NUM_MAGIC];
  int16_t tot = 0;

  Hash() { memset(table, -1, sizeof(table)); }

  void put(int x) {
    if (table[x] == -1) {
      relative_points[tot] = x;
      table[x] = tot++;
    }
  }

  int hash(int x) const {
    CHECK(table[x] != -1);
    return table[x];
  }

  int hash_no_check(int x) const { return table[x]; }

  void clear() {
    for (int i = 0; i < tot; ++i)
      table[relative_points[i]] = -1;
    tot = 0;
  }
};

struct SparseTable {
  int u[18][kN << 1];
  int8_t lg[kN << 1];

  int *access() { return u[0]; }

  void build(int n) {
    lg[0] = -1;
    for (int i = 1; i < kN << 1; ++i)
      lg[i] = lg[i >> 1] + 1;
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        u[j][i] = std::min(u[j - 1][i], u[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int ask(int a, int b) const {
    CHECK(a <= b);
    int k = lg[b - a + 1];
    return std::min(u[k][a], u[k][b - (1 << k) + 1]);
  }
};

struct RmqLca {
  int n;
  int dfn[kN], rd[kN << 1], depth[kN];
  int stmp;
  SparseTable st;
  int *dr = st.access();

  void init(int size) {
    n = size;
    stmp = 0;
  }

  void build(const OriginalTree &tree) {
    this->dfs(0, -1, tree);
    st.build(stmp);
  }

  int get_lca_depth(int a, int b) const {
    if (dfn[a] > dfn[b])
      std::swap(a, b);
    return rd[st.ask(dfn[a], dfn[b])];
  }

  int get_dist(int a, int b) const {
    return depth[a] + depth[b] - (get_lca_depth(a, b) << 1);
  }

  void dfs(int u, int fa, const OriginalTree &tree) {
    depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    dfn[u] = stmp;
    dr[stmp] = stmp;
    rd[stmp++] = depth[u];
    for (int i = tree.start[u]; i < tree.start[u + 1]; ++i) {
      int v = tree.v[i];
      if (v == fa)
        continue;
      this->dfs(v, u, tree);
      dr[stmp++] = dfn[u];
    }
  }
};

RmqLca lca_solver;

// u --> [-d' -- v -- d']
int get_radius(int u, int d, int v) { return d - lca_solver.get_dist(u, v); }

struct Circle {
  int p, d;
};

struct Query {
  std::vector<Circle> circles;
};

struct QueryContext {
  Query query;
  int id;
};

QueryContext query_contexts[kN];

struct ClusterContext {
  Tree tree;
  Borders borders;
  Hash hash;
  int16_t tot;

  std::pair<int16_t, int16_t> seq[MAGIC << 1][MAGIC << 1];
  int16_t dist_table[MAGIC << 1][MAGIC << 1];

  int table[MAGIC << 1][MAGIC << 1];
  int16_t table_dim[2];

  int8_t mark[MAGIC << 1];

  int16_t hashed_weight[MAGIC << 1];

  void build(const Cluster &cluster) {
    CHECK(!cluster.E.empty());
    CHECK(cluster.borders.size() == 2);
    hash.clear();
    // So that we map borders[0] to 0 and borders[1] to 1 respectively.
    hash.put(cluster.borders[0]);
    hash.put(cluster.borders[1]);
    for (const Edge &e : cluster.E) {
      hash.put(e.u);
      hash.put(e.v);
    }
    tot = hash.tot;

    for (int16_t i = 0; i < tot; ++i) {
      hashed_weight[i] = weight[hash.relative_points[i]];
    }

    tree.init(tot);
    for (const Edge &e : cluster.E) {
      int x = hash.hash(e.u);
      int y = hash.hash(e.v);
      tree.add_edge(x, y);
      tree.add_edge(y, x);
    }
    tree.make();
    borders = cluster.borders;

    for (int i = 0; i < tot; ++i) {
      bfs(i);
    }
  }

  void bfs(int16_t source) {
    dist_table[source][source] = 0;
    int16_t qe = 0;
    seq[source][qe].first = 0;
    seq[source][qe++].second = source;
    static int16_t par[MAGIC << 1];
    memset(par, -1, sizeof(par[0]) * hash.tot);
    for (int16_t qf = 0; qf < qe; ++qf) {
      int16_t d = seq[source][qf].first;
      int16_t u = seq[source][qf].second;
      for (int16_t i = tree.start[u]; i < tree.start[u + 1]; ++i) {
        int16_t v = tree.v[i];
        if (v == par[u])
          continue;
        par[v] = u;
        seq[source][qe].first = d + 1;
        seq[source][qe++].second = v;
        dist_table[source][v] = d + 1;
      }
    }

    int p = seq[0][tot - 1].first + 1;
    int q = seq[1][tot - 1].first + 1;
    table_dim[0] = p;
    table_dim[1] = q;
    memset(mark, 0, sizeof(mark[0]) * tot);
    int sum_weight_x = 0;
    for (int i = 0, x = 0; i < p; ++i) {
      memset(table[i], 0, sizeof(table[0][0]) * q);
      while (x < tot && seq[0][x].first <= i) {
        sum_weight_x += hashed_weight[seq[0][x].second];
        mark[seq[0][x++].second] = 1;
      }
      int sum_weight = sum_weight_x;
      for (int j = 0, y = 0; j < tot; ++j) {
        while (y < tot && seq[1][y].first <= j) {
          if (!mark[seq[1][y].second]) {
            sum_weight += hashed_weight[seq[1][y].second];
          }
          ++y;
        }
        table[i][j] = sum_weight;
      }
    }
  }

  void remark(int p, int d) {
    for (int i = 0; i < tot; ++i) {
      if (seq[p][i].first > d)
        break;
      mark[seq[p][i].second] = 1;
    }
  }

  int calc(int d0, int d1, const Circle inner_circles[kN],
           int num_inner_circles) {
    if (d0 >= table_dim[0] - 1 || d1 >= table_dim[1] - 1) {
      return table[table_dim[0] - 1][0];
    }
    if (num_inner_circles == 0) {
      return table[d0][d1];
    }
    memset(mark, 0, sizeof(mark[0]) * tot);
    remark(0, d0);
    remark(1, d1);
    for (int i = 0; i < num_inner_circles; ++i) {
      const Circle &circle = inner_circles[i];
      remark(circle.p, circle.d);
    }
    int ret = 0;
    for (int i = 0; i < tot; ++i)
      if (mark[i])
        ret += hashed_weight[i];
    return ret;
  }

  int calc_border(bool need_border[2], int d[2], const Circle inner_circles[kN],
                  int num_inner_circles) {
    int ret = 0;
    for (int i = 0; i < 2; ++i) {
      if (need_border[i]) {
        bool ok = false;
        ok |= d[i] >= 0;
        ok |= d[i ^ 1] >= dist_table[0][1];
        for (int j = 0; !ok && j < num_inner_circles; ++j) {
          ok |= dist_table[i][inner_circles[j].p] <= inner_circles[j].d;
        }
        if (ok) {
          ret += hashed_weight[i];
        }
      }
    }
    return ret;
  }
};

ClusterContext cluster_context;

Hash border_hash;

int16_t belong[kN];

void solve() {
  if (n <= 1) {
    for (int i = 0; i < m; ++i) {
      result[i] = weight[0];
    }
    return;
  }
  clusters.clear();
  decompose(0, -1, original_tree);
  for (int i = 0; i < clusters.size(); ++i) {
    clusters[i].id = i;
    CHECK(clusters[i].E.size() <= MAGIC * 2);
  }
  lca_solver.init(n);
  lca_solver.build(original_tree);
  memset(belong, -1, sizeof(belong[0]) * n);

  for (int c = 0; c < clusters.size(); ++c) {
    const Cluster &cluster = clusters[c];
    CHECK(cluster.borders.size() == 2);
    cluster_context.build(cluster);

    const int sum_border_weight =
        cluster_context.hashed_weight[0] + cluster_context.hashed_weight[1];

    bool need_border[2] = {};
    for (int j = 0; j < 2; ++j) {
      if (belong[cluster.borders[j]] == -1) {
        need_border[j] = true;
        belong[cluster.borders[j]] = c;
      }
    }

    int d[2];
    static Circle inner_circles[kN];
    int num_inner_circles;

    for (int q = 0; q < m; ++q) {
      QueryContext &query_context = query_contexts[q];
      const Query &query = query_context.query;

      d[0] = d[1] = -1;
      num_inner_circles = 0;

      for (int i = 0; i < query.circles.size(); ++i) {
        const Circle &circle = query.circles[i];
        int p = cluster_context.hash.hash_no_check(circle.p);
        if (p >= 0 && p < 2) {
          enlarge(d[p], circle.d);
        } else if (p >= 2) {
          if (cluster_context.seq[p][cluster_context.tot - 1].first <=
              circle.d) {
            d[0] = cluster_context.table_dim[0] - 1;
          } else {
            inner_circles[num_inner_circles].p = p;
            inner_circles[num_inner_circles].d = circle.d;
            ++num_inner_circles;
          }
        } else {
          enlarge(d[0], get_radius(circle.p, circle.d, cluster.borders[0]));
          enlarge(d[1], get_radius(circle.p, circle.d, cluster.borders[1]));
        }
      }

      result[q] += cluster_context.calc_border(need_border, d, inner_circles,
                                               num_inner_circles);

      enlarge(d[0], 0);
      enlarge(d[1], 0);
      result[q] +=
          cluster_context.calc(d[0], d[1], inner_circles, num_inner_circles) -
          sum_border_weight;
    }
  }
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n >> m) {
    for (int i = 0; i < n; ++i) {
      reader >> weight[i];
    }
    original_tree.init(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      reader >> a >> b;
      --a;
      --b;
      original_tree.add_edge(a, b);
      original_tree.add_edge(b, a);
    }
    original_tree.make();

    for (int i = 0; i < m; ++i) {
      int k;
      reader >> k;
      CHECK(k > 0);
      query_contexts[i].query.circles.resize(k);
      for (int j = 0; j < k; ++j) {
        Circle &circle = query_contexts[i].query.circles[j];
        reader >> circle.p >> circle.d;
        --circle.p;
        query_contexts[i].id = i;
      }
    }
    std::fill(result, result + m, 0);
    solve();
    for (int i = 0; i < m; ++i) {
      printf("%d\n", result[i]);
    }
  }
}
