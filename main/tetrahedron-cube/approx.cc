#include <bits/stdc++.h>

static const int COUNT = 10000000;

int main() {
  std::mt19937_64 gen{0};
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

    const int dim_x = x[1];
    const int dim_y = y[1];
    const int dim_z = z[1];
    std::uniform_real_distribution<double> x_range(x[2], x[3]),
        y_range(y[2], y[3]), z_range(z[2], z[3]);
    int insides = 0;
    for (int _ = 0; _ < COUNT; ++_) {
      double sample_x = x_range(gen);
      double sample_y = y_range(gen);
      double sample_z = z_range(gen);
      if (sample_x >= 0 && sample_y >= 0 && sample_z >= 0 &&
          sample_x / dim_x + sample_y / dim_y + sample_z / dim_z <= 1) {
        insides++;
      }
    }
    printf("%.9f\n", (x[3] - x[2]) * (y[3] - y[2]) * (z[3] - z[2]) *
                         static_cast<double>(insides) / COUNT);
  }
}
