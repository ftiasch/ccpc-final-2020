#include <bits/stdc++.h>

#include "./common.h"

#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

namespace {

const int kN = N + 5;

int n, m, h, w, k;
int a[kN][kN];

struct BestK {
  int bests[K];
  int tot = 0;

  void reset() { tot = 0; }

  void feed(int x) {
    for (int i = 0; i < tot; ++i) {
      if (bests[i] > x)
        std::swap(bests[i], x);
    }
    if (tot < k)
      bests[tot++] = x;
  }
};

BestK operator+(const BestK &lhs, const BestK &rhs) {
  static int tmp[K + K];
  std::merge(lhs.bests, lhs.bests + lhs.tot, rhs.bests, rhs.bests + rhs.tot,
             tmp);
  BestK ret;
  ret.tot = std::min(k, lhs.tot + rhs.tot);
  std::copy(tmp, tmp + ret.tot, ret.bests);
  return ret;
}

// qwe
// asd
// zxc
BestK q[kN][kN], e[kN][kN], z[kN][kN], c[kN][kN];

void prepare(int bi, int bj) {
  int i = bi * h;
  int j = bj * w;
  static BestK tmp[kN];
  static BestK sum;
  for (int y = j; y < j + w && y < m; ++y) {
    tmp[y].reset();
  }
  for (int x = i; x < i + h && x < n; ++x) {
    sum.reset();
    for (int y = j; y < j + w && y < m; ++y) {
      tmp[y].feed(a[x][y]);
      sum = sum + tmp[y];
      q[x][y] = sum;
    }
  }
  if (j + w <= m) {
    for (int y = j + w - 1; y >= j; --y) {
      tmp[y].reset();
    }
    for (int x = i; x < i + h && x < n; ++x) {
      sum.reset();
      for (int y = j + w - 1; y >= j; --y) {
        tmp[y].feed(a[x][y]);
        sum = sum + tmp[y];
        e[x][y] = sum;
      }
    }
  }
  if (i + h <= n) {
    for (int y = j; y < j + w && y < m; ++y) {
      tmp[y].reset();
    }
    for (int x = i + h - 1; x >= i; --x) {
      sum.reset();
      for (int y = j; y < j + w && y < m; ++y) {
        tmp[y].feed(a[x][y]);
        sum = sum + tmp[y];
        z[x][y] = sum;
      }
    }
  }
  if (i + h <= n && j + w <= m) {
    for (int y = j + w - 1; y >= j; --y) {
      tmp[y].reset();
    }
    for (int x = i + h - 1; x >= i; --x) {
      sum.reset();
      for (int y = j + w - 1; y >= j; --y) {
        tmp[y].feed(a[x][y]);
        sum = sum + tmp[y];
        c[x][y] = sum;
      }
    }
  }
}

void solve() {
  for (int bi = 0; bi * h < n; ++bi) {
    for (int bj = 0; bj * w < m; ++bj) {
      prepare(bi, bj);
    }
  }
  for (int i = 0; i + h <= n; ++i) {
    for (int j = 0; j + w <= m; ++j) {
      BestK best = c[i][j];
      if (i % h) {
        best = best + e[i + h - 1][j];
      }
      if (j % w) {
        best = best + z[i][j + w - 1];
      }
      if (i % h && j % w) {
        best = best + q[i + h - 1][j + w - 1];
      }
      CHECK(best.tot == k);
      printf("%d%c", best.bests[k - 1], " \n"[j + w == m]);
    }
  }
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n >> m >> h >> w >> k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        reader >> a[i][j];
      }
    }
    solve();
  }
}
