#include "testlib.h"

#include <bits/stdc++.h>

std::vector<int> gen_stack_sortable(int n) {
  int i = n;
  std::vector<int> seq, stack;
  while (static_cast<int>(seq.size()) < n) {
    if (rnd.next(0, 1)) {
      // pop
      if (i) {
        stack.push_back(--i);
      }
    } else {
      // push
      if (!stack.empty()) {
        seq.push_back(stack.back());
        stack.pop_back();
      }
    }
  }
  std::reverse(seq.begin(), seq.end());
  return seq;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  int n = opt<int>("n");
  int w = opt<int>("w");
  while (T--) {
    auto values = rnd.perm(n, 1);
    int m = rnd.wnext(1, n, w);
    std::sort(values.begin(), values.begin() + m);
    auto sortable = gen_stack_sortable(m);
    {
      std::vector<int> new_values(m);
      for (int i = 0; i < m; ++i) {
        new_values[i] = values[sortable[i]];
      }
      for (int i = 0; i < m; ++i) {
        values[i] = new_values[i];
      }
    }
    std::vector<int> order(n);
    std::fill(order.begin() + m, order.end(), 1);
    shuffle(order.begin(), order.end());
    int count[]{0, m};
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
      printf("%d%c", values[count[order[i]]++], " \n"[i + 1 == n]);
    }
  }
}
