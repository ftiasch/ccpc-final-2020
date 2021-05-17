#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1000000 + 1;

int n, m, a[N], stack[N], result, delta, enter[N], leave[N];

template <int dir> void update(int k, int i) {
  int l = stack[k];
  int r = stack[k + 1];
  int b = m - a[r];
  if (b + i < l) {
    result += dir * (r - l);
    enter[std::min(l - b - 1, n)] += dir;
    leave[std::min(r - b - 1, n)] += dir;
  } else if (b + i < r) {
    result += dir * (r - (b + i));
    delta += dir;
    leave[std::min(r - b - 1, n)] += dir;
  }
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    a[0] = n + 1;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
    }
    memset(enter, 0, sizeof(*enter) * (n + 1));
    memset(leave, 0, sizeof(*leave) * (n + 1));
    int top = 0;
    stack[0] = 0;
    result = delta = 0;
    for (int i = 1; i <= n; ++i) {
      while (a[stack[top]] <= a[i]) {
        update<-1>(--top, i);
      }
      stack[++top] = i;
      update<1>(top - 1, i);
      printf("%d%c", result, " \n"[i == n]);
      result -= delta;
      delta += enter[i];
      delta -= leave[i];
    }
  }
}