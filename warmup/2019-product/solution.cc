#include <cstdio>
#include <iostream>

const int NUM[] = {1, 3, 673, 2019};

void count(int n, int *cnt) {
  cnt[3] = n / 2019;
  cnt[2] = n / 3 - cnt[3];
  cnt[1] = n / 673 - cnt[3];
  cnt[0] = n - cnt[1] - cnt[2] - cnt[3];
}

long long solve(int n, int m) {
  static int a[4], b[4];
  count(n, a);
  count(m, b);
  long long result = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (NUM[i] * NUM[j] % 2019 == 0) {
        result += 1LL * a[i] * b[j];
      }
    }
  }
  return result;
}

int main() {
  int a, b, c, d;
  while (scanf("%d%d%d%d", &a, &b, &c, &d) == 4) {
    a--, c--;
    std::cout << solve(b, d) - solve(a, d) - solve(b, c) + solve(a, c)
              << std::endl;
  }
}
