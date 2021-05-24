#include "testlib.h"

static const int G = 5;
static const int P = 2017;

using B = std::bitset<P - 1>;

int main(int argc, char *argv[]) {
  std::vector<int> g(P - 1);
  g[0] = 1;
  for (int i = 1; i < P - 1; ++i) {
    g[i] = g[i - 1] * G % P;
  }
  registerGen(argc, argv, 1);
  int T = opt<int>("T");
  // const int n = opt<int>("n");
  const int minord = opt<int>("minord");
  const int maxord = opt<int>("maxord");
  while (T--) {
    int n;
    if (has_opt("n")) {
      n = opt<int>("n");
    } else {
      n = rnd.next(1, opt<int>("maxn"));
    }

    std::vector<int> a;
    a.reserve(n);

    B result;
    result.set(0);
    for (int i = 0; i < n; ++i) {
      int o = rnd.next(minord, maxord);
      a.push_back(g[o]);
      result ^= (result << o) | (result >> (P - 1 - o));
    }
    result.flip(0);

    std::vector<int> zeros, ones;
    for (int i = 0; i < P - 1; ++i) {
      if (result.test(i)) {
        ones.push_back(g[i]);
      } else {
        zeros.push_back(g[i]);
      }
    }
    int r = -1;
    if (zeros.empty()) {
      r = rnd.any(ones);
    } else if (ones.empty()) {
      r = rnd.any(zeros);
    } else if (rnd.next(0, 1)) {
      r = rnd.any(ones);
    } else {
      r = rnd.any(zeros);
    }

    printf("%d %d\n", n, r);
    for (int i = 0; i < n; ++i) {
      printf("%d%c", a[i], " \n"[i + 1 == n]);
    }
  }
}
