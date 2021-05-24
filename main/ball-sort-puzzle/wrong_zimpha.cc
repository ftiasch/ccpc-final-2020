#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<std::vector<int>> pos(n);
    std::vector<std::vector<int>> stacks(m);
    for (int i = 0, k; i < m; ++i) {
      scanf("%d", &k);
      stacks[i].resize(k);
      for (int j = 0; j < k; ++j) {
        scanf("%d", &stacks[i][j]);
        --stacks[i][j];
        pos[stacks[i][j]].push_back(i);
      }
    }
    bool valid = true;
    std::vector<std::pair<int, int>> moves;

    auto do_move = [&](int f, int t) {
      int u = stacks[f].back();
      stacks[f].pop_back();
      stacks[t].push_back(u);
      for (auto &x : pos[u]) {
        if (x == f)
          x = t;
      }
      moves.emplace_back(f + 1, t + 1);
    };

    auto find_chain_with_empty = [&](int p, int &w) {
      for (; !stacks[p].empty();) {
        int u = stacks[p][0];
        int q = pos[u][0] + pos[u][1] - p;
        if (stacks[q].back() == u) {
          do_move(q, p);
          p = q;
        } else if (w != -1) {
          do_move(q, w);
          do_move(q, p);
          p = w;
          w = q;
        } else {
          break;
        }
      }
      return p;
    };

    auto solve_two_empty_stacks = [&](int w1, int w2) {
      for (int i = 0; i < m; ++i)
        if (stacks[i].size() != 0) {
          if (stacks[i].size() == 2) {
            if (stacks[i][0] == stacks[i][1]) {
              continue;
            }
            do_move(i, w2);
          }
          int p = find_chain_with_empty(i, w1);
          assert(stacks[p].empty());
          if (!stacks[w2].empty()) {
            find_chain_with_empty(w2, w1);
            w2 = p;
          }
        }
    };

    // solve chain
    for (int i = 0, w = -1; i < m; ++i) {
      if (stacks[i].size() == 1) {
        find_chain_with_empty(i, w);
      }
    }
    std::vector<int> empties;
    for (int i = 0; i < m; ++i) {
      if (stacks[i].size() == 0) {
        empties.push_back(i);
      }
    }
    if (empties.size() > 1) { // solve two stacks
      solve_two_empty_stacks(empties[0], empties[1]);
    } else if (empties.size() == 1) { // solve one stack
      int w1 = empties[0], w2 = -1;
      for (int i = 0; i < m; ++i) {
        if (stacks[i].size() != 1)
          continue;
        w2 = find_chain_with_empty(i, w1);
        solve_two_empty_stacks(w1, w2);
        break;
      }
      if (w2 == -1) { // only one empty stack and all stacks are full
        for (int i = 0; i < n && w1 != -1 && valid; ++i) {
          int a = pos[i][0], b = pos[i][1];
          if (a != b && stacks[a].back() == stacks[b].back()) {
            do_move(a, w1);
            do_move(b, w1);
            w1 = -1;
            int p = find_chain_with_empty(a, w1);
            int q = find_chain_with_empty(b, w1);
            if (stacks[p].empty())
              w1 = p;
            else if (stacks[q].empty())
              w1 = q;
            else if (stacks[p][0] == stacks[q][0]) {
              do_move(p, q);
              w1 = p;
            } else {
              valid = false;
            }
          }
        }
        for (int i = 0; i < n && w1 != -1 && valid; ++i) {
          int a = pos[i][0], b = pos[i][1];
          if (a != b && stacks[a].back() != stacks[b].back()) {
            do_move(a, w1);
            w1 = -1;
            w1 = find_chain_with_empty(a, w1);
            assert(stacks[w1].empty());
          }
        }
      }
    } else {
      for (int i = 0; i < n; ++i) {
        int a = pos[i][0], b = pos[i][1];
        valid &= a == b;
      }
    }
    if (!valid)
      puts("-1");
    else {
      printf("%d\n", (int)moves.size());
      for (auto &e : moves) {
        printf("%d %d\n", e.first, e.second);
      }
    }
  }
  return 0;
}
