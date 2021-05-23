#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 50;

void update(int &x, int a) { x = std::max(x, a); }

int dp[N][N][N][N];

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    if (n >= N) {
      puts("-1");
    } else {
      memset(dp, -1, sizeof(dp));
      dp[0][0][0][0] = 0;
      for (int i = 0; i < n; ++i) {
        for (int l1 = 0; l1 <= i; ++l1) {
          for (int l2 = 0; l2 <= i; ++l2) {
            for (int l3 = 0; l3 <= i; ++l3) {
              int v = dp[i][l1][l2][l3];
              if (~v) {
                update(dp[i + 1][l1][l2][l3], v);
                if (s[i] == '2') {
                  update(dp[i + 1][l1 + 1][l2][l3], v);
                  if (l2) {
                    update(dp[i + 1][l1][l2 - 1][l3 + 1], v);
                  }
                }
                if (s[i] == '0') {
                  if (l1) {
                    update(dp[i + 1][l1 - 1][l2 + 1][l3], v);
                  }
                  if (l3) {
                    update(dp[i + 1][l1][l2][l3 - 1], v + 1);
                  }
                }
              }
            }
          }
        }
      }
      printf("%d\n", dp[n][0][0][0]);
    }
  }
}
