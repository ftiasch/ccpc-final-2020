#include <bits/stdc++.h>

static const int WIDTH = 18;
static const int64_t MAX = 1000000000000000000ULL;
static const constexpr std::array<int64_t, WIDTH + 1> LIMIT_LIMBS{
    0,
    1,
    11,
    111,
    1111,
    11111,
    111111,
    1111111,
    11111111,
    111111111,
    1111111111,
    11111111111,
    111111111111,
    1111111111111,
    11111111111111,
    111111111111111,
    1111111111111111,
    11111111111111111,
    111111111111111111};

struct BigInt {
  BigInt(int limbs, const std::string &s) : limb(limbs) {
    for (int i = s.size(); i--;) {
      limb[i / WIDTH] = limb[i / WIDTH] * 10 + s[i] - '0';
    }
  }

  int limbs() const { return limb.size(); }

  int64_t operator[](int i) const { return limb[i]; }

  template <bool tracking = true> void add_one() {
    int i = 0;
    while (i < limbs()) {
      if (limb[i] < MAX - 1) {
        limb[i]++;
        if (tracking) {
          track();
        }
        return;
      }
      limb[i++] = 0;
    }
    assert(i < limbs());
  }

  void sub_one() {
    int i = 0;
    while (i < limbs()) {
      if (limb[i] > 0) {
        limb[i]--;
        return;
      }
      limb[i++] = MAX - 1;
    }
    assert(i < limbs());
  }

  bool operator<=(const BigInt &other) const {
    for (int i = limbs(); i--;) {
      if (limb[i] != other[i]) {
        return limb[i] < other[i];
      }
    }
    return true;
  }

  BigInt &operator-=(const BigInt &one) {
    int borrow = 0;
    for (int i = 0; i < limbs(); ++i) {
      if (limb[i] - borrow >= one[i]) {
        limb[i] -= borrow + one[i];
        borrow = 0;
      } else {
        limb[i] += MAX - borrow - one[i];
        borrow = 1;
      }
    }
    return *this;
  }

  // mod by other, and return the quotient
  int mod(const BigInt &other) {
    int q = 0;
    while (other <= *this) {
      q++;
      *this -= other;
    }
    return q;
  }

  int64_t limit_limb(int i) const {
    int full = limit / WIDTH;
    if (i < full) {
      return LIMIT_LIMBS[WIDTH];
    }
    if (i == full) {
      return LIMIT_LIMBS[limit % WIDTH];
    }
    return 0;
  }

  void track() {
    while (tracker > 0 && limb[tracker - 1] == limit_limb(tracker - 1)) {
      tracker--;
    }
  }

  void set_limit(int limit_) {
    limit = limit_;
    tracker = limbs();
    track();
  }

  // std::string to_string() const {
  //   std::vector<char> buffer(WIDTH * limbs() + 1);
  //   char* s = buffer.data();
  //   for (int i = limbs(); i--;) {
  //     sprintf(s, "%018llu", limb[i]);
  //   }
  //   return buffer.data();
  // }

  void set_zero() {
    std::fill(limb.begin(), limb.end(), 0);
    set_limit(limit);
  }

  bool limit_reached() const { return tracker == 0; }

  std::vector<int64_t> limb;
  int limit, tracker;
};

bool operator==(const BigInt &a, const BigInt &b) {
  for (int i = 0; i < a.limbs(); ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

struct Segment {
  Segment(const BigInt &start_) : start(start_) {}

  void add(int v) { values.push_back(v); }

  int size() const { return values.size(); }

  BigInt start;
  std::vector<int> values;
};

std::vector<Segment> merge(const BigInt &zero,
                           const std::vector<Segment> &segs) {
  std::vector<Segment> result;
  int n = segs.size();
  std::vector<int> cur(n, -1);
  BigInt start = zero;
  Segment seg{zero};
  while (true) {
    int v = INT_MAX;
    for (int i = 0; i < n; ++i) {
      if (segs[i].start == start) {
        cur[i] = 0;
      }
      if (0 <= cur[i] && cur[i] < segs[i].size()) {
        v = std::min(v, segs[i].values[cur[i]++]);
      }
    }
    if (v == INT_MAX) {
      if (seg.size()) {
        result.push_back(seg);
      }
      int i = 0;
      while (i < n && ~cur[i]) {
        i++;
      }
      if (i == n) {
        return result;
      }
      start = segs[i].start;
      for (int j = i; j < n; ++j) {
        if (cur[j] == -1 && segs[j].start <= start) {
          start = segs[j].start;
        }
      }
      seg = Segment{start};
    } else {
      seg.add(v);
      start.add_one<false>();
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::string s;
  while (std::cin >> s) {
    std::reverse(s.begin(), s.end());
    int digits = (s.size() + 1 + WIDTH - 1) / WIDTH;
    // fprintf(stderr, "digits=%d\n", digits);
    BigInt zero{digits, ""};
    std::vector<Segment> psegs, nsegs;
    {
      Segment seg{BigInt{digits, s}};
      seg.add(0);
      psegs.push_back(seg);
    }
    for (int length = s.size() + 1; length > 0; --length) {
      std::vector<Segment> new_psegs, new_nsegs;
      BigInt cur_one{digits, std::string(length, '1')};
      // fprintf(stderr, "one.limbs=%d\n", cur_one.limb.size());
      // for (int i = cur_one.limb.size(); i --; ) {
      //   fprintf(stderr, "one[%d]=%llu\n", i, cur_one.limb[i]);
      // }
      for (auto &&seg : psegs) {
        BigInt r = seg.start;
        // fprintf(stderr, "r.limbs=%d\n", r.limb.size());
        // for (int i = r.limb.size(); i --; ) {
        //   fprintf(stderr, "r[%d]=%llu\n", i, r.limb[i]);
        // }
        int k = r.mod(cur_one);
        // fprintf(stderr, "k=%d\n", k);
        Segment new_pseg{r}, new_nseg{r};
        r.set_limit(length);
        r.add_one();
        for (int v : seg.values) {
          new_pseg.add(v + k * length);
          new_nseg.add(v + (k + 1) * length);
          if (r.limit_reached()) {
            new_psegs.push_back(new_pseg);
            new_nsegs.push_back(new_nseg);
            k++;
            r.set_zero();
            new_pseg = new_nseg = Segment{r};
            r.add_one();
          } else {
            r.add_one();
          }
        }
        if (new_pseg.size()) {
          new_psegs.push_back(new_pseg);
          new_nsegs.push_back(new_nseg);
        }
      }
      for (auto &&seg : nsegs) {
        BigInt r = seg.start;
        int k;
        if (r == zero) {
          r = cur_one;
          r.sub_one();
          k = 10;
        } else {
          r.sub_one();
          k = 9 - r.mod(cur_one);
        }
        // fprintf(stderr, "k=%d\n", k);
        Segment new_pseg{r}, new_nseg{r};
        r.set_limit(length);
        r.add_one();
        for (int v : seg.values) {
          new_nseg.add(v + k * length);
          new_pseg.add(v + (k + 1) * length);
          if (r.limit_reached()) {
            new_psegs.push_back(new_pseg);
            new_nsegs.push_back(new_nseg);
            k--;
            r.set_zero();
            new_pseg = new_nseg = Segment{r};
            r.add_one();
          } else {
            r.add_one();
          }
        }
        if (new_pseg.size()) {
          new_psegs.push_back(new_pseg);
          new_nsegs.push_back(new_nseg);
        }
      }
      psegs = merge(zero, new_psegs);
      nsegs = merge(zero, new_nsegs);
      // fprintf(stderr, "length=%d\n", length);
      // for (auto &&seg : psegs) {
      //   for (auto &&v : seg.values) {
      //     fprintf(stderr, "%d,", v);
      //   }
      // }
      // fprintf(stderr, "\n");
      // for (auto &&seg : nsegs) {
      //   for (auto &&v : seg.values) {
      //     fprintf(stderr, "%d,", v);
      //   }
      // }
      // fprintf(stderr, "\n");
    }
    assert(psegs.size());
    assert(psegs[0].start == zero);
    printf("%d\n", psegs[0].values[0]);
  }
}
