#include "testlib.h"

int main() {
  registerValidation();
  int sum_n = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
      points[i].first = inf.readInt(0, 1000000000, format("x[%d]", i));
      inf.readSpace();
      points[i].second = inf.readInt(0, 1000000000, format("y[%d]", i));
      inf.readEoln();
    }
    std::sort(points.begin(), points.end());
    ensuref(std::unique(points.begin(), points.end()) == points.end(),
            "points are not distcint.");
    ensuref((sum_n += n) <= 100000, "sum of n > 10 ** 5");
  }
  inf.readEof();
}
