#include <bits/stdc++.h>

int main() {
  int x[4], y[4], z[4];
  while (scanf("%d%d%d", x, y, z) == 3) {
    for (int i = 1; i < 4; ++i) {
      scanf("%d%d%d", x + i, y + i, z + i);
    }

#define NORMALIZE(W)                                                           \
  if (W[0] > W[1]) {                                                           \
    for (int i = 0; i < 4; ++i) {                                              \
      W[i] *= -1;                                                              \
    }                                                                          \
  }                                                                            \
  for (int i = 1; i < 4; ++i) {                                                \
    W[i] -= W[0];                                                              \
  }                                                                            \
  if (W[2] > W[3]) {                                                           \
    std::swap(W[2], W[3]);                                                     \
  }

    NORMALIZE(x);
    NORMALIZE(y);
    NORMALIZE(z);

#undef NORMALIZE

    double result = 0.;

    const double dim_x = x[1];
    const double dim_y = y[1];
    const double dim_z = z[1];
    for (int mask = 0; mask < 1 << 3; ++mask) {
      const int min_x = std::max(x[2 + (mask >> 0 & 1)], 0);
      const int min_y = std::max(y[2 + (mask >> 1 & 1)], 0);
      const int min_z = std::max(z[2 + (mask >> 2 & 1)], 0);
      double length = 1 - min_x / dim_x - min_y / dim_y - min_z / dim_z;
      if (length >= 0) {
        double length3 = length * length * length;
        if (__builtin_parity(mask)) {
          result -= length3;
        } else {
          result += length3;
        }
      }
    }
    printf("%.9f\n", result * dim_x * dim_y * dim_z / 6);
  }
}
