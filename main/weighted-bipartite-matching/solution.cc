#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <deque>
#include <numeric>
#include <vector>

static constexpr int N = 1000;

template <class cost_t = int64_t> struct KuhnMunkres {
  static constexpr cost_t inf = std::numeric_limits<cost_t>::max();

  cost_t x[N], y[N]; // label of left/right
  int match_x[N], match_y[N];
  int n, m;

  bool try_aug(int v) {
    vis_y[v] = true;
    if (match_y[v] == -1) {
      while (v != -1) {
        match_y[v] = parent[v];
        std::swap(v, match_x[match_y[v]]);
      }
      return true;
    } else {
      vis_x[match_y[v]] = true;
      queue.push_back(match_y[v]);
    }
    return false;
  }

  void find(int src, const cost_t w[][N]) {
    memset(vis_x, 0, sizeof(*vis_x) * n);
    memset(vis_y, 0, sizeof(*vis_y) * m);
    for (int v = 0; v < m; ++v)
      slack[v] = inf;
    queue.clear();
    queue.push_back(src);
    vis_x[src] = true;
    for (size_t i = 0;;) {
      for (; i < queue.size(); ++i) {
        int u = queue[i];
        for (int v = 0; v < m; ++v)
          if (!vis_y[v]) {
            if (x[u] + y[v] - w[u][v] < slack[v]) {
              slack[v] = x[u] + y[v] - w[u][v];
              parent[v] = u;
            }
            if (!slack[v] && try_aug(v))
              return;
          }
      }
      cost_t delta = inf;
      for (int v = 0; v < m; ++v) {
        if (!vis_y[v])
          delta = std::min(delta, slack[v]);
      }
      for (int u = 0; u < n; ++u) {
        if (vis_x[u])
          x[u] -= delta;
      }
      for (int v = 0; v < m; ++v) {
        if (vis_y[v])
          y[v] += delta;
        else
          slack[v] -= delta;
      }
      for (int v = 0; v < m; ++v) {
        if (!vis_y[v] && !slack[v] && try_aug(v))
          return;
      }
    }
  }

  // make sure n <= m
  void run(int _n, int _m, const cost_t w[][N]) {
    n = _n, m = _m;
    assert(n <= m);
    memset(y, 0, sizeof(*y) * m);
    memset(match_x, -1, sizeof(*match_x) * n);
    memset(match_y, -1, sizeof(*match_y) * m);
    for (int i = 0; i < n; ++i) {
      x[i] = *std::max_element(w[i], w[i] + m);
    }
    queue.reserve(n);
    for (int i = 0; i < n; ++i)
      find(i, w);
  }

private:
  cost_t slack[N];
  std::vector<int> queue;
  int parent[N];
  bool vis_x[N], vis_y[N];
};

int w[N][N], g[N][N];
KuhnMunkres<int> km;
int ret_left[N];
int n, m;

void spfa(int n, int src, int *dis) {
  std::vector<bool> mark(n);
  std::deque<int> queue;
  for (int i = 0; i < n; ++i)
    dis[i] = -km.inf;
  dis[src] = 0;
  queue.push_back(src);
  mark[src] = true;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop_front();
    mark[u] = false;
    for (int v = 0; v < n; ++v)
      if (g[u][v] != -km.inf) {
        if (dis[v] < dis[u] + g[u][v]) {
          dis[v] = dis[u] + g[u][v];
          if (!mark[v])
            queue.push_back(v);
          mark[v] = true;
        }
      }
  }
}

void init(int n) {
  for (int i = 0; i < n; ++i) {
    std::fill(g[i], g[i] + n, -km.inf);
  }
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    int vm = std::max(n, m);
    for (int i = 0; i < vm; ++i) {
      std::fill(w[i], w[i] + vm, 0);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &w[i][j]);
      }
    }
    km.run(n, vm, w);
    int weight = 0;
    for (int i = 0; i < n; ++i) {
      weight += w[i][km.match_x[i]];
    }
    // 1. remove vertex from left part
    int src = n + vm;
    init(src + 1);
    for (int x = 0; x < n; ++x) {
      int y = km.match_x[x];
      // printf("%d -> %d: %d\n", y + n, x, -w[x][y]);
      g[y + n][x] = -w[x][y];
    }
    for (int y = 0; y < vm; ++y) {
      int x = km.match_y[y];
      if (x != -1) {
        g[src][y + n] = 0;
        // printf("%d -> %d: %d\n", src, y + n, 0);
      }
    }
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < vm; ++y) {
        if (y == km.match_x[x])
          continue;
        g[x][y + n] = w[x][y];
        // printf("%d -> %d: %d\n", x, y + n, w[x][y]);
      }
    }
    spfa(src + 1, src, ret_left);
    // 2. solve remove two vertices case
    init(src + 1);
    for (int x = 0; x < n; ++x) {
      g[src][x] = 0;
    }
    for (int y = 0; y < vm; ++y) {
      int x = km.match_y[y];
      if (x == -1)
        g[src][y + n] = 0;
      else
        g[y + n][src] = 0;
    }
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < vm; ++y) {
        if (y == km.match_x[x])
          g[x][y + n] = -w[x][y];
        else
          g[y + n][x] = w[x][y];
      }
    }
    for (int k = 0; k <= src; ++k) {
      for (int i = 0; i <= src; ++i)
        if (g[i][k] != -km.inf) {
          for (int j = 0; j <= src; ++j)
            if (g[k][j] != -km.inf) {
              if (g[i][j] < g[i][k] + g[k][j]) {
                g[i][j] = g[i][k] + g[k][j];
              }
            }
        }
    }
    // 3. output answer
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (y)
          putchar(' ');
        if (km.match_y[y] == -1) { // y not matched
          printf("%d", ret_left[x] + weight);
        } else { // y matched
          printf("%d", g[x][y + n] + weight);
        }
      }
      puts("");
    }
  }
  return 0;
}
