#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

using flt = double;
const flt eps = 1e-12;

int sign(flt x) { return (x < -eps) ? -1 : (x > eps); }

void norm(int w[4]) {
  if (w[0] > w[1]) {
    for (int i = 0; i < 4; ++i) {
      w[i] *= -1;
    }
  }
  for (int i = 1; i < 4; ++i) {
    w[i] -= w[0];
  }
  if (w[2] > w[3]) {
    std::swap(w[2], w[3]);
  }
  w[2] = std::max(w[2], 0);
}

struct Equation {
  // a * x + b * y <= c
  double a, b, c;
  int side(flt x, flt y) const { return sign(a * x + b * y - c); }
};

// a * x + b
flt int_x(flt x0, flt x1, flt a, flt b) {
  return a / 2 * (x1 * x1 - x0 * x0) + b * (x1 - x0);
}

// a * x^2 + b * x + c
flt int_x2(flt x0, flt x1, flt a, flt b, flt c) {
  return a / 3 * (x1 * x1 * x1 - x0 * x0 * x0) + b / 2 * (x1 * x1 - x0 * x0) +
         c * (x1 - x0);
}

// a * x + b * y + c
flt int_xy(flt x0, flt x1, flt y0, flt y1, flt a, flt b, flt c) {
  return int_x(x0, x1, a * (y1 - y0),
               c * (y1 - y0) + 0.5 * b * (y1 * y1 - y0 * y0));
}

flt solve(flt x0, flt x1, flt y0, flt y1, const Equation &u,
          const Equation &v) {
  // u.side(x, y) <= 0, integral v.a * x + v.b * y + v.c
  if (u.side(x0, y0) >= 0) {
    return 0;
  }
  if (u.side(x1, y1) <= 0) {
    return int_xy(x0, x1, y0, y1, v.a, v.b, v.c);
  }
  flt ret = 0;
  if (u.side(x0, y1) < 0 && u.side(x1, y1) >= 0) {
    flt xm = (u.c - u.b * y1) / u.a;
    ret += int_xy(x0, xm, y0, y1, v.a, v.b, v.c);
    x0 = xm;
  }
  if (u.side(x1, y0) > 0) {
    x1 = (u.c - u.b * y0) / u.a;
  }
  flt ub2 = u.b * u.b, ua2 = u.a * u.a, uc2 = u.c * u.c;
  flt a = -u.a * v.a / u.b + 0.5 * v.b * ua2 / ub2;
  flt b = u.c * v.a / u.b - v.a * y0 - u.a * v.c / u.b - v.b / ub2 * u.c * u.a;
  flt c = v.c * (u.c / u.b - y0) + 0.5 * v.b * uc2 / ub2 - 0.5 * v.b * y0 * y0;
  ret += int_x2(x0, x1, a, b, c);
  return ret;
}

int main() {
  int x[4], y[4], z[4];
  while (scanf("%d%d%d", x, y, z) == 3) {
    for (int i = 1; i < 4; ++i) {
      scanf("%d%d%d", x + i, y + i, z + i);
    }
    norm(x);
    norm(y);
    norm(z);
    if (x[2] >= x[3] || y[2] >= y[3] || z[2] >= z[3]) {
      puts("0");
      continue;
    }
    if (x[2] + y[2] + z[2] >= x[1] + y[1] + z[1]) {
      puts("0");
      continue;
    }
    flt a = x[1], b = y[1], c = z[1];
    flt ret = solve(x[2], x[3], y[2], y[3], (Equation){c / a, c / b, c - z[3]},
                    (Equation){0., 0., double(z[3] - z[2])});
    ret += solve(x[2], x[3], y[2], y[3], (Equation){c / a, c / b, c - z[2]},
                 (Equation){-c / a, -c / b, c - z[2]});
    ret -= solve(x[2], x[3], y[2], y[3], (Equation){c / a, c / b, c - z[3]},
                 (Equation){-c / a, -c / b, c - z[2]});
    printf("%.10f\n", ret);
  }
  return 0;
}
