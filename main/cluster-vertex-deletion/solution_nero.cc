#include <bits/stdc++.h>

#include "./common.h"

#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

namespace {

const int kN = N + 5;
const int MOD = 998244353;

using LL = long long;
int n, m, k;
bool graph[kN][kN];
std::set<LL> set;
std::vector<LL> anti_chains;
LL binom[kN][kN];

bool has(LL mask, int at) { return mask >> at & 1; }

void search(LL mask, int num_deleted) {
  int a, b, c;
  auto find = [&]() -> bool {
    for (a = 0; a < n; ++a)
      if (has(mask, a))
        for (b = 0; b < n; ++b)
          if (a != b && has(mask, b) && graph[a][b])
            for (c = 0; c < n; ++c)
              if (a != c && b != c && has(mask, c) && graph[a][c] &&
                  !graph[b][c])
                return true;
    return false;
  };
  if (!find()) {
    set.emplace(mask);
    return;
  }
  if (num_deleted >= k)
    return;
  search(mask ^ 1LL << a, num_deleted + 1);
  search(mask ^ 1LL << b, num_deleted + 1);
  search(mask ^ 1LL << c, num_deleted + 1);
}

void make_anti_chain() {
  anti_chains.clear();
  for (auto it = set.rbegin(); it != set.rend(); ++it) {
    LL p = *it;
    auto judge = [&](LL p) -> bool {
      for (LL q : anti_chains) {
        if ((p & q) == p)
          return false;
      }
      return true;
    };
    if (judge(p))
      anti_chains.emplace_back(p);
  }
}

int num_deleted(LL mask) { return n - __builtin_popcountll(mask); }

LL calc(int at, LL mask) {
  int d = num_deleted(mask);
  if (d > k)
    return 0;
  for (int i = at; i < anti_chains.size(); ++i) {
    if ((mask & anti_chains[i]) == mask) {
      return 0;
    }
  }
  LL ret = binom[n - d][k - d];
  for (int i = at; i < anti_chains.size(); ++i) {
    ret -= calc(i + 1, mask & anti_chains[i]);
  }
  return ret;
}

LL solve() {
  if (n < k)
    return 0;
  if (n == k)
    return 1;
  set.clear();
  search((1LL << n) - 1, 0);
  DUMP(set);
  make_anti_chain();
  LL result = 0;
  DUMP(anti_chains);
  for (int i = 0; i < anti_chains.size(); ++i) {
    result += calc(i + 1, anti_chains[i]);
  }
  return result;
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  for (int i = 0; i < kN; ++i) {
    binom[i][i] = binom[i][0] = 1;
    for (int j = 1; j < i; ++j)
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
  }

  while (reader >> n >> m >> k) {
    memset(graph, false, sizeof(graph));
    for (int i = 0; i < m; ++i) {
      int a, b;
      reader >> a >> b;
      --a;
      --b;
      graph[a][b] = graph[b][a] = true;
    }
    printf("%lld\n", solve() % MOD);
  }
}
