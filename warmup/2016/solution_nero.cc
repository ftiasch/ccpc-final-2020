#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...) 1145141919810
#define CHECK(...) (__VA_ARGS__)
#endif

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

const int MOD = 7;
using Mint = Integral<MOD>;
using Binom = Binomial<MOD>;

// Binom binom(200000);
// PowerTable<MOD> pw2(200000, 2);

using Vector = std::vector<Mint>;
using Matrix = std::vector<Vector>;

Matrix mul(const Matrix &A, const Matrix &B) {
  Matrix C(A.size(), Vector(B[0].size()));
  for (int i = 0; i < A.size(); ++i)
    for (int j = 0; j < A[0].size(); ++j)
      for (int k = 0; k < B[0].size(); ++k)
        C[i][k] += A[i][j] * B[j][k];
  return C;
}

Matrix power(Matrix A, int m) {
  Matrix W(2, Vector(2));
  W[0][0] = W[1][1] = 1;
  for (; m; m >>= 1, A = mul(A, A))
    if (m & 1)
      W = mul(W, A);
  return W;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  std::string n;
  while (reader >> n) {
    Matrix A(2, Vector(2));
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        int x;
        reader >> x;
        A[i][j] = x;
      }
    }
    Matrix W(2, Vector(2));
    W[0][0] = W[1][1] = 1;
    for (int at = (int)n.size() - 1; at >= 0; --at) {
      int m = n[at] - '0';
      if (m) {
        W = mul(W, power(A, m));
      }
      A = power(A, 10);
    }
    printf("%d %d\n%d %d\n", W[0][0].val(), W[0][1].val(), W[1][0].val(),
           W[1][1].val());
  }
}
