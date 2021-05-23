#include <bits/stdc++.h>

int main() {
  std::mt19937 gen{0};
  int n;
  while (scanf("%d", &n) == 1) {
    n = std::min(n, 2015);
    for (int i = 0; i < n; ++i) {
      puts("CCPC");
    }
  }
}
