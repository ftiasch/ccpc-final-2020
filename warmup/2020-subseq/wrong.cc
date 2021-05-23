#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<char> s(n + 1);
    scanf("%s", s.data());
    int result = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '2' && (~result & 1)) {
        result++;
      }
      if (s[i] == '0' && (result & 1)) {
        result++;
      }
    }
    printf("%d\n", result >> 2);
  }
}
