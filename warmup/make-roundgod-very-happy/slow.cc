#include <cstdio>
#include <cstring>

const int N = 1000000 + 1;

int a[N], stack[N];

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    a[0] = n + 1;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
    }
    int top = 0;
    stack[0] = 0;
    for (int i = 1; i <= n; ++i) {
      while (a[stack[top]] <= a[i]) {
        top--;
      }
      stack[++top] = i;
      int result = 0;
      for (int k = 0; k < top; ++k) {
        int l = stack[k];
        int r = stack[k + 1];
        // j in [l, r)
        int maximum = a[r];
        int bound = m - maximum + i;
        if (bound < l) {
          result += r - l;
        } else if (bound < r) {
          result += r - bound;
        }
      }
      printf("%d%c", result, " \n"[i == n]);
    }
  }
}