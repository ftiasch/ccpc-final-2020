#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  int sum_m = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();
    inf.readToken(format("[bo]{%d}", n), "s");
    inf.readEoln();
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
      int a = inf.readInt(1, n, format("a[%d]", i + 1));
      inf.readSpace();
      int b = inf.readInt(1, n, format("b[%d]", i + 1));
      inf.readEoln();
      ensuref(a != b, "a self loop occurs");
      if (a > b) {
        std::swap(a, b);
      }
      edges.emplace_back(a, b);
    }
    std::sort(edges.begin(), edges.end());
    ensuref(std::unique(edges.begin(), edges.end()) == edges.end(),
            "duplicated edges");
    ensuref((sum_n += n) <= 200000, "sum of n exceeds");
    ensuref((sum_m += m) <= 200000, "sum of m exceeds");
  }
  inf.readEof();
}
