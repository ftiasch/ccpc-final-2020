#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  const int maxm = opt<int>("maxm");
  while (T--) {
    const int n = has_opt("n") ? opt<int>("n") : rnd.next(1, opt<int>("maxn"));
    std::vector<int> seq(2 * n);
    int used = 0;
    std::vector<int> used_once;
    for (int i = 0; i < 2 * n; ++i) {
      int choice =
          rnd.next(0, static_cast<int>(used_once.size()) + (used < n) - 1);
      if (choice < static_cast<int>(used_once.size())) {
        seq[i] = used_once[choice];
        used_once.erase(used_once.begin() + choice);
      } else {
        seq[i] = used++;
        used_once.push_back(seq[i]);
      }
    }
    int two = rnd.next(std::max(2 * n - maxm, 0), n);
    int one = 2 * n - 2 * two;
    int zero = rnd.next(0, std::min(maxm - two - one, 2));
    auto ball_map = rnd.perm(n, 1);
    std::vector<std::vector<int>> stacks(two + one + zero);
    for (int i = 0, j = 0; i < two + one; ++i) {
      stacks[i].push_back(ball_map[seq[j++]]);
      if (i < two) {
        stacks[i].push_back(ball_map[seq[j++]]);
      }
    }
    shuffle(stacks.begin(), stacks.end());
    printf("%d %d\n", n, static_cast<int>(stacks.size()));
    for (auto &&s : stacks) {
      printf("%d", static_cast<int>(s.size()));
      for (auto &&b : s) {
        printf(" %d", b);
      }
      puts("");
    }
  }
}
