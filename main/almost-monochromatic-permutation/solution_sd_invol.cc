#include <bits/stdc++.h>
const int N = 2005;

int n;
char g[N][N];

void work() {
  for (int i = 0; i < n; ++i) {
    scanf("%s\n", g[i]);
  }
  std::vector<int> loop = {0, 1};
  for (int x = 2; x < n; ++x) {
    for (int i = 0; i < x; ++i) {
      int a = loop[(i + x - 1) % x];
      int b = loop[i];
      int c = loop[(i + 1) % x];
      if (g[a][b] == '0' && g[b][c] == '1') {
        std::rotate(loop.begin(), loop.begin() + i, loop.end());
        break;
      }
    }
    int pre = loop.back();
    int cur = loop[0];
    int nxt = loop[1];
    if (g[pre][cur] == g[cur][nxt]) {
      loop.emplace_back(x);
    } else {
      assert(g[pre][cur] == '0');
      assert(g[cur][nxt] == '1');
      int mask =
          (g[x][pre] - '0') << 2 | (g[x][cur] - '0') << 1 | (g[x][nxt] - '0');
      if ((~mask & 4) || mask == 6) { // 0?? or 110
        loop.emplace_back(x);
      } else if ((mask & 1) || mask == 4) { // ??1 or 100
        loop.insert(loop.begin() + 1, x);
      } else {
        assert(0);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    int a = loop[(i + n - 1) % n];
    int b = loop[i];
    int c = loop[(i + 1) % n];
    if (g[a][b] == '1' && g[b][c] == '0') {
      std::rotate(loop.begin(), loop.begin() + i, loop.end());
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d%c", loop[i] + 1, " \n"[i + 1 == n]);
  }
}

int main() {
  while (~scanf("%d\n", &n)) {
    work();
  }
}