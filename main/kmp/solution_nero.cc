#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

namespace {

template <int MOD> struct Integral {
  int v_ = 0;

  template <typename T>
  Integral(T v) : v_(norm(v)) { // Implicit conversion is allowed.
    static_assert(std::is_integral<T>::value, "input should be an integral.");
  }
  Integral() = default;
  ~Integral() = default;

  template <typename T> T norm(T v) const {
    if (std::is_same<long long, T>::value) {
      v %= MOD;
      if (v < 0)
        v += MOD;
    } else {
      if (v >= MOD)
        v -= MOD;
      if (v < 0)
        v += MOD;
      if (v >= MOD || v < 0) {
        v %= MOD;
        if (v < 0)
          v += MOD;
      }
    }
    return v;
  }

  int val() const { return v_; }
  Integral &operator+=(const Integral &rhs) {
    v_ += rhs.val();
    if (v_ >= MOD)
      v_ -= MOD;
    return *this;
  }
  Integral &operator-=(const Integral &rhs) {
    v_ += MOD - rhs.val();
    if (v_ >= MOD)
      v_ -= MOD;
    return *this;
  }
  Integral &operator*=(const Integral &rhs) {
    v_ = v_ * 1LL * rhs.val() % MOD;
    return *this;
  }
  Integral &operator/=(const Integral &rhs) {
    v_ = v_ * 1LL * rhs.inv().val() % MOD;
    return *this;
  }
  Integral operator+(const Integral &rhs) const {
    Integral ret = *this;
    return ret += rhs;
  }
  Integral operator-(const Integral &rhs) const {
    Integral ret = *this;
    return ret -= rhs;
  }
  Integral operator*(const Integral &rhs) const {
    Integral ret = *this;
    return ret *= rhs;
  }
  Integral operator/(const Integral &rhs) const {
    Integral ret = *this;
    return ret /= rhs;
  }
  bool operator==(const Integral &rhs) const { return val() == rhs.val(); }
  bool operator!=(const Integral &rhs) const { return !(*this == rhs); }
  const Integral operator-() const { return Integral(-val()); }
  const Integral &operator++() {
    v_ += 1;
    if (v_ >= MOD)
      v_ -= MOD;
    return *this;
  }
  const Integral operator++(int) {
    Integral ret = *this;
    ++(*this);
    return ret;
  }
  const Integral &operator--() {
    v_ += MOD - 1;
    if (v_ >= MOD)
      v_ -= MOD;
    return *this;
  }
  const Integral operator--(int) {
    Integral ret = *this;
    --(*this);
    return ret;
  }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for (; b; b >>= 1, a = a * a % MOD)
      if (b & 1)
        ret = ret * a % MOD;
    return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};

template <int MOD> std::string to_string(const Integral<MOD> &v) {
  return std::string("{") + std::to_string(v.val()) + "}";
}

template <int MOD, bool kAllowBruteForce = false> struct Binomial {
  std::vector<Integral<MOD>> factor, inv_factor;

  explicit Binomial(int n = 0) : factor(n + 1), inv_factor(n + 1) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i)
      factor[i] = factor[i - 1] * i;
    inv_factor[n] = factor[n].inv();
    for (int i = n; i >= 1; --i)
      inv_factor[i - 1] = inv_factor[i] * i;
  }
  ~Binomial() = default;

  template <typename T> Integral<MOD> operator()(T a, T b) const {
    if (a < b || b < 0)
      return 0;
    if (a < factor.size())
      return factor[a] * inv_factor[b] * inv_factor[a - b];
    if (!kAllowBruteForce) {
      throw std::out_of_range("Binomial");
    } else {
      b = std::min(b, a - b);
      Integral<MOD> ret = 1;
      for (T i = 1; i <= b; ++i)
        ret = ret * (a + 1 - i) / i;
      return ret;
    }
  }
};

template <int MOD> struct PowerTable : public std::vector<Integral<MOD>> {
  PowerTable(int n, const Integral<MOD> &g) {
    static_assert(sizeof(PowerTable) == sizeof(std::vector<Integral<MOD>>), "");
    this->resize(n + 1);
    this->at(0) = 1;
    this->at(1) = g;
    for (int i = 2; i < this->size(); ++i)
      this->at(i) = this->at(i - 1) * this->at(1);
  }
};

const int MOD = 998244353;
using Mint = Integral<MOD>;
using Binom = Binomial<MOD>;

// Binom binom(200000);
// PowerTable<MOD> pw2(200000, 2);

using ULL = unsigned long long;

const ULL seed = 9973;
const int kN = 1000000 + 5;
Mint pw[kN];

struct StringHash {
  std::vector<Mint> table;

  explicit StringHash(const std::string &s) : table(s.length() + 1) {
    CHECK(s.length() >= 1);
    for (int i = s.length() - 1; i >= 0; --i) {
      table[i] = table[i + 1] * seed + s[i];
    }
  }

  ULL hash(int l, int r) const {
    CHECK(r + 1 < table.size());
    return (table[l] - table[r + 1] * pw[r - l + 1]).val();
  }
};

struct KMP {
  std::vector<int> next;

  explicit KMP(const std::string &s) : next(s.length()) {
    next[0] = -1;
    for (int i = 1, j = -1; i < s.length(); ++i) {
      while (j > -1 && s[j + 1] != s[i])
        j = next[j];
      next[i] = s[j + 1] == s[i] ? ++j : -1;
    }
  }
};

void solve(const std::string &s, const std::string &t) {
  StringHash sh(s);
  KMP sk(s);
  StringHash th(t);
  int default_value = 0;
  for (int len = 1; len <= s.length() && len <= t.length(); ++len) {
    if (sh.hash(0, len - 1) == th.hash(t.length() - len, t.length() - 1)) {
      default_value = len;
    }
  }
  int last_jump = 0;
  for (int len = s.length() - 1; len > 0; --len) {
    if (sh.hash(s.length() - len, s.length() - 1) == sh.hash(0, len - 1)) {
      last_jump = len;
      break;
    }
  }
  auto transfer = [&](int j) -> int {
    if (j == s.length())
      return last_jump;
    return j;
  };

  std::vector<int> cache(s.length(), -1);
  for (int j = 0; j < s.length(); ++j) {
    if (j + t.length() <= s.length() &&
        sh.hash(j, j + t.length() - 1) == th.hash(0, t.length() - 1)) {
      cache[j] = j;
    } else if (j > 0) {
      cache[j] = cache[sk.next[j - 1] + 1];
    }
    int val = default_value;
    if (cache[j] >= 0) {
      val = cache[j] + t.length();
    }
    int result = transfer(val);
    printf("%d%c", result, " \n"[j + 1 == s.length()]);
  }
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  pw[0] = 1;
  for (int i = 1; i < kN; ++i)
    pw[i] = pw[i - 1] * seed;

  std::string s, t;
  while (reader >> s >> t) {
    solve(s, t);
  }
}
