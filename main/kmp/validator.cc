#include "testlib.h"
#include <functional>
#include <set>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  int snm = 0;
  while (!inf.eof()) {
    std::string s = inf.readToken("[a-z]{1,1000000}", "s");
    inf.readEoln();
    std::string t = inf.readToken("[a-z]{1,1000000}", "t");
    inf.readEoln();
    snm += std::max(s.size(), t.size());
    ensuref(snm <= 1000000, "sum of max(|s|, |t|) <= 1000000");
  }
  inf.readEof();
  return 0;
}
