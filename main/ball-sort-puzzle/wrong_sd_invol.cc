#include <bits/stdc++.h>

const int N = 200005;

int n, m;

std::vector<int> stack[N];
std::vector<std::pair<int, int>> pos[N];
std::vector<std::pair<int, int>> res;
std::set<int> singles, empties;

void move(int a, int b) {
  // from a to b
  assert(!stack[a].empty());
  int x = stack[a].back();
  assert(stack[b].empty() || stack[b].back() == x);
  assert(stack[b].size() < 2);

  stack[a].pop_back();
  std::pair<int, int> p = {a, stack[a].size()};
  int id = pos[x][1] == p;
  pos[x][id] = {b, stack[b].size()};
  stack[b].push_back(x);
  res.emplace_back(a, b);

  if (stack[a].size() == 0) {
    singles.erase(a);
    empties.insert(a);
  }
  if (stack[a].size() == 1) {
    singles.insert(a);
  }
  if (stack[b].size() == 1) {
    empties.erase(b);
    singles.insert(b);
  }
  if (stack[b].size() == 2) {
    singles.erase(b);
  }
}

void print() {
  puts("====");
  for (int i = 0; i < m; ++i) {
    printf("%d ", stack[i].size());
    for (auto &x : stack[i]) {
      printf("%d ", x);
    }
    puts("");
  }
  printf("Singles: ");
  for (auto &x : singles) {
    printf("%d ", x);
  }
  puts("");
  printf("Empties: ");
  for (auto &x : empties) {
    printf("%d ", x);
  }
  puts("");
}

void single(int a);

bool possible_to_pop(int a) {
  assert(stack[a].size() == 2);

  int x = stack[a].back();
  int id = pos[x][1] == std::make_pair(a, 1);
  int b = pos[x][id ^ 1].first;
  int j = pos[x][id ^ 1].second;

  if (stack[b].size() == 1) {
    move(a, b);
    return true;
  } else {
    if (j == 1) {
      if (empties.empty()) {
        return false;
      }
      int e = *empties.begin();
      move(a, e);
      move(b, e);
      single(b);
      return true;
    } else {
      if (possible_to_pop(b)) {
        move(a, b);
        return true;
      }
      return false;
    }
  }
}

void single(int a) {
  assert(stack[a].size() == 1);
  int x = stack[a].back();
  int id = pos[x][1] == std::make_pair(a, 0);

  int b = pos[x][id ^ 1].first;
  int j = pos[x][id ^ 1].second;

  if (stack[b].back() == x) {
    move(b, a);
    if (stack[b].size() == 1) {
      single(b);
    }
  } else {
    assert(stack[b].size() == 2);
    assert(j == 0);
    if (possible_to_pop(b)) {
      move(b, a);
    }
  }
}

void work() {
  for (int i = 1; i <= n; ++i) {
    pos[i].clear();
  }
  singles.clear();
  empties.clear();
  res.clear();
  for (int i = 0; i < m; ++i) {
    int k;
    scanf("%d", &k);
    stack[i].resize(k);
    for (int j = 0; j < k; ++j) {
      scanf("%d", &stack[i][j]);
      pos[stack[i][j]].emplace_back(i, j);
    }
    if (k == 0) {
      empties.insert(i);
    }
    if (k == 1) {
      singles.insert(i);
    }
  }
  // printf("Test case:\n");
  // printf("%d %d\n", n , m);
  // print();

  for (int aa = 0; aa < m + m; ++aa) {
    int a = aa % m;
    if (stack[a].size() != 1) {
      continue;
    }
    single(a);
  }

  if (!singles.empty()) {
    puts("-1");
    return;
  }

  // 12 23 13 .. loop
  for (int i = 1; i <= n; ++i) {
    if (pos[i][0].second == 1 && pos[i][1].second == 1) {
      if (empties.empty()) {
        puts("-1");
        return;
      }
      int e = *empties.begin();
      move(pos[i][0].first, e);
      single(e);
      if (stack[pos[i][0].first].size() == 1) {
        single(pos[i][0].first);
      }
    }
  }

  // 12 23 31 .. loop
  for (int i = 0; i < m; ++i) {
    if (stack[i].size() == 2 && stack[i][0] != stack[i][1]) {
      if (empties.empty()) {
        puts("-1");
        return;
      }
      int e = *empties.begin();
      move(i, e);
      single(e);
      if (stack[i].size() == 1) {
        single(i);
      }
    }
  }
  // print();
  assert(singles.empty());

  printf("%d\n", res.size());
  for (int i = 0; i < res.size(); ++i) {
    printf("%d %d\n", res[i].first + 1, res[i].second + 1);
  }
}

int main() {
  while (~scanf("%d%d", &n, &m)) {
    work();
  }
}

//  for f in tests/???; do cat $f | time ./a | ./check.exe $f $f.a; done