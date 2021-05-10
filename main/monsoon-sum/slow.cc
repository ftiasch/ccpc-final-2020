#include <bits/stdc++.h>

namespace {

static const int MOD = 998244353;

struct Matrix {
  Matrix(int dim) : matrix(dim, std::vector<int>(dim)) {}

  int dim() const { return matrix.size(); }

  const int *operator[](int i) const { return matrix[i].data(); }

  int *operator[](int i) { return matrix[i].data(); }

  std::vector<std::vector<int>> matrix;
};

Matrix operator*(const Matrix &a, const Matrix &b) {
  int n = a.dim();
  Matrix c{n};
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      long long result = 0;
      for (int k = i; k <= j; ++k) {
        result += static_cast<long long>(a[i][k]) * b[k][j] % MOD;
        if (result >= MOD) {
          result -= MOD;
        }
      }
      c[i][j] = result;
    }
  }
  return c;
}

Matrix power(Matrix a, int n) {
  int m = a.dim();
  Matrix result{m};
  for (int i = 0; i < m; ++i) {
    result[i][i] = 1;
  }
  while (n) {
    if (n & 1) {
      result = result * a;
    }
    a = a * a;
    n >>= 1;
  }
  return result;
}

} // namespace

int main() {
  int n, x, y, q;
  while (scanf("%d%d%d%d", &n, &x, &y, &q) == 4) {
    std::vector<int> a(q), b(q);
    int m = 0;
    for (int i = 0; i < q; ++i) {
      scanf("%d%d", &a[i], &b[i]);
      m = std::max(m, std::max(a[i], b[i]));
    }
    int v = (m + 1) << 1;
    Matrix mat{v};
    for (int i = 0; i + 1 < v; ++i) {
      mat[i][i + 1] = 1;
    }
    for (int i = 0; i <= m; ++i) {
      mat[i][i] = x;
      mat[m + 1 + i][m + 1 + i] = y;
    }
    mat = power(mat, n + 1);
    for (int i = 0; i < q; ++i) {
      printf("%d\n", mat[m - a[i]][m + 1 + b[i]]);
    }
  }
}
