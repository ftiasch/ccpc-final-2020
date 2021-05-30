#include "testlib.h"
#include <algorithm>
#include <vector>

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  int cas = 0;
  while (!inf.eof()) {
    ++cas;
    int n = inf.readInt();
    inf.readEoln();
    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
      s[i] = inf.readToken();
      inf.readEoln();
    }
    bool all_same = true;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j)
          continue;
        if (s[i][j] != s[0][1])
          all_same = false;
      }
    }
    int p0 = ouf.readInt();
    if (p0 == -1) {
      quitf(_wa, "case #%d: user does not find a solution", cas);
    }
    if (p0 < 1 || p0 > n) {
      quitf(_wa, "case #%d: p[1] out of bound", cas);
    }
    std::vector<int> p = {p0 - 1};
    for (int i = 1; i < n; ++i) {
      p.push_back(ouf.readInt(1, n) - 1);
    }
    std::vector<bool> mark(n);
    for (int i = 0; i < n; ++i) {
      if (mark[p[i]]) {
        quitf(_wa, "case #%d: not a permutation", cas);
      }
      mark[p[i]] = true;
    }
    int cnt = 0;
    for (int i = 1; i < n; ++i) {
      cnt += s[p[i - 1]][p[i]] != s[p[i]][p[(i + 1) % n]];
    }
    if (cnt > 1)
      quitf(_wa, "case #%d: found %d indices", cas, cnt);
  }
  quitf(_ok, "%d cases.", cas);
  return 0;
}
