#include <bits/stdc++.h>

static const int MOD = 998244353;

struct SGT {
  struct Node {
    void flip(int l, int r) {
      flipped ^= 1;
      count = (r - l + 1) - count;
      sum = static_cast<long long>(l + r) * (r - l + 1) / 2 - sum;
    }

    bool flipped;
    int count;
    long long sum;
  };

  SGT(int n_, const std::vector<char> &s) : n(n_), tree(n << 1) {
    build(s, 0, n - 1);
  }

  static int get_id(int l, int r) { return l + r | (l != r); }

  void update(int l, int r) {
    Node &n = tree[get_id(l, r)];
    int m = (l + r) >> 1;
    const Node &ln = tree[get_id(l, m)];
    const Node &rn = tree[get_id(m + 1, r)];
    n.count = ln.count + rn.count;
    n.sum = ln.sum + rn.sum;
  }

  void push_down(int l, int r) {
    Node &n = tree[get_id(l, r)];
    if (n.flipped) {
      int m = (l + r) >> 1;
      Node &ln = tree[get_id(l, m)];
      Node &rn = tree[get_id(m + 1, r)];
      ln.flip(l, m);
      rn.flip(m + 1, r);
      n.flipped = false;
    }
  }

  void build(const std::vector<char> &s, int l, int r) {
    Node &n = tree[get_id(l, r)];
    if (l == r) {
      n.flipped = false;
      n.count = s[l] == '1';
      n.sum = s[l] == '1' ? l : 0;
    } else {
      int m = (l + r) >> 1;
      build(s, l, m);
      build(s, m + 1, r);
      n.flipped = false;
      update(l, r);
    }
  }

  void flip(int l, int r, int a, int b) {
    if (b < l || r < a) {
      return;
    }
    if (a <= l && r <= b) {
      tree[get_id(l, r)].flip(l, r);
    } else {
      push_down(l, r);
      int m = (l + r) >> 1;
      flip(l, m, a, b);
      flip(m + 1, r, a, b);
      update(l, r);
    }
  }

  long long flip(int l, int r) {
    flip(0, n - 1, l, r);
    const Node &root = tree[get_id(0, n - 1)];
    return 2 * root.sum + 2 * root.count -
           static_cast<long long>(root.count) * root.count;
  }

  int n;
  std::vector<Node> tree;
};

int main() {
  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    std::vector<char> buffer(n + 1);
    scanf("%s", buffer.data());
    SGT sgt{n, buffer};
    while (q--) {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%d\n", static_cast<int>(sgt.flip(l - 1, r - 1) % MOD));
    }
  }
}
