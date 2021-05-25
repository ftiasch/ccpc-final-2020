#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>

using pii = std::pair<int, int>;

const int N = 1e4 + 10, M = 1e6 + 10;

char s[N];
int _table[M * 2 + 1], pw[10];
int *table = _table + M;

int dp[2][11][50001];
int small_dp[2][M * 2 + 1];

void prepare() {
  pw[0] = 1;
  for (int i = 1; i < 10; ++i) {
    pw[i] = pw[i - 1] * 10;
  }
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  for (int i = -M; i <= M; ++i)
    table[i] = -1;
  table[0] = 0;
  pq.emplace(0, 0);
  while (!pq.empty()) {
    int d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (table[u] < d)
      continue;
    for (int e = 0; e < 2; ++e) {
      for (int i = 1; i <= 7; ++i) {
        int v = u + (pw[i] - 1) / 9 * (e == 0 ? 1 : -1);
        if (-M <= v && v <= M && (table[v] == -1 || table[v] > d + i)) {
          table[v] = d + i;
          pq.emplace(d + i, v);
        }
      }
    }
  }
}

int &at(int i, int carry, int sum) { return dp[i & 1][carry + 5][sum + 25000]; }

int &at(int i, int sum) { return small_dp[i & 1][sum + M]; }

void update(int &x, int y) {
  if (x == -1 || x > y)
    x = y;
}

int main() {
  prepare();
  while (scanf("%s", s) == 1) {
    int n = strlen(s);
    if (n <= 5) {
      int v = std::atoi(s);
      printf("%d\n", table[v]);
      continue;
    }
    std::reverse(s, s + n);
    for (int i = 0, c = 0; i < n || (i >= n && c); ++i) {
      int o = c + (i < n ? (s[i] - '0') : 0) * 9;
      s[i] = '0' + o % 10;
      if (i >= n)
        s[i + 1] = 0;
      c = o / 10;
    }

    const int carry_bound = 1;
    const int x_bound = 6;

    n = strlen(s);
    memset(dp, -1, sizeof(dp));
    at(n + 1, 0, 0) = 0;
    for (int i = n + 1; i > 5; --i) {
      memset(dp[(i - 1) & 1], -1, sizeof(dp[0]));
      int o = (i - 1 < n) ? (s[i - 1] - '0') : 0;
      for (int carry = -carry_bound; carry <= carry_bound; ++carry) {
        for (int sum = -x_bound * n; sum <= n * x_bound; ++sum) {
          int w = at(i, carry, sum);
          if (w == -1)
            continue;
          for (int x = -x_bound; x <= x_bound; ++x) {
            int new_carry = carry * 10 + x - o;
            int new_sum = x + sum;
            // printf("i=%d carry=%d sum=%d new_carry=%d new_sum=%d\n", i,
            // carry, sum, new_carry, new_sum);
            if (-carry_bound <= new_carry && new_carry <= carry_bound) {
              update(at(i - 1, new_carry, new_sum), w + std::abs(x) * (i - 1));
            }
          }
        }
      }
    }
    memset(small_dp, -1, sizeof(small_dp));
    for (int carry = -carry_bound; carry <= carry_bound; ++carry) {
      for (int sum = -x_bound * n; sum <= n * x_bound; ++sum) {
        int w = at(5, carry, sum);
        if (w == -1)
          continue;
        // printf("carry=%d sum=%d %d %d\n", carry, sum, carry * 100000 - sum,
        // w);
        update(at(5, carry * 100000 - sum), w);
      }
    }
    int p10 = 10000;
    for (int i = 5; i >= 1; --i) {
      int o = s[i - 1] - '0';
      memset(small_dp[(i - 1) & 1], -1, sizeof(small_dp[0]));
      for (int sum = -M; sum <= M; ++sum) {
        int w = at(i, sum);
        if (w == -1)
          continue;
        for (int x = -x_bound; x <= x_bound; ++x) {
          update(at(i - 1, sum + x * p10 - x - o * p10),
                 w + std::abs(x) * (i - 1));
        }
      }
      p10 /= 10;
    }
    printf("%d\n", at(0, 0));
  }
  return 0;
}
