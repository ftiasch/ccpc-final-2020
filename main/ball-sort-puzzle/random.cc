#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int n = opt<int>("n");
  while (T--) {
    const int m = rnd.next(n + 2, opt<int>("maxm"));
    std::vector<int> ball_order(n << 1);
    for (int i = 0; i < n << 1; ++i) {
      ball_order[i] = (i >> 1) + 1;
    }
    shuffle(ball_order.begin(), ball_order.end());
    std::vector<int> stack_order;
    for (int i = 0; i < (m - 2) << 1; ++i) {
      stack_order.push_back(i >> 1);
    }
    shuffle(stack_order.begin(), stack_order.end());
    std::vector<std::vector<int>> s(m);
    for (int i = 0; i < n << 1; ++i) {
      s[stack_order[i]].emplace_back(ball_order[i]);
    }
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
      printf("%d", static_cast<int>(s[i].size()));
      for (int j = 0; j < static_cast<int>(s[i].size()); ++j) {
        printf(" %d", s[i][j]);
      }
      puts("");
    }
  }
}
