#include <cstdio>
#include <vector>
using namespace std;

int n, m;

vector<vector<int>> s;
vector<vector<pair<int, int>>> pos;
vector<pair<int, int>> ans;
vector<int> empty;

void move(int i, int j) {
  int c = s[i].back();
  s[j].push_back(c);
  s[i].pop_back();
  if (s[i].size() == 0) {
    empty.push_back(i);
  }
  int id = i == pos[c][1].second ? 1 : 0;
  pos[c][id].first = s[j].size() - 1;
  pos[c][id].second = j;
  ans.push_back(make_pair(i + 1, j + 1));
}

bool solve_chain(int start) {
  int ci = start, ch = 0;
  while (true) {
    int cc = s[ci][ch], id = ci == pos[cc][1].second ? 1 : 0,
        chp = pos[cc][1 - id].first, cip = pos[cc][1 - id].second;
    if (s[cip].size() == 1) {
      if (s[ci].size() == 1) {
        move(ci, cip);
        return true;
      } else {
        return solve_chain(cip);
      }
    } else {
      if (s[ci].size() == 1 && chp == 1) {
        move(cip, ci);
      }
      if (ch == 0 || chp == 0) {
        ci = cip;
        ch = 1 - chp;
      } else {
        if (empty.size() == 0) {
          return false;
        } else {
          int tmp = empty.back();
          empty.pop_back();
          move(ci, tmp);
          solve_chain(ci);
          return solve_chain(tmp);
        }
      }
    }
  }
}

int main() {
  while (scanf("%d%d", &n, &m) != -1) {
    s.resize(m);
    for (int i = 0; i < m; ++i) {
      s[i].clear();
    }
    pos.resize(n);
    for (int i = 0; i < n; ++i) {
      pos[i].clear();
    }
    empty.clear();
    ans.clear();
    for (int i = 0; i < m; ++i) {
      int sz;
      scanf("%d", &sz);
      if (sz == 0) {
        empty.push_back(i);
      }
      for (int j = 0; j < sz; ++j) {
        int c;
        scanf("%d", &c);
        --c;
        s[i].push_back(c);
        pos[c].push_back(make_pair(j, i));
      }
    }
    for (int r = 0; r < 2; ++r) {
      for (int i = 0; i < m; ++i) {
        if (s[i].size() == 1) {
          solve_chain(i);
        }
      }
    }
    bool valid = true;
    for (int r = 0; r < 2; ++r) {
      for (int i = 0; i < n; ++i) {
        if ((r == 0 && pos[i][0].first == 1 && pos[i][1].first == 1) ||
            (r == 1 && pos[i][0].second != pos[i][1].second)) {
          if (empty.size() > 0) {
            int ti = pos[i][0].second, tmp = empty.back();
            empty.pop_back();
            move(ti, tmp);
            solve_chain(ti);
          } else {
            valid = false;
          }
        }
      }
    }
    if (!valid) {
      printf("-1\n");
    } else {
      printf("%d\n", (int)ans.size());
      for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
      }
    }
  }
}
