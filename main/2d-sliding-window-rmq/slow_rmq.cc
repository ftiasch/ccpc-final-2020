#include <bits/stdc++.h>

#include "./common.h"

#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

namespace {

template <typename RandomAccessIterator>
void radix_sort(RandomAccessIterator begin, RandomAccessIterator end,
                const std::function<int(const decltype(*begin) &)> &get_key) {
  const int n = std::distance(begin, end);
  if (n == 0)
    return;
  int L = 1;
  while (1 << (L + 1) <= n)
    ++L;
  const int m = 1 << L;
  const int mask = m - 1;
  int mx = 0;
  for (auto iter = begin; iter != end; ++iter)
    mx = std::max(mx, get_key(*iter));
  using ElemType = typename std::remove_reference<decltype(*begin)>::type;
  std::vector<ElemType> b(n);
  for (int step = 0; mx >> (L * step); ++step) {
    std::vector<int> bucket_size(m);
    for (auto iter = begin; iter != end; ++iter) {
      ++bucket_size[get_key(*iter) >> (L * step) & mask];
    }
    for (int i = 1; i < m; ++i)
      bucket_size[i] += bucket_size[i - 1];
    for (int i = n - 1; i >= 0; --i) {
      b[--bucket_size[get_key(*(begin + i)) >> (L * step) & mask]] =
          *(begin + i);
    }
    std::copy(b.begin(), b.end(), begin);
  }
}

const int kN = N + 5;

int n, m, h, w, k;
int a[kN][kN];
std::tuple<int, int, int> arr[kN * kN];

int get_key(const std::tuple<int, int, int> &tuple) {
  return std::get<0>(tuple);
}

void relabel() {
  int tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      arr[tot++] = std::make_tuple(a[i][j], i, j);
    }
  }
  radix_sort(arr, arr + tot, get_key);
  for (int i = 0; i < tot; ++i) {
    a[std::get<1>(arr[i])][std::get<2>(arr[i])] = i;
  }
}

struct BestK {
  int bests[K];
  int tot = 0;

  void init(int x) {
    tot = 0;
    bests[tot++] = x;
  }
};

BestK operator+(const BestK &lhs, const BestK &rhs) {
  static int tmp[K + K];
  std::merge(lhs.bests, lhs.bests + lhs.tot, rhs.bests, rhs.bests + rhs.tot,
             tmp);
  int tot = std::unique(tmp, tmp + lhs.tot + rhs.tot) - tmp;
  BestK ret;
  ret.tot = std::min(k, tot);
  std::copy(tmp, tmp + ret.tot, ret.bests);
  return ret;
}

int lg[kN];
BestK table[2][kN][kN];
int cur = 0;

void rmq_init() {
  lg[0] = -1;
  for (int i = 1; i < kN; ++i) {
    lg[i] = lg[i >> 1] + 1;
  }
  cur = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      table[cur][i][j].init(a[i][j]);
    }
  }
  for (int i = 1; i <= lg[h]; ++i) {
    int nex = cur ^ 1;
    for (int x = 0; x + (1 << i) - 1 < n; ++x) {
      for (int y = 0; y < m; ++y) {
        table[nex][x][y] = table[cur][x][y] + table[cur][x + (1 << (i - 1))][y];
      }
    }
    std::swap(cur, nex);
  }
  for (int j = 1; j <= lg[w]; ++j) {
    int nex = cur ^ 1;
    for (int x = 0; x + (1 << lg[h]) - 1 < n; ++x) {
      for (int y = 0; y + (1 << j) - 1 < m; ++y) {
        table[nex][x][y] = table[cur][x][y] + table[cur][x][y + (1 << (j - 1))];
      }
    }
    std::swap(cur, nex);
  }
}

void solve() {
  relabel();
  rmq_init();
  for (int i = 0; i + h <= n; ++i) {
    for (int j = 0; j + w <= m; ++j) {
      int x0 = i;
      int y0 = j;
      int x1 = x0 + h - 1 - (1 << lg[h]) + 1;
      int y1 = y0 + w - 1 - (1 << lg[w]) + 1;
      BestK best = table[cur][x0][y0] + table[cur][x0][y1] +
                   table[cur][x1][y0] + table[cur][x1][y1];
      CHECK(best.tot == k);
      int result = std::get<0>(arr[best.bests[k - 1]]);
      printf("%d%c", result, " \n"[j + w == m]);
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
