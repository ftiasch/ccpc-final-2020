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

Point det(const Point &lhs, const Point &rhs) {
  return Point{.x = lhs.y * rhs.z - lhs.z * rhs.y,
               .y = lhs.z * rhs.x - lhs.x * rhs.z,
               .z = lhs.x * rhs.y - lhs.y * rhs.x};
}

DType length(const Point &p) { return std::sqrt(dot(p, p)); }

Point operator-(const Point &lhs, const Point &rhs) {
  return Point{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z};
}

Point operator*(DType a, const Point &p) {
  return Point{.x = a * p.x, .y = a * p.y, .z = a * p.z};
}

Point normalized(const Point &p) {
  const DType len = length(p);
  return Point{.x = p.x / len, .y = p.y / len, .z = p.z / len};
}

std::string to_string(const Point &p) {
  return std::string("Point{x=") + std::to_string(p.x) +
         ",y=" + std::to_string(p.y) + ",z=" + std::to_string(p.z) + "}";
}

bool cross(const Point &P, const Point &Q, const Point &A, const Point &B) {
  if (P == Q || A == Q || B == Q) {
    return true;
  }
  const Point PQ = normalized(P - Q);
  const Point AQ = normalized(A - Q);
  const Point BQ = normalized(B - Q);
  return dcmp(dot(det(PQ, AQ), det(PQ, BQ))) <= 0;
}

const Point origin = Point{.x = 0, .y = 0, .z = 0};

// P -> A -> Q
DType walk(const Point &P, const Point &Q, const Point &A) {
  return length(P - A) + length(Q - A);
}

double solve(const Point &P, const Point &Q, const Point &A, const Point &B) {
  if (A == B) {
    return walk(P, Q, A);
  }
  if (det(A - Q, B - Q) == origin) {
    DType ret = std::min(walk(P, Q, A), walk(P, Q, B));
    if (dcmp(dot(A - Q, B - Q)) < 0) {
      ret = std::min(ret, length(P - Q));
    }
    return ret;
  }
  const Point PP = P - B;
  const Point QQ = Q - B;
  const Point AA = normalized(A - B);

  const DType dis = length(PP - dot(PP, AA) * AA);
  const Point R = normalized(QQ - dot(QQ, AA) * AA);
  const Point PPP = dot(PP, AA) * AA - dis * R;

  if (!cross(PPP, QQ, A - B, origin)) {
    return std::min(length(P - A) + length(Q - A),
                    length(P - B) + length(Q - B));
  }

  return length(PPP - QQ);
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
