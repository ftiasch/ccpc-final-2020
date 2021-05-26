#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  while (T--) {
    const int n = has_opt("n") ? opt<int>("n") : rnd.next(2, opt<int>("maxn"));
    const int maxlen =
        has_opt("maxlen") ? std::min(n / 2, opt<int>("maxlen")) : n / 2;
    std::vector<std::pair<int, int>> intervals;
    for (int i = 0; i < n / 2; ++i) {
      int j = std::min(i + rnd.next(1, maxlen), n - 1);
      intervals.emplace_back(i, j);
    }
    for (int i = n / 2 + 1; i < n; ++i) {
      int j = std::max(i - rnd.next(1, maxlen), 0);
      intervals.emplace_back(i, j);
    }
    const int m = has_opt("m") ? opt<int>("m")
                               : rnd.next(static_cast<int>(intervals.size()),
                                          opt<int>("maxn"));
    while (static_cast<int>(intervals.size()) < m) {
      int len = rnd.next(0, maxlen);
      int i = rnd.next(len, n - 1);
      intervals.emplace_back(i, i + len);
    }
    shuffle(intervals.begin(), intervals.end());
    const int offset = rnd.next(0, n - 1);
    printf("%d %d\n", n, m);
    for (auto &&interval : intervals) {
      int a = interval.first;
      int b = interval.second;
      if (rnd.next(0, 1)) {
        std::swap(a, b);
      }
      printf("%d %d\n", (offset + a) % n + 1, (offset + b) % n + 1);
    }
  }
}
