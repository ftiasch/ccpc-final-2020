#include "testlib.h"

struct Gen {
  Gen(int n_) : n(n_), used_once(n) {}

  void gen(int used) {
    if (static_cast<int>(seq.size()) < 2 * n) {
      if (used < n) {
        used_once[used] = true;
        seq.push_back(used);
        gen(used + 1);
        seq.pop_back();
        used_once[used] = false;
      }
      for (int i = 0; i < n; ++i) {
        if (used_once[i]) {
          used_once[i] = false;
          seq.push_back(i);
          gen(used);
          seq.pop_back();
          used_once[i] = true;
        }
      }
    } else {
      for (int two = 0; two <= n; ++two) {
        int one = 2 * (n - two);
        for (int zero = 0; zero <= 2; ++zero) {
          std::vector<std::vector<int>> stacks(two + one + zero);
          int count = 0;
          for (int i = 0; i < two + one; ++i) {
            stacks[i].push_back(seq[count++]);
            if (i < two) {
              stacks[i].push_back(seq[count++]);
            }
          }
          shuffle(stacks.begin(), stacks.end());
          printf("%d %d\n", n, static_cast<int>(stacks.size()));
          for (auto &&s : stacks) {
            printf("%d", static_cast<int>(s.size()));
            for (auto &&e : s) {
              printf(" %d", e + 1);
            }
            puts("");
          }
        }
      }
    }
  }

  int n;
  std::vector<bool> used_once;
  std::vector<int> seq;
};

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  Gen{n}.gen(0);
}
