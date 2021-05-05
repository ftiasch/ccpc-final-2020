#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) 1145141919810
#endif

const int kN = 2000 + 5;
int n;
bool graph[kN][kN];

void solve() {
  std::list<int> path;
  path.emplace_back(0);
  path.emplace_back(1);
  auto seperator = path.begin(); // 11111 sp 000000

  auto adjust = [&]() -> void {
    CHECK(seperator != path.end());
    while (std::next(seperator) != path.end() &&
           graph[*seperator][*std::next(seperator)])
      ++seperator;
    while (seperator != path.begin() &&
           !graph[*std::prev(seperator)][*seperator])
      --seperator;
  };

  adjust();

  for (int i = 2; i < n; ++i) {
    if (std::next(seperator) == path.end()) {
      path.insert(std::next(seperator), i);
      if (graph[*seperator][i]) {
        ++seperator;
      }
    } else {
      if (graph[*seperator][i] >= graph[i][*std::next(seperator)]) {
        path.insert(std::next(seperator), i);
      } else {
        path.insert(seperator, i);
      }
    }
    adjust();
  }
  if (graph[*path.begin()][path.back()]) {
    int v = path.back();
    path.erase(std::prev(path.end()));
    path.insert(path.begin(), v);
  }
  std::vector<int> result(path.begin(), path.end());
  for (int i = 0; i < n; ++i) {
    printf("%d%c", result[i] + 1, " \n"[i + 1 == n]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  while (reader >> n) {
    for (int i = 0; i < n; ++i) {
      std::string s;
      reader >> s;
      for (int j = 0; j < n; ++j)
        graph[i][j] = s[j] - '0';
    }
    solve();
  }
}
