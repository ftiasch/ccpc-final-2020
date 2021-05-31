#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= n; ++i)
#define pb push_back
#define mp make_pair
typedef long double ld;
using namespace std;
struct poi {
  int a[3];
  poi operator-(poi p) {
    poi tmp;
    tmp.a[0] = a[0] - p.a[0];
    tmp.a[1] = a[1] - p.a[1];
    tmp.a[2] = a[2] - p.a[2];
    return tmp;
  }
  poi operator*(poi p) {
    poi tmp;
    tmp.a[0] = a[1] * p.a[2] - a[2] * p.a[1],
    tmp.a[1] = a[2] * p.a[0] - a[0] * p.a[2],
    tmp.a[2] = a[0] * p.a[1] - a[1] * p.a[0];
    return tmp;
  }
  int operator%(poi p) { return a[0] * p.a[0] + a[1] * p.a[1] + a[2] * p.a[2]; }
  int scan() { return scanf("%d%d%d", a + 0, a + 1, a + 2); }
} p[4], u[3];
int main() {
  while (~p[0].scan()) {
    for (int i = 1; i < 4; ++i)
      p[i].scan();
    // rep(tim,100000){
    //	for(int i=0;i<4;++i)p[i].scan();
    for (int i = 0; i < 3; ++i) {
      if (p[0].a[i] > p[1].a[i])
        for (int j = 0; j < 4; ++j)
          p[j].a[i] *= -1;
      if (p[2].a[i] > p[3].a[i])
        swap(p[2].a[i], p[3].a[i]);
      p[2].a[i] = max(p[2].a[i], p[0].a[i]);
      p[3].a[i] = max(p[3].a[i], p[0].a[i]);
    }
    u[0] = u[1] = u[2] = p[0];
    for (int i = 0; i < 3; ++i)
      u[i].a[i] = p[1].a[i];
    ld ans = 0;
    int ini = (u[0] - p[0]) * (u[1] - p[0]) % (u[2] - p[0]);
    // printf("%d\n",ini);
    for (int mk = 0; mk < 8; ++mk) {
      poi tmp;
      int typ = 1;
      for (int i = 0; i < 3; ++i)
        if (mk & (1 << i))
          tmp.a[i] = p[3].a[i], typ *= -1;
        else
          tmp.a[i] = p[2].a[i];
      int c = (u[0] - tmp) * (u[1] - tmp) % (u[2] - tmp);
      // printf("%d\n",c);
      ans += (ld)typ * max(0.L, (ld)c * c * c / ini / ini);
    }
    ans /= 6;
    printf("%.15Lf\n", ans);
  }
  return 0;
}
