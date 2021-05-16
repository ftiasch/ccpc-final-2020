#include <bits/stdc++.h>

#define SIZE(v) (static_cast<int>((v).size()))

using State = std::vector<std::vector<int>>;

State normalize(State s) {
  std::sort(s.begin(), s.end());
  return s;
}

bool is_sorted(const State &s) {
  for (int i = 0; i < SIZE(s); ++i) {
    if (SIZE(s[i]) == 1) {
      return false;
    }
    if (SIZE(s[i]) == 2 && s[i][0] != s[i][1]) {
      return false;
    }
  }
  return true;
}

bool work(State &&s0) {
  std::vector<State> queue{s0};
  std::vector<std::tuple<int, int, int>> from{{-1, -1, -1}};
  std::set<State> states{normalize(s0)};
  int head = 0;
  while (head < SIZE(queue)) {
    int index = head++;
    State s = queue[index];
    if (is_sorted(s)) {
      std::vector<std::pair<int, int>> moves;
      while (index) {
        int last_index, src, dst;
        std::tie(last_index, src, dst) = from[index];
        moves.emplace_back(src, dst);
        index = last_index;
      }
      printf("%d\n", SIZE(moves));
      for (int i = SIZE(moves); i--;) {
        printf("%d %d\n", moves[i].first + 1, moves[i].second + 1);
      }
      return true;
    }
    for (int src = 0; src < SIZE(s); ++src) {
      if (SIZE(s[src]) > 0) {
        for (int dst = 0; dst < SIZE(s); ++dst) {
          if (dst != src &&
              (SIZE(s[dst]) == 0 ||
               SIZE(s[dst]) == 1 && s[src].back() == s[dst].back())) {
            auto new_state = s;
            new_state[dst].push_back(new_state[src].back());
            new_state[src].pop_back();
            if (states.insert(normalize(new_state)).second) {
              queue.push_back(new_state);
              from.emplace_back(index, src, dst);
            }
          }
        }
      }
    }
  }
  return false;
}

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    State s(m);
    for (int i = 0, size, ball; i < m; ++i) {
      scanf("%d", &size);
      while (size--) {
        scanf("%d", &ball);
        s[i].push_back(ball);
      }
    }
    if (!work(std::move(s))) {
      puts("-1");
    }
  }
}
