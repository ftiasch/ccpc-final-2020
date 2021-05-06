#include <bits/stdc++.h>

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i < n; ++i) {
      scanf("%*d%*d");
    }
    printf("%d\n", n / 3);
  }
}
