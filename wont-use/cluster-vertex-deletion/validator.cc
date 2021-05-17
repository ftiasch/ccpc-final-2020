#include "testlib.h"

#include "./common.h"

#include <functional>
#include <set>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int sum_n = 0;
  while (!inf.eof()) {
    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1) / 2, "m");
    inf.readSpace();
    int k = inf.readInt(1, K, "k");
    inf.readEoln();
    ensure((sum_n += n) <= N);
    std::vector<std::vector<bool>> graph(n, std::vector<bool>(n));
    for (int i = 0; i < m; ++i) {
      int a = inf.readInt(1, n) - 1;
      inf.readSpace();
      int b = inf.readInt(1, n) - 1;
      inf.readEoln();
      ensuref(a != b, "self loop");
      ensuref(!graph[a][b] && !graph[b][a], "redundant edge");
      graph[a][b] = graph[b][a] = true;
    }
  }
  inf.readEof();
  return 0;
}
