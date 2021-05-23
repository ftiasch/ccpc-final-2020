#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

int solve(int n, const std::string &s) {
  auto ok = [&](int k) -> bool {
    std::vector<int> start, end;
    for (int i = 0; i < n && start.size() < k; ++i) {
      if (s[i] == '2') {
        start.emplace_back(i);
      }
    }
    if (start.size() < k)
      return false;
    for (int i = n - 1; i >= 0 && end.size() < k; --i) {
      if (s[i] == '0') {
        end.emplace_back(i);
      }
    }
    if (end.size() < k)
      return false;
    std::reverse(end.begin(), end.end());
    int ca = 0, cb = 0;
    for (int i = 0; i < n && cb < k; ++i) {
      if (s[i] == '0') {
        if (i < end[0] && ca < k && start[ca] < i)
          ++ca;
      } else if (s[i] == '2') {
        if (i > start.back() && ca > cb && i < end[cb])
          ++cb;
      }
    }
    return cb == k;
  };
  int l = 1, r = n / 4;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (ok(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l - 1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  int n;
  std::string s;
  while (reader >> n >> s) {
    printf("%d\n", solve(n, s));
  }
}
