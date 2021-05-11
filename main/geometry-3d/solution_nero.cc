#include <bits/stdc++.h>
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

template<typename T> T sqr(T x) { return x * x; }

struct Point {
  DType x, y, z;
};

bool operator == (const Point& lhs, const Point& rhs) {
  return dcmp(lhs.x - rhs.x) == 0 && dcmp(lhs.y - rhs.y) == 0 && dcmp(lhs.z - rhs.z) == 0;
}

DType dot(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Point det(const Point& lhs, const Point& rhs) {
  return Point{
    .x = lhs.y * rhs.z - lhs.z * rhs.y,
    .y = lhs.z * rhs.x - lhs.x * rhs.z,
    .z = lhs.x * rhs.y - lhs.y * rhs.x
  };
}

DType length(const Point& p) {
  return std::sqrt(dot(p, p));
}

Point operator - (const Point& lhs, const Point& rhs) {
  return Point{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z};
}

Point operator * (DType a, const Point& p) {
  return Point{.x = a * p.x, .y = a * p.y, .z = a * p.z};
}

Point normalized(const Point& p) {
  const DType len = length(p);
  return Point{.x = p.x / len, .y = p.y / len, .z = p.z / len};
}

bool cross(const Point& P, const Point& Q, const Point& A, const Point& B) {
  const Point PQ = normalized(P - Q);
  const Point AQ = normalized(A - Q);
  const Point BQ = normalized(B - Q);
  return dcmp(dot(det(PQ, AQ), det(PQ, BQ))) <= 0;
}

double solve(const Point& P, const Point& Q, const Point& A, const Point& B) {
  if (A == B) {
    return length(P - A) + length(Q - A);
  }
  const Point PP = P - B;
  const Point QQ = Q - B;
  const Point AA = normalized(A - B);

  const DType dis = length(PP - dot(PP, AA) * AA);
  const Point R = normalized(QQ - dot(QQ, AA) * AA);
  const Point PPP = dot(PP, AA) * AA - dis * R;

  if (!cross(PPP, QQ, AA, Point{.x = 0, .y = 0, .z = 0})) {
    return std::min(length(P - A) + length(Q - A), length(P - B) + length(Q - B));
  }

  return length(PPP - QQ);
}

}  // namespace

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream& reader = std::cin;

  double x, y, z;
  while (reader >> x >> y >> z) {
    const Point P = Point{.x = x, .y = y, .z = z};
    reader >> x >> y >> z;
    const Point Q = Point{.x = x, .y = y, .z = z};
    reader >> x >> y >> z;
    const Point A = Point{.x = x, .y = y, .z = z};
    reader >> x >> y >> z;
    const Point B = Point{.x = x, .y = y, .z = z};

    printf("%.13f\n", solve(P, Q, A, B));
  }
}

