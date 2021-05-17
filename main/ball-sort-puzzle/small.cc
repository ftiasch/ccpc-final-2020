#include "testlib.h"

using Stacks = std::vector<std::vector<int>>;

void output(int n, const Stacks &s, int empties) {
  auto ball_order = rnd.perm(n, 1);
  auto stack_order = rnd.perm(static_cast<int>(s.size()) + empties);
  printf("%d %d\n", n, static_cast<int>(stack_order.size()));
  for (auto &&sid : stack_order) {
    if (sid >= static_cast<int>(s.size())) {
      puts("0");
    } else {
      printf("%d", static_cast<int>(s[sid].size()));
      for (auto &&bid : s[sid]) {
        printf(" %d", ball_order[bid]);
      }
      puts("");
    }
  }
}

void generate1(int n, Stacks &s, std::vector<bool> &used_once, int used) {
  int count1 = 0;
  for (int i = 0; i < n; ++i) {
    count1 += used_once[i];
  }
  if (!count1 && used == n) {
    output(n, s, 0);
    output(n, s, 1);
    output(n, s, 2);
  }
  for (int bot_idx = -1, bot; bot_idx < n; ++bot_idx) {
    if ((bot_idx == -1 && used < n) || (~bot_idx && used_once[bot_idx])) {
      if (~bot_idx) {
        used_once[bot = bot_idx] = false;
      } else {
        used_once[bot = used++] = true;
      }
      s.push_back({bot});
      generate1(n, s, used_once, used);
      s.pop_back();
      if (~bot_idx) {
        used_once[bot_idx] = true;
      } else {
        used_once[bot] = false;
        used--;
      }
    }
  }
}

void generate2(int n, Stacks &s, std::vector<bool> &used_once, int used) {
  generate1(n, s, used_once, used);
  for (int bot_idx = -1, bot; bot_idx < n; ++bot_idx) {
    if ((bot_idx == -1 && used < n) || (~bot_idx && used_once[bot_idx])) {
      if (~bot_idx) {
        used_once[bot = bot_idx] = false;
      } else {
        used_once[bot = used++] = true;
      }
      for (int top_idx = -1, top; top_idx < n; ++top_idx) {
        if ((top_idx == -1 && used < n) || (~top_idx && used_once[top_idx])) {
          if (~top_idx) {
            used_once[top = top_idx] = false;
          } else {
            used_once[top = used++] = true;
          }
          s.push_back({bot, top});
          generate2(n, s, used_once, used);
          s.pop_back();
          if (~top_idx) {
            used_once[top_idx] = true;
          } else {
            used_once[top] = false;
            used--;
          }
        }
      }
      if (~bot_idx) {
        used_once[bot_idx] = true;
      } else {
        used_once[bot] = false;
        used--;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  const int n = opt<int>("n");
  Stacks s;
  std::vector<bool> used_once(n);
  generate2(n, s, used_once, 0);
}
