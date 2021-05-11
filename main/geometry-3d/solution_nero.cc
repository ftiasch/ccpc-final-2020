#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

namespace {

using DType = long double;

template<typename T> T sqr(T x) { return x * x; }

struct Point {
  DType x, y, z;
};

DType dot(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
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

    const Point PP = P - B;
    const Point QQ = Q - B;
    const Point AA = normalized(A - B);

    const DType dis = length(PP - dot(PP, AA) * AA);
    const Point R = normalized(QQ - dot(QQ, AA) * AA);
    const Point PPP = dot(PP, AA) * AA - dis * R;

    DType res = length(PPP - QQ);
    printf("%.13f\n", double(res));
  }
}

