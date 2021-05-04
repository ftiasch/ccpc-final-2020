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

std::multiset<int> sets[kN];

void solve() {
  for (int j = 0; j < m; ++j) {
    sets[j].clear();
    for (int i = 0; i < h; ++i) {
      sets[j].emplace(a[i][j]);
    }
  }
  for (int i = 0; i + h <= n; ++i) {
    using IterType = std::multiset<int>::iterator;
    static IterType last_iter[kN];
    std::set<std::pair<int, int>> best_ks;
    for (int j = 0; j < w; ++j) {
      CHECK(!sets[j].empty());
      last_iter[j] = sets[j].begin();
      best_ks.emplace(*last_iter[j], j);
    }

    for (int j = 0; j + w <= m; ++j) {
      static int updated[K];
      int val = 0;
      for (int r = 0; r < k; ++r) {
        CHECK(!best_ks.empty());
        int& id = updated[r];
        std::tie(val, id) = *best_ks.begin();
        best_ks.erase(best_ks.begin());
        CHECK(last_iter[id] != sets[id].end());
        if (++last_iter[id] != sets[id].end()) {
          best_ks.emplace(*last_iter[id], id);
        }
      }
      printf("%d%c", val, " \n"[j + w == m]);
      if (j + w < m) {
        for (int r = 0; r < k; ++r) {
          int id = updated[r];
          if (last_iter[id] != sets[id].begin()) {
            if (last_iter[id] != sets[id].end()) {
              best_ks.erase(std::make_pair(*last_iter[id], id));
            }
            last_iter[id] = sets[id].begin();
            CHECK(last_iter[id] != sets[id].end());
            best_ks.emplace(*last_iter[id], id);
          }
        }
        CHECK(!sets[j + w].empty());
        last_iter[j + w] = sets[j + w].begin();
        CHECK(last_iter[j + w] != sets[j + w].end());
        best_ks.emplace(*last_iter[j + w], j + w);
        best_ks.erase(std::make_pair(*last_iter[j], j));
      }
    }

    if (i + h < n) {
      for (int j = 0; j < m; ++j) {
        sets[j].emplace(a[i + h][j]);
        sets[j].erase(sets[j].find(a[i][j]));
      }
    }
  }
}

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  while (reader >> n >> m >> h >> w >> k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        reader >> a[i][j];
      }
    }
    solve();
  }
}
