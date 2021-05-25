#include "testlib.h"

int main() {
  registerValidation();
  int sum_length = 0;
  while (!inf.eof()) {
    std::string s = inf.readToken("[0-9]{1,5000}");
    inf.readEoln();
    ensure(s[0] != '0');
    ensure((sum_length += s.length()) <= 50000);
  }
  inf.readEof();
}
