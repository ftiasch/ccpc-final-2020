#include <bits/stdc++.h>

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
    }
    long long result = 0;
    std::vector<int> stack;
    stack.reserve(n);
    for (uint64_t mask = 1; mask < 1ULL << n; ++mask) {
      stack.clear();
      bool ok = true;
      int last = 0;
      for (int i = 0; i < n && ok; ++i) {
        if (mask >> i & 1) {
          while (!stack.empty() && stack.back() < p[i] && ok) {
            ok &= last < stack.back();
            last = stack.back();
            stack.pop_back();
          }
          stack.push_back(p[i]);
        }
      }
      while (!stack.empty() && ok) {
        ok &= last < stack.back();
        last = stack.back();
        stack.pop_back();
      }
      if (ok) {
        result++;
      }
    }
    std::cout << result << std::endl;
  }
}
