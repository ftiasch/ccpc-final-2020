#include <bits/stdc++.h>
#ifdef ALGO
#include "el_psy_congroo.hpp"
#else
#define DUMP(...)
#define CHECK(...)
#endif

using LL = long long;

struct Node {
  LL sum[2] = {};
  int cnt[2] = {};
  bool is_fliped = false;

  void flip() {
    std::swap(sum[0], sum[1]);
    std::swap(cnt[0], cnt[1]);
    is_fliped ^= 1;
  }
};

Node operator+(const Node &lhs, const Node &rhs) {
  Node ret;
  for (int i = 0; i < 2; ++i) {
    ret.sum[i] = lhs.sum[i] + rhs.sum[i];
    ret.cnt[i] = lhs.cnt[i] + rhs.cnt[i];
  }
  return ret;
}

struct SegmentTree {
  std::vector<Node> nodes;
  static int get_id(int l, int r) { return l + r | (l != r); }

  explicit SegmentTree(int size) : nodes(size * 2 - 1) {}

  void build(int l, int r, const std::string &s) {
    if (l == r) {
      int c = s[l] == '1';
      Node &node = nodes[get_id(l, r)];
      node.sum[c] = 2 * (l + 1);
      node.cnt[c]++;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, s);
    build(mid + 1, r, s);
    up(l, r);
  }

  void up(int l, int r) {
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    nodes[get_id(l, r)] = nodes[get_id(l, mid)] + nodes[get_id(mid + 1, r)];
  }

  void down(int l, int r) {
    if (l == r)
      return;
    if (!nodes[get_id(l, r)].is_fliped)
      return;
    int mid = (l + r) >> 1;
    nodes[get_id(l, mid)].flip();
    nodes[get_id(mid + 1, r)].flip();
    nodes[get_id(l, r)].is_fliped = false;
  }

  void flip(int L, int R, int l, int r) {
    if (L <= l && r <= R) {
      nodes[get_id(l, r)].flip();
      return;
    }
    down(l, r);
    int mid = (l + r) >> 1;
    if (L <= mid)
      flip(L, R, l, mid);
    if (mid < R)
      flip(L, R, mid + 1, r);
    up(l, r);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::istream &reader = std::cin;

  const int MOD = 998244353;
  int n, q;
  while (reader >> n >> q) {
    std::string s;
    reader >> s;
    SegmentTree tree(n);
    tree.build(0, n - 1, s);
    while (q--) {
      int l, r;
      reader >> l >> r;
      --l;
      --r;
      tree.flip(l, r, 0, n - 1);
      const Node &node = tree.nodes[SegmentTree::get_id(0, n - 1)];
      LL result = node.sum[1] - LL(node.cnt[1]) * node.cnt[1];
      printf("%lld\n", result % MOD);
    }
  }
}
