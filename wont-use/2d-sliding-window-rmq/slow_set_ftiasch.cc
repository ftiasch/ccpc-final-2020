#include <bits/stdc++.h>

#include "./common.h"

namespace {

int a[N][N];

struct MultiSet : public std::multiset<int> {
  void get_kth(int k, int *result) const {
    auto iterator = begin();
    for (int i = 0; i < k; ++i) {
      if (iterator == end()) {
        result[i] = std::numeric_limits<int>::max();
      } else {
        result[i] = *(iterator++);
      }
    }
  }

  void erase_one(int v) { erase(find(v)); }
};

MultiSet column[N];
int buffer[N][K], buffer0[K];
} // namespace

int main() {
  int n, m, h, w, k;
  while (scanf("%d%d%d%d%d", &n, &m, &h, &w, &k) == 5) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", a[i] + j);
      }
    }
    for (int j = 0; j < m; ++j) {
      column[j].clear();
      for (int i = 0; i < h - 1; ++i) {
        column[j].insert(a[i][j]);
      }
    }
    MultiSet row;
    for (int i = h - 1; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        column[j].insert(a[i][j]);
        column[j].get_kth(k, buffer[j]);
      }
      row.clear();
      for (int j = 0; j < w - 1; ++j) {
        for (int t = 0; t < k; ++t) {
          row.insert(buffer[j][t]);
        }
      }
      for (int j = w - 1; j < m; ++j) {
        for (int t = 0; t < k; ++t) {
          row.insert(buffer[j][t]);
        }
        row.get_kth(k, buffer0);
        printf("%d%c", buffer0[k - 1], " \n"[j + 1 == m]);
        for (int t = 0; t < k; ++t) {
          row.erase_one(buffer[j - w + 1][t]);
        }
      }
      for (int j = 0; j < m; ++j) {
        column[j].erase_one(a[i - h + 1][j]);
      }
    }
  }
}
