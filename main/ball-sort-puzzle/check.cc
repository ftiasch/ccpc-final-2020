#include "testlib.h"

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  int cases = 0;
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
    int out_cnt = ouf.readInt();
    if (~out_cnt) {
      if (out_cnt > 2 * n) {
        quitf(_wa, "Too many moves [Case %d]", cases);
      }
      std::vector<std::pair<int, int>> moves;
      for (int i = 0; i < out_cnt; ++i) {
        int src = ouf.readInt();
        int dst = ouf.readInt();
        moves.emplace_back(src, dst);
      }
      for (int i = 0; i < out_cnt; ++i) {
        int src = moves[i].first - 1;
        int dst = moves[i].second - 1;
        if (src < 0 || src >= m) {
          quitf(_wa, "Invalid source [Case %d, Move %d]", cases, i + 1);
        } else if (dst < 0 || dst >= m) {
          quitf(_wa, "Invalid destination [Case %d, Move %d]", cases, i + 1);
        } else if (s[src].empty()) {
          quitf(_wa, "Empty source stack [Case %d, Move %d]", cases, i + 1);
        } else if (static_cast<int>(s[dst].size()) == 2) {
          quitf(_wa, "Full destination stack [Case %d, Move %d]", cases, i + 1);
        } else if (src == dst) {
          quitf(_wa, "src == dst [Case %d, Move %d]", cases, i + 1);
        } else if (static_cast<int>(s[dst].size()) == 1 &&
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
    } else if (~ans_cnt) {
      quitf(_wa, "Should find solution [Case %d]", cases);
    }
  }
  quitf(_ok, "%d cases passed.", cases);
}
