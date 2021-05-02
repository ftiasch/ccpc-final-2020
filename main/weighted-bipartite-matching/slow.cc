#include <cstdio>
#include <algorithm>

static const int N = 1000;

struct KM {
  typedef int cost_t;
  static const cost_t inf = 1e9;
  cost_t lx[N], ly[N], sl[N];
  int px[N],py[N],sy[N],fa[N],n;
  void aug(int v) {
    sy[v]=py[v]; if (px[sy[v]]!=-2) aug(px[sy[v]]);
  }
  bool find(int v, const cost_t w[][N]) {
    for (int i=0;i<n;++i) if (!~py[i]) {
      if (sl[i]>lx[v]+ly[i]-w[v][i]) {
        sl[i]=lx[v]+ly[i]-w[v][i]; fa[i] = v;
      }
      if (lx[v]+ly[i]==w[v][i]) {
        py[i]=v; if (!~sy[i]) {aug(i); return 1;}
        if (~px[sy[i]]) continue;
        px[sy[i]]=i; if (find(sy[i],w)) return 1;
      }
    }
    return 0;
  }
  cost_t gao(int _n, const cost_t w[][N], cost_t m=inf) {
    n=_n; std::fill(sy,sy+n,-1); std::fill(ly,ly+n,0);
    for (int i=0;i<n;++i) lx[i]=*std::max_element(w[i],w[i]+n);
    for (int i(0),flag;i<n;++i) {
      for (int j=0;j<n;++j)px[j]=py[j]=-1,sl[j]=inf;
      px[i]=-2; if (find(i,w)) continue;
      for (flag=0,m=inf; !flag; m=inf) {
        for (int j=0;j<n;++j) if (!~py[j]) m=std::min(m,sl[j]);
        for (int j=0;j<n;++j) {
          if (~px[j]) lx[j]-=m;
          if (~py[j]) ly[j]+=m;
          else sl[j]-=m;
        }
        for (int j=0;j<n;++j) if (!~py[j]&&!sl[j]) {
          py[j]=fa[j]; if (!~sy[j]) {aug(j);flag=1;break;}
          px[sy[j]]=j; if (find(sy[j],w)) {flag=1;break;}
        }
      }
    }
    cost_t ret(0);
    for (int i=0;i<n;++i) ret+=w[sy[i]][i];
    return ret;
  }
} km;

int w[N][N], tw[N][N];

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &w[i][j]);
      }
    }
    int nn = std::max(n, m) - 1;
    for (int i = 0; i < nn; ++i) {
      for (int j = 0; j < nn; ++j) {
        tw[i][j] = 0;
      }
    }
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < m; ++v) {
        for (int i = 0, ni = 0; i < n; ++i) if (i != u) {
          for (int j = 0, nj = 0; j < m; ++j) if (j != v) {
            tw[ni][nj] = w[i][j];
            ++nj;
          }
          ++ni;
        }
        if (v) putchar(' ');
        printf("%d", km.gao(nn, tw));
      }
      puts("");
    }
  }
  return 0;
}
