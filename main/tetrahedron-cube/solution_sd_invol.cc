#include <bits/stdc++.h>

const double eps = 1e-10;

inline int dcmp(double x) { return (x > eps) - (x < -eps); }

bool normalize(int *x) {
  // assert x0 < x1
  if (x[1] < x[0]) {
    for (int i = 0; i < 4; ++i) {
      x[i] *= -1;
    }
  }
  // assert x2 < x3
  if (x[2] > x[3]) {
    std::swap(x[2], x[3]);
  }
  // assert [x0, x1] and [x2, x3] are intersected
  x[4] = std::max(x[0], x[2]);
  x[5] = std::min(x[1], x[3]);
  if (x[4] >= x[5]) {
    return false;
  }
  for (int i = 1; i < 6; ++i) {
    x[i] -= x[0];
  }
  return true;
}
int A, B, C, D, X, Y, Z;

double F(double z) {
  // [0, X] x [0, Y]; // Ax + By <= D - Cz;
  if (A * X + B * Y <= D - C * z) {
    return X * Y;
  } else if (0 >= D - C * z) {
    return 0;
  }
  double yl = (D - C * z) / B;
  double yr = (D - C * z - A * X) / B;
  double xu = (D - C * z - B * Y) / A;
  double xd = (D - C * z) / A;
  if (dcmp(yl) >= 0 && dcmp(yl - Y) <= 0) {
    if (dcmp(yr) >= 0 && dcmp(yr - Y) <= 0) {
      return (yl + yr) * X / 2;
    } else {
      assert(dcmp(xd) >= 0 && dcmp(xd - X) <= 0);
      return yl * xd / 2;
    }
  } else {
    assert(dcmp(xu) >= 0 && dcmp(xu - X) <= 0);
    if (dcmp(yr) >= 0 && dcmp(yr - Y) <= 0) {
      return X * Y - (X - xu) * (Y - yr) / 2;
    } else {
      assert(dcmp(xd) >= 0 && dcmp(xd - X) <= 0);
      return (xu + xd) * Y / 2;
    }
  }
}
double simpson(double a, double b) {
  if (dcmp(a - b) == 0) {
    return 0;
  }
  double c = (a + b) * 0.5;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}

double cal() {
  std::vector<double> v = {0, 1.0 * Z};
  double z = 1.0 * (D - A * X - B * Y) / C;
  if (dcmp(z) > 0 && dcmp(z - Z) < 0) {
    v.push_back(z);
  }
  z = 1.0 * (D - B * Y) / C;
  if (dcmp(z) > 0 && dcmp(z - Z) < 0) {
    v.push_back(z);
  }
  z = 1.0 * (D - A * X) / C;
  if (dcmp(z) > 0 && dcmp(z - Z) < 0) {
    v.push_back(z);
  }
  z = 1.0 * D / C;
  if (dcmp(z) > 0 && dcmp(z - Z) < 0) {
    v.push_back(z);
  }
  double ret = 0;
  std::sort(v.begin(), v.end());
  for (int i = 0; i + 1 < v.size(); ++i) {
    ret += simpson(v[i], v[i + 1]);
  }
  return ret;
}

int main() {
  int x[6], y[6], z[6];
  while (~scanf("%d%d%d", x, y, z)) {
    for (int i = 1; i < 4; ++i) {
      scanf("%d%d%d", x + i, y + i, z + i);
    }
    if (!normalize(x) || !normalize(y) || !normalize(z)) {
      puts("0");
      continue;
    }
    A = y[1] * z[1], B = x[1] * z[1], C = x[1] * y[1];
    D = x[1] * y[1] * z[1] - A * x[4] - B * y[4] - C * z[4];
    // Ax + By + Cz <= D
    x[5] -= x[4], x[4] = 0;
    y[5] -= y[4], y[4] = 0;
    z[5] -= z[4], z[4] = 0;
    // printf("%dx + %dy + %dz <= %d\n", A, B, C, D);
    // printf("X: [%d, %d]\n", x[4], x[5]);
    // printf("Y: [%d, %d]\n", y[4], y[5]);
    // printf("Z: [%d, %d]\n", z[4], z[5]);
    X = x[5] - x[4];
    Y = y[5] - y[4];
    Z = z[5] - z[4];
    // [0, X] X [0, Y] X [0, Z] and Ax + By + Cz <= D
    printf("%.9f\n", cal());
  }
}
