#include "testlib.h"

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  int cases = 0;
  double max_ratio = 0.;
  while (!inf.seekEof()) {
    ++cases;
    int n = inf.readInt();
    int m = inf.readInt();
    std::vector<std::vector<int>> s(m);
    for (int i = 0; i < m; ++i) {
      int size = inf.readInt();
      while (size--) {
        s[i].push_back(inf.readInt());
      }
    }
    int ans_cnt = ans.readInt();
    if (~ans_cnt) {
      for (int _ = 0; _ < ans_cnt; ++_) {
        ans.readInt();
        ans.readInt();
      }
    }
    int out_cnt = ouf.readInt(-1, 2 * n);
    if (out_cnt != -1) {
      if (out_cnt > 3 * n / 2) {
        quitf(_wa, "Too many moves [Case %d]", cases);
      }
      for (int i = 0; i < out_cnt; ++i) {
        int src = ouf.readInt(1, m) - 1;
        int dst = ouf.readInt(1, m) - 1;
        if (s[src].empty()) {
          quitf(_wa, "Empty source stack [Case %d, Move %d]", cases, i + 1);
        }
        if (static_cast<int>(s[dst].size()) == 2) {
          quitf(_wa, "Full destination stack [Case %d, Move %d]", cases, i + 1);
        }
        if (src == dst) {
          quitf(_wa, "src == dst [Case %d, Move %d]", cases, i + 1);
        }
        if (static_cast<int>(s[dst].size()) == 1 &&
            s[src].back() != s[dst].back()) {
          quitf(_wa, "src.top() != dst.top() [Case %d, Move %d]", cases, i + 1);
        }
        s[dst].push_back(s[src].back());
        s[src].pop_back();
      }
      for (int i = 0; i < m; ++i) {
        if (static_cast<int>(s[i].size()) == 1) {
          quitf(_wa, "size == 1 [Case %d, Stack %d]", cases, i + 1);
        } else if (static_cast<int>(s[i].size()) == 2 && s[i][0] != s[i][1]) {
          quitf(_wa, "stack[0] != stack[1] [Case %d, Stack %d]", cases, i + 1);
        }
      }
      max_ratio = std::max(max_ratio, 1.0 * out_cnt / n);
    } else if (~ans_cnt) {
      quitf(_wa, "Should find solution [Case %d]", cases);
    }
  }
  quitf(_ok, "%d cases passed. max #moves/#balls = %.9f", cases, max_ratio);
}
