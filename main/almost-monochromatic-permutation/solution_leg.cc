#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define rep(i, n) for (int i = 1; i <= n; ++i)
const int N = 2005;
int n;
char s[N][N];
int q[N * 6], l, r;
int main() {
  while (~scanf("%d", &n)) {
    l = 3 * N, r = 3 * N - 1;
    rep(i, n) scanf("%s", s[i] + 1);
    rep(i, n) {
      if (i <= 2) {
        q[++r] = i;
        continue;
      }
      if (s[q[l]][i] == '1') {
        if (s[q[r]][i] == '1') {
          q[--l] = i;
          q[--l] = q[r];
          --r;
        } else {
          q[--l] = i;
        }
      } else {
        if (s[q[l + 1]][i] == '1') {
          q[++r] = q[l];
          q[l] = i;
        } else {
          q[++r] = q[l];
          q[++r] = i;
          ++l;
        }
      }
    }
    for (int i = l; i <= r; ++i)
      printf("%d%c", q[i], " \n"[i == r]);

    // for(int i=l;i<r;++i)printf("%c",s[q[i]][q[i+1]]);
    // puts("");
  }
  return 0;
}
