#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define rep(i, n) for (int i = 1; i <= n; ++i)
int n, m, now;
pair<int, int> a[210000];
set<pair<int, int>> dic;
vector<int> st[210000], ed[210000];
int cur[210000];
int dist(int x, int y, int d) {
  int d1 = 2147483647;
  if (!(x <= d && d < y))
    d1 = y - x;
  int d2 = 2147483647;
  if (x <= d && d < y)
    d2 = n - (y - x);
  return min(d1, d2);
}
void update(int x, int d) {
  dic.erase(mp(-cur[x], x));
  cur[x] = dist(a[x].first, a[x].second, d);
  dic.insert(mp(-cur[x], x));
  now = dic.begin()->first;
}
void print(int ti) {
  cout << ti << ":" << endl;
  for (int i = 1; i <= m; i++)
    cout << cur[i] << " ";
  puts("");
  cout << now << endl;
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    dic.clear();
    for (int i = 1; i <= n; i++)
      st[i].clear(), ed[i].clear();
    for (int i = 1; i <= m; i++) {
      scanf("%d%d", &a[i].first, &a[i].second);
      if (a[i].first > a[i].second)
        swap(a[i].first, a[i].second);
      st[a[i].first].pb(i);
      st[a[i].second].pb(i);
    }
    int ans = -2147483647;
    for (int i = 1; i <= m; i++)
      update(i, 1);
    ans = max(ans, now);
    // print(1);
    for (int i = 2; i <= n; i++) {
      for (auto p : st[i])
        update(p, i);
      for (auto p : ed[i])
        update(p, i);
      // print(2);
      ans = max(ans, now);
    }
    printf("%d\n", -ans);
  }
  return 0;
}
