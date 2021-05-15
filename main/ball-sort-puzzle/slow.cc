#include <bits/stdc++.h>

using Stacks = std::vector<std::vector<int>>;

struct Solver {
  bool check(Stacks stacks) {
    bool ok = true;
    for (int i = 0; i < static_cast<int>(stacks.size()); ++i) {
      if (static_cast<int>(stacks[i].size()) == 1 ||
          (static_cast<int>(stacks[i].size()) == 2 &&
           stacks[i][0] != stacks[i][1])) {
        ok = false;
      }
    }
    if (ok) {
      return true;
    }
    std::sort(stacks.begin(), stacks.end());
    if (memory.count(stacks)) {
      return memory[stacks];
    }
    for (int i = 0; i < static_cast<int>(stacks.size()); ++i) {
      if (static_cast<int>(stacks[i].size()) == 1 ||
          (static_cast<int>(stacks[i].size()) == 2 &&
           stacks[i][0] != stacks[i][1])) {
        for (int j = 0; j < static_cast<int>(stacks.size()); ++j) {
          if (i != j &&
              (stacks[j].empty() || stacks[i].back() == stacks[j].back())) {
            auto new_stacks = stacks;
            new_stacks[j].push_back(stacks[i].back());
            new_stacks[i].pop_back();
            if (check(new_stacks)) {
              return memory[stacks] = true;
            }
          }
        }
      }
    }
    return memory[stacks] = false;
  }

};

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    Stacks stacks(m);
    for (int i = 0, size; i < m; ++i) {
      scanf("%d", &size);
      while (size--) {
        int elem;
        scanf("%d", &elem);
        stacks[i].push_back(elem);
      }
    }
    std::map<Stacks> memory;
    // Solver solver;
    puts(solver.check(stacks) ? "Yes" : "No");
  }
}
