#include <bits/stdc++.h>

#define DEBUG(...)                                                             \
  do {                                                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
  } while (0)

namespace {

// struct FastIn {
//   FastIn(FILE *in_ = stdin) : in(in_) {}

//   char next_char() {
//     if (head == length) {
//       head = 0;
//       length = fread(buffer, 1, LENGTH, in);
//     }
//     return buffer[head++];
//   }

//   uint64_t next_uint() {
//     char c = next_char();
//     while (!std::isdigit(c)) {
//       c = next_char();
//     }
//     uint64_t x = 0;
//     for (; std::isdigit(c); c = next_char()) {
//       x = x * 10U + c - '0';
//     }
//     return x;
//   }

//   uint64_t next_int() {
//     char c = next_char();
//     while (!std::isdigit(c) && c != '-') {
//       c = next_char();
//     }
//     uint64_t sign = 1;
//     if (c == '-') {
//       sign = -1;
//       c = next_char();
//     }
//     uint64_t x = 0;
//     for (; std::isdigit(c); c = next_char()) {
//       x = x * 10 + c - '0';
//     }
//     return sign * x;
//   }

// private:
//   static const int LENGTH = 1 << 16;

//   char buffer[LENGTH];
//   size_t head = 0;
//   size_t length = 0;
//   FILE *in;
// };

const int CIRCLES = 200000;
const int BASE_EDGES = 100000;
const int MAGIC = 256;
const int OUTER_EDGES = (BASE_EDGES + (MAGIC - 1)) / MAGIC * 4;
const int INNER_EDGES = MAGIC << 1;

int n;
int base_parent[BASE_EDGES + 1];

struct BaseMap {
  int outer_id, inner_id;
};

BaseMap base_map[BASE_EDGES + 1];

struct InnerEntry {
  int head, to, parent, distance[2], vertex_weight;
};

InnerEntry inner_tree_entry_buffer[BASE_EDGES + 2 * OUTER_EDGES];
InnerEntry *inner_tree_entry_buffer_start = inner_tree_entry_buffer;

int quick_inner_tree_sum[INNER_EDGES + 2][INNER_EDGES + 2],
    inner_tree_timestamp[INNER_EDGES + 1];

// tree[i].to is an edge to vertex (tree[i].to)
// tree[v].parent is the inner id of the parent of v
struct InnerTree {
  template <int root> void dfs(int p, int u, int d) {
    tree[u].distance[root] = d;
    max_distance[root] = std::max(max_distance[root], d);
    if (u) {
      int v = tree[u].parent;
      if (v != p) {
        dfs<root>(u, v, d + 1);
      }
    }
    for (int i = tree[u].head; i < tree[u + 1].head; ++i) {
      int v = tree[i].to;
      if (v != p) {
        dfs<root>(u, v, d + 1);
      }
    }
  }

  int query_preprocess() const {
    for (int x = 0; x <= max_distance[0] + 1; ++x) {
      for (int y = 0; y <= max_distance[1] + 1; ++y) {
        quick_inner_tree_sum[x][y] = 0;
      }
    }
    int sum_vertex_weight = 0;
    for (int i = 1; i <= edges; ++i) {
      sum_vertex_weight += tree[i].vertex_weight;
      quick_inner_tree_sum[tree[i].distance[0]][tree[i].distance[1]] +=
          tree[i].vertex_weight;
    }
    for (int x = max_distance[0]; x >= 0; --x) {
      for (int y = max_distance[1]; y >= 0; --y) {
        quick_inner_tree_sum[x][y] += quick_inner_tree_sum[x + 1][y] +
                                      quick_inner_tree_sum[x][y + 1] -
                                      quick_inner_tree_sum[x + 1][y + 1];
      }
    }
    return sum_vertex_weight;
  }

  int slow_count(int now, int max_r0, int max_r1) const {
    int result = 0;
    for (int i = 1; i <= edges; ++i) {
      if (inner_tree_timestamp[i] == now || tree[i].distance[0] <= max_r0 ||
          tree[i].distance[1] <= max_r1) {
        result += tree[i].vertex_weight;
      }
    }
    return result;
  }

  void dfs_with_timestamp(int now, int p, int u, int d) const {
    inner_tree_timestamp[u] = now;
    if (d) {
      if (u) {
        int v = tree[u].parent;
        if (v != p) {
          dfs_with_timestamp(now, u, v, d - 1);
        }
      }
      for (int i = tree[u].head; i < tree[u + 1].head; ++i) {
        int v = tree[i].to;
        if (v != p) {
          dfs_with_timestamp(now, u, v, d - 1);
        }
      }
    }
  }

  void finish_build() {
    for (int i = 0; i <= edges + 1; ++i) {
      tree[i].head = 0;
    }
    for (int i = 1; i <= edges; ++i) {
      tree[tree[i].parent].head++;
    }
    for (int i = 1; i <= edges + 1; ++i) {
      tree[i].head += tree[i - 1].head;
    }
    for (int i = edges; i >= 1; --i) {
      tree[--tree[tree[i].parent].head].to = i;
    }
    max_distance[0] = max_distance[1] = 0;
    dfs<0>(-1, 0, 0);
    dfs<1>(-1, 1, 0);
  }

  int edges, top_outer_id, bot_outer_id, top_base_id, max_distance[2];
  InnerEntry *tree;
} inner_tree[OUTER_EDGES + 1];

struct OuterTree {
  struct OuterEdge {
    int to, length;
  };

  void dfs0(int &count, int p, int u) {
    dfs_position[u] = count++;
    size[u] = 1;
    for (int i = head[u]; i < head[u + 1]; ++i) {
      int v = children[i].to;
      dfs0(count, u, v);
      size[u] += size[v];
    }
  }

  void dfs(int r, int p, int u, int d) {
    distance[r][u] = d;
    if (u) {
      int v = parent[u].to;
      if (v != p) {
        dfs(r, u, v, d + parent[u].length);
      }
    }
    for (int i = head[u]; i < head[u + 1]; ++i) {
      int v = children[i].to;
      if (v != p) {
        dfs(r, u, v, d + children[i].length);
      }
    }
  }

  void finish_build() {
    memset(head, 0, sizeof(*head) * (edges + 2));
    for (int i = 1; i <= edges; ++i) {
      head[parent[i].to]++;
    }
    for (int i = 1; i <= edges + 1; ++i) {
      head[i] += head[i - 1];
    }
    for (int i = edges; i >= 1; --i) {
      children[--head[parent[i].to]] = {i, parent[i].length};
    }
    int count = 0;
    dfs0(count, -1, 0);
    for (int r = 0; r <= edges; ++r) {
      dfs(r, -1, r, 0);
    }
  }

  // return true is u is an ancestor of v
  bool is_ancestor(int u, int v) const {
    return dfs_position[u] <= dfs_position[v] &&
           dfs_position[v] < dfs_position[u] + size[u];
  }

  int edges, head[OUTER_EDGES + 2], dfs_position[OUTER_EDGES + 1],
      size[OUTER_EDGES + 1];
  OuterEdge parent[OUTER_EDGES + 1];
  OuterEdge children[OUTER_EDGES];
  int distance[OUTER_EDGES + 1][OUTER_EDGES + 1];
} outer_tree;

struct TreeDecomposition {
  struct Subtree {
    bool boundary_exists() const { return ~outer_id; }

    bool operator<(const Subtree &o) const {
      return boundary_exists() == o.boundary_exists()
                 ? edges < o.edges
                 : boundary_exists() > o.boundary_exists();
    }

    int stack_begin, outer_depth, outer_id, base_id, edges;
  };

  void add_subtree_range(int outer_id, InnerTree &it, const Subtree &st) {
    for (int i = 0; i < st.edges; ++i) {
      int v = to[stack[st.stack_begin + i]];
      int p = base_parent[v];
      base_map[v].outer_id = outer_id;
      if (base_map[v].inner_id == -1) {
        base_map[v].inner_id = ++it.edges;
      }
      it.tree[base_map[v].inner_id].parent = base_map[p].inner_id;
    }
  }

  void dfs(int magic, int i, int u) {
    int childs = head[u + 1] - head[u];
    int stack_begin = stack_size;
    int boundaries = 0;
    for (int j = head[u]; j < head[u] + childs; ++j) {
      int v = to[j];
      Subtree &subtree = subtree_buffer[j];
      subtree.stack_begin = stack_size;
      subtree.outer_id = -1;
      stack[stack_size++] = j;
      dfs(magic, j, v);
      subtree.edges = stack_size - subtree.stack_begin;
      boundaries += subtree.boundary_exists();
    }
    std::sort(subtree_buffer + head[u], subtree_buffer + head[u] + childs);
    if (u && stack_size - stack_begin <= magic && boundaries < 2) {
      Subtree &returned_subtree = subtree_buffer[i];
      if (childs == 0) {
        returned_subtree.outer_depth = 1;
        returned_subtree.outer_id = -1;
        returned_subtree.base_id = u;
      } else {
        Subtree first_subtree = subtree_buffer[head[u]];
        returned_subtree.outer_depth = first_subtree.outer_depth + 1;
        returned_subtree.outer_id = first_subtree.outer_id;
        returned_subtree.base_id = first_subtree.base_id;
      }
    } else {
      int u_outer_id = u ? ++outer_tree.edges : 0;
      int k = boundaries;
      for (int j = 0; j < boundaries; ++j) {
        Subtree subtree_with_boundary = subtree_buffer[head[u] + j];
        assert(subtree_with_boundary.boundary_exists());
        int outer_id = subtree_with_boundary.outer_id;
        InnerTree &it = inner_tree[outer_id];
        it.tree = inner_tree_entry_buffer_start;
        it.edges = 1;
        base_map[u] = {u_outer_id, 0};
        base_map[subtree_with_boundary.base_id] = {outer_id, 1};
        it.top_outer_id = u_outer_id;
        it.bot_outer_id = outer_id;
        it.top_base_id = u;
        outer_tree.parent[outer_id] = {u_outer_id,
                                       subtree_with_boundary.outer_depth};
        add_subtree_range(outer_id, it, subtree_with_boundary);
        while (k < childs &&
               it.edges + subtree_buffer[head[u] + k].edges <= (magic << 1)) {
          add_subtree_range(outer_id, it, subtree_buffer[head[u] + (k++)]);
        }
        it.finish_build();
        inner_tree_entry_buffer_start += 2 + it.edges;
      }
      while (k < childs) {
        Subtree &first_subtree = subtree_buffer[head[u] + (k++)];
        int outer_id = ++outer_tree.edges;
        InnerTree &it = inner_tree[outer_id];
        it.tree = inner_tree_entry_buffer_start;
        it.edges = 1;
        base_map[u] = {u_outer_id, 0};
        base_map[first_subtree.base_id] = {outer_id, 1};
        it.top_outer_id = u_outer_id;
        it.bot_outer_id = outer_id;
        it.top_base_id = u;
        outer_tree.parent[outer_id] = {u_outer_id, first_subtree.outer_depth};
        add_subtree_range(outer_id, it, first_subtree);
        while (k < childs &&
               it.edges + subtree_buffer[head[u] + k].edges <= (magic << 1)) {
          add_subtree_range(outer_id, it, subtree_buffer[head[u] + (k++)]);
        }
        it.finish_build();
        inner_tree_entry_buffer_start += 2 + it.edges;
      }
      stack_size = stack_begin;
      if (~i) {
        Subtree &returned_subtree = subtree_buffer[i];
        returned_subtree.outer_depth = 1;
        returned_subtree.outer_id = u_outer_id;
        returned_subtree.base_id = u;
      }
    }
  }

  void decompose(int magic) {
    memset(head, 0, sizeof(*head) * (n + 1));
    for (int i = 1; i < n; ++i) {
      head[base_parent[i]]++;
    }
    for (int i = 1; i <= n; ++i) {
      head[i] += head[i - 1];
    }
    for (int i = n; i-- > 1;) {
      to[--head[base_parent[i]]] = i;
    }
    stack_size = 0;
    for (int i = 0; i < n; ++i) {
      base_map[i].inner_id = -1;
    }
    outer_tree.edges = 0;
    dfs(magic, -1, 0);
    outer_tree.finish_build();
  }

  int head[BASE_EDGES + 2], to[BASE_EDGES];
  int stack_size, stack[BASE_EDGES];
  Subtree subtree_buffer[BASE_EDGES];
};

struct Circle {
  int o, r;
};

Circle circle_buffer[CIRCLES];

struct QueryContext {
  Circle &operator[](int i) { return circle[i]; }

  const Circle &operator[](int i) const { return circle[i]; }

  int k;
  Circle *circle;
  int result;
};

QueryContext query_context[100000];

struct BaseParent {
  void initialize(int n) {
    base_parent[1] = 0;
    memset(head, -1, sizeof(*head) * (n + 1));
    for (int i = 0; i < (n - 1) << 1; ++i) {
      scanf("%d", to + i);
    }
    for (int i = 0; i < (n - 1) << 1; ++i) {
      next[i] = head[to[i ^ 1]];
      head[to[i ^ 1]] = i;
    }
    dfs(0, 1);
  }

  void dfs(int p, int u) {
    base_parent[u] = p;
    for (int iterator = head[u]; ~iterator; iterator = next[iterator]) {
      int v = to[iterator];
      if (v != p) {
        dfs(u, v);
      }
    }
  }

  int head[BASE_EDGES + 1], to[BASE_EDGES << 1], next[BASE_EDGES << 1];
};

} // namespace

#ifndef NO_MAIN
int main() {
  int q;
  int now = 0;
  while (scanf("%d%d", &n, &q) == 2) {
    static int vertex_weight[BASE_EDGES + 1];
    for (int i = 1; i <= n; ++i) {
      scanf("%d", vertex_weight + i);
    }
    {
      static BaseParent bp;
      bp.initialize(n);
    }
    n++;
    //   base_parent[1] = 0;
    //   for (int i = 2; i < n; ++i) {
    //     base_parent[i] = fin.next_uint();
    //   }
    {
      static TreeDecomposition d;
      d.decompose(MAGIC);
    }
    // for (int i = 0; i < n; ++i) {
    //   DEBUG("%d = (%d, %d)\n", i, base_map[i].outer_id,
    //   base_map[i].inner_id);
    // }
    for (int i = 1; i < n; ++i) {
      inner_tree[base_map[i].outer_id]
          .tree[base_map[i].inner_id]
          .vertex_weight = vertex_weight[i];
    }
    int circle_count = 0;
    for (int i = 0; i < q; ++i) {
      QueryContext &qc = query_context[i];
      scanf("%d", &qc.k);
      qc.circle = circle_buffer + circle_count;
      qc.result = 0;
      circle_count += qc.k;
      for (int j = 0; j < qc.k; ++j) {
        scanf("%d%d", &qc[j].o, &qc[j].r);
      }
    }
    for (int current_bot = 1; current_bot <= outer_tree.edges; ++current_bot) {
      int current_top = outer_tree.parent[current_bot].to;
      //   DEBUG("current_top=%d current_bot=%d\n", current_top, current_bot);
      const InnerTree &it = inner_tree[current_bot];
      int sum_inner_tree_vertex_weight = it.query_preprocess();
      for (int query_id = 0; query_id < q; ++query_id) {
        ++now;
        int max_r[]{-1, -1};
        int has_inside = false;
        QueryContext &qc = query_context[query_id];
        for (int j = 0; j < qc.k; ++j) {
          //   DEBUG("\trange(%d, %d)\n", qc[j].o, qc[j].r);
          int bot_outer_id = base_map[qc[j].o].outer_id;
          int top_outer_id = outer_tree.parent[bot_outer_id].to;
          int inner_id = base_map[qc[j].o].inner_id;
          if (bot_outer_id == current_bot) {
            // DEBUG("\t\tinside\n");
            has_inside = true;
            it.dfs_with_timestamp(now, -1, inner_id, qc[j].r);
          } else {
            int entry, distance_to_entry;
            if (outer_tree.is_ancestor(current_bot, bot_outer_id)) {
              //   DEBUG("A\n");
              entry = 1;
              distance_to_entry =
                  inner_tree[bot_outer_id].tree[inner_id].distance[0] +
                  outer_tree.distance[top_outer_id][current_bot];
            } else if (outer_tree.is_ancestor(bot_outer_id, current_bot)) {
              //   DEBUG("B\n");
              entry = 0;
              distance_to_entry =
                  inner_tree[bot_outer_id].tree[inner_id].distance[1] +
                  outer_tree.distance[bot_outer_id][current_top];
            } else {
              //   DEBUG("C\n");
              entry = 0;
              distance_to_entry =
                  inner_tree[bot_outer_id].tree[inner_id].distance[0] +
                  outer_tree.distance[top_outer_id][current_top];
            }
            // DEBUG("\t\toutside entry=%d distance_to_entry=%d\n", entry,
            //       distance_to_entry);
            if (distance_to_entry <= qc[j].r) {
              max_r[entry] =
                  std::max(max_r[entry], std::min(qc[j].r - distance_to_entry,
                                                  it.max_distance[entry]));
            }
          }
        }
        if (has_inside) {
          int result = it.slow_count(now, max_r[0], max_r[1]);
          //   DEBUG("\twith inside now=%d max_r0=%d max_r1=%d | result = %d\n",
          //   now,
          // max_r[0], max_r[1], result);
          qc.result += result;
        } else {
          //   DEBUG("\twithout inside max_r0=%d max_r1=%d | result = %d\n",
          //         max_r[0], max_r[1], -1);
          qc.result += sum_inner_tree_vertex_weight -
                       quick_inner_tree_sum[max_r[0] + 1][max_r[1] + 1];
        }
      }
    }
    for (int i = 0; i < q; ++i) {
      printf("%d\n", query_context[i].result);
    }
  }
}
#endif
