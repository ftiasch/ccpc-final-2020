#include <bits/stdc++.h>

#include "./common.h"

namespace {

struct Candidate {
  Candidate() {
    std::fill(value, value + K, std::numeric_limits<int>::max());
  }

  void add(int v) {
    int i = 0;
    while (i < K && value[i] < v) {
      i ++;
    }
    if (i < K) {
      for (int j = K - 1; j > i; j --) {
        value[j] = value[j - 1];
      }
      value[i] = v;
    }
  }

  int operator[](int index) const {
    return value[index];
  }

  int& operator[](int index) {
    return value[index];
  }

  int value[K];
};

void merge(Candidate& result, const Candidate& a, const Candidate& b) {
  for (int k = 0, i = 0, j = 0; k < K; ++ k) {
    if (j == K || i < K && a[i] < b[j]) {
      result[k] = a[i ++];
    } else {
      result[k] = b[j ++];
    }
  }
}

int a[N][N];

}

int main() {
  int n, m, h, w, k;
  while (scanf("%d%d%d%d%d", &n, &m, &h, &w, &k) == 5) {
    for (int i = 0; i < n; ++ i) {
      for (int j = 0; j < m; ++ j) {
        scanf("%d", a[i] + j);
      }
    }

  }
}
