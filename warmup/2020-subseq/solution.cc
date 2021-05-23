#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

bool check(int n, const std::vector<char> &s, int k) {
  std::vector<bool> used(n);
  std::vector<int> rights;
  {
    std::queue<int> queue;
    for (int i = 0; i < n && static_cast<int>(rights.size()) < k; ++i) {
      if (s[i] == '2') {
        queue.push(i);
      }
      if (s[i] == '0' && !queue.empty()) {
        int j = queue.front();
        queue.pop();
        used[j] = used[i] = true;
        rights.push_back(i);
      }
    }
  }
  int zeros = 0;
  int count = k;
  for (int i = n; i-- && count;) {
    if (!used[i]) {
      if (s[i] == '0') {
        zeros++;
      }
      if (s[i] == '2' && zeros) {
        zeros--;
        if (rights[--count] >= i) {
          return false;
        }
      }
    }
  }
  return count == 0;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    int low = 0;
    int high = n >> 2;
    while (low < high) {
      int middle = (low + high + 1) >> 1;
      if (check(n, s, middle)) {
        low = middle;
      } else {
        high = middle - 1;
      }
    }
    printf("%d\n", low);
  }
}
