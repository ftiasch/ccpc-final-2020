#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define rep(i, n) for (int i = 1; i <= n; ++i)
#define N 210000
struct node {
  int cnt[2], tag;
  long long sum[2];
} st[N * 4];
int n, q;
char s[N];
void flip(int t) {
  swap(st[t].cnt[0], st[t].cnt[1]);
  swap(st[t].sum[0], st[t].sum[1]);
}
void update(int t) {
  st[t].cnt[0] = st[2 * t].cnt[0] + st[2 * t + 1].cnt[0];
  st[t].cnt[1] = st[2 * t].cnt[1] + st[2 * t + 1].cnt[1];
  st[t].sum[0] = st[2 * t].sum[0] + st[2 * t + 1].sum[0];
  st[t].sum[1] = st[2 * t].sum[1] + st[2 * t + 1].sum[1];
}
void pushdown(int t) {
  if (!st[t].tag)
    return;
  st[t].tag = 0;

  st[2 * t].tag ^= 1;
  st[2 * t + 1].tag ^= 1;

  flip(2 * t);
  flip(2 * t + 1);
}
void build(int t, int l, int r) {
  st[t].cnt[0] = st[t].cnt[1] = 0;
  st[t].tag = 0;
  st[t].sum[0] = st[t].sum[1] = 0;
  if (l == r) {
    if (s[l] == '0')
      st[t].cnt[0]++;
    else
      st[t].cnt[1]++;
    if (s[l] == '0')
      st[t].sum[0] += l;
    else
      st[t].sum[1] += l;
    return;
  }
  int mid = (l + r) / 2;
  build(2 * t, l, mid);
  build(2 * t + 1, mid + 1, r);
  update(t);
}
void flip(int t, int l, int r, int a, int b) {
  if (a <= l && r <= b) {
    flip(t);
    st[t].tag ^= 1;
    return;
  }
  pushdown(t);
  int mid = (l + r) / 2;
  if (a <= mid)
    flip(2 * t, l, mid, a, b);
  if (b > mid)
    flip(2 * t + 1, mid + 1, r, a, b);
  update(t);
}
long long get(int t, int l, int r, int a, int b, int typ) {
  if (a > b)
    return 0;
  if (a <= l && r <= b)
    return st[t].sum[typ];
  pushdown(t);
  int mid = (l + r) / 2;
  long long ret = 0;
  if (a <= mid)
    ret = ret + get(2 * t, l, mid, a, b, typ);
  if (b > mid)
    ret = ret + get(2 * t + 1, mid + 1, r, a, b, typ);
  return ret;
}
int main() {
  while (~scanf("%d%d", &n, &q)) {
    scanf("%s", s + 1);
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      flip(1, 1, n, l, r);
      int k = st[1].cnt[1];
      if (k == 0) {
        puts("0");
        continue;
      }
      long long ans1 = 2ll * get(1, 1, n, k, n, 1);
      long long ans2 = 2ll * get(1, 1, n, 1, k - 1, 0);
      printf("%lld\n", ans1 - ans2 - k);
    }
  }
  return 0;
}
