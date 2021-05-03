#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int size = opt<int>("size");
  int count = opt<int>("count");
  while (count--) {
    std::vector<std::pair<int, int>> points{{0, 0}};
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (i || j) {
          if (rnd.next(0, 1)) {
            points.emplace_back(i, j);
          }
        }
      }
    }
    shuffle(points.begin(), points.end());
    printf("%d\n", static_cast<int>(points.size()));
    for (auto &&p : points) {
      printf("%d %d\n", p.first, p.second);
    }
  }
}
