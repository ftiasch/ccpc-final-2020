#include <cmath>
#include <iostream>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

namespace {

using DType = long double;

const DType eps = 1e-8;

int dcmp(DType x) { return x < -eps ? -1 : x > eps; }

template <typename T> T sqr(T x) { return x * x; }

struct Point {
  DType x, y, z;
};

bool operator==(const Point &lhs, const Point &rhs) {
  return dcmp(lhs.x - rhs.x) == 0 && dcmp(lhs.y - rhs.y) == 0 &&
         dcmp(lhs.z - rhs.z) == 0;
}

DType dot(const Point &lhs, const Point &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

DType length(const Point &p) { return std::sqrt(dot(p, p)); }

Point operator+(const Point &lhs, const Point &rhs) {
  return Point{.x = lhs.x + rhs.x, .y = lhs.y + rhs.y, .z = lhs.z + rhs.z};
}

Point operator-(const Point &lhs, const Point &rhs) {
  return Point{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z};
}

Point operator*(DType a, const Point &p) {
  return Point{.x = a * p.x, .y = a * p.y, .z = a * p.z};
}

DType walk(const Point &P, const Point &Q, const Point &A) {
  return length(P - A) + length(Q - A);
}

double solve(const Point &P, const Point &Q, const Point &A, const Point &B) {
  DType result = walk(P, Q, A);
  if (A == B) {
    return result;
  }
  DType l = 0.0, r = 1.0;
  for (int step = 0; step < 100; ++step) {
    DType ll = (l * 2 + r) / 3.0;
    DType rr = (l + r * 2) / 3.0;
    DType lla = walk(P, Q, ll * (B - A) + A);
    DType rra = walk(P, Q, rr * (B - A) + A);
    result = std::min(result, lla);
    result = std::min(result, rra);
    if (lla > rra) {
      l = ll;
    } else {
      r = rr;
    }
  }
  return result;
}

} // namespace

int main() {
  int x, y, z;
  while (scanf("%d%d%d", &x, &y, &z) == 3) {
    const Point P = Point{.x = (double)x, .y = (double)y, .z = (double)z};
    scanf("%d%d%d", &x, &y, &z);
    const Point Q = Point{.x = (double)x, .y = (double)y, .z = (double)z};
    scanf("%d%d%d", &x, &y, &z);
    const Point A = Point{.x = (double)x, .y = (double)y, .z = (double)z};
    scanf("%d%d%d", &x, &y, &z);
    const Point B = Point{.x = (double)x, .y = (double)y, .z = (double)z};

    printf("%.13f\n", solve(P, Q, A, B));
  }
}
