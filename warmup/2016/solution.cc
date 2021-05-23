#include <cstring>
#include <iostream>
#include <string>

struct Matrix {
  Matrix() { memset(mat, 0, sizeof(mat)); }

  int *operator[](int i) { return mat[i]; }

  const int *operator[](int i) const { return mat[i]; }

  int mat[2][2];
};

Matrix operator*(const Matrix &a, const Matrix &b) {
  Matrix c;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        (c[i][j] += a[i][k] * b[k][j]) %= 7;
      }
    }
  }
  return c;
}

int main() {
  std::string n;
  while (std::cin >> n) {
    Matrix a;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        std::cin >> a[i][j];
      }
    }
    int r = 0;
    for (auto &&c : n) {
      r = (r * 10 + c - '0') % 2016;
    }
    Matrix b;
    b[0][0] = b[1][1] = 1;
    for (int _ = 0; _ < r; ++_) {
      b = b * a;
    }
    printf("%d %d\n%d %d\n", b[0][0], b[0][1], b[1][0], b[1][1]);
  }
}
