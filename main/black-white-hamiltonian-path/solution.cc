#include <cstdio>
#include <cstdlib>
#include <vector>

const int N = 2000 + 10;

char s[N][N];

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i < n; ++i)
      scanf("%s", s[i]);
    std::vector<int> path = {0, 1, 2};
    std::vector<char> col = {s[0][1], s[1][2], s[2][0]};
    for (int i = 3; i < n; ++i) {
      int x = 0, y = 1, z = 2;
      for (size_t j = 0; j < path.size(); ++j) {
        if (col[j] != col[(j + 1) % path.size()]) {
          x = j;
          y = (j + 1) % path.size();
          z = (j + 2) % path.size();
          break;
        }
      }
      char t = s[i][path[y]];
      if (t == col[x]) {
        path.insert(path.begin() + z, i);
        col[y] = col[x];
        col.insert(col.begin() + z, s[i][path[z + 1]]);
      } else {
        path.insert(path.begin() + y, i);
        col.insert(col.begin() + y, t);
        col[x] = s[i][path[(y - 1 + path.size()) % path.size()]];
      }
    }
    int x = 0;
    for (size_t j = 0; j < path.size(); ++j) {
      if (col[j] != col[(j + 1) % path.size()]) {
        x = j;
        break;
      }
    }
    for (int i = 1; i <= n; ++i) {
      printf("%d", path[(x + i) % n] + 1);
      if (i == n)
        puts("");
      else
        putchar(' ');
    }
  }
  return 0;
}
