#include "testlib.h"
#include <algorithm>
#include <cstring>
#include <vector>

using i64 = long long;

// Two Efficient Algorithms for Linear Suffix Array Construction
#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;
  std::vector<int> lcp;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const { return sa.size() - 1; }

private:
  using SLTypes = std::vector<bool>;
  int *buffer, *freq, *cur;
  int len;

  void buildRankTable();
  template <class T> void computeLCPArray(const T *s);
  template <class T> void countFrequency(const T *s, int n, int m);
  template <class T> void induce(const T *s, int *sa, int m, const SLTypes &t);
  template <class T> void sa_is(const T *s, int *sa, int n, int m);
};

template <class T> void SuffixArray::build(const T *s, int n) {
  this->len = n;
  int m = *std::max_element(s, s + n) + 1;
  build(s, n, m);
  buildRankTable();
  computeLCPArray(s);
}

template <class T> void SuffixArray::build(const T *s, int n, int m) {
  sa.resize(n + 1);
  if (n == 0)
    sa[0] = 0;
  else {
    // memory usage: sa + buffer + types
    // = 4 * (n + max(m * 2, n)) + 2 * n / 8 + O(1) bytes
    std::vector<int> buffer((std::max(m, (n + 1) / 2) + 1) * 2);
    this->buffer = &buffer[0];
    sa_is<T>(s, &sa[0], n + 1, m);
  }
}

void SuffixArray::buildRankTable() {
  int n = size() + 1;
  rank.resize(n);
  for (int i = 0; i < n; ++i)
    rank[sa[i]] = i;
}

template <class T> void SuffixArray::computeLCPArray(const T *s) {
  const int n = size() + 1;
  lcp.resize(n);
  for (int i = 0, h = lcp[0] = 0; i < n; ++i)
    if (rank[i]) {
      int j = sa[rank[i] - 1];
      while (i + h < n && j + h < n && s[i + h] == s[j + h])
        ++h;
      if (lcp[rank[i]] = h)
        --h;
    }
}

template <class T> void SuffixArray::countFrequency(const T *s, int n, int m) {
  memset(freq, 0, sizeof(int) * m);
  for (int i = 0; i < n; ++i)
    ++freq[(int)s[i]];
  for (int i = 1; i < m; ++i)
    freq[i] += freq[i - 1];
  memcpy(cur, freq, sizeof(int) * m);
}

template <class T>
void SuffixArray::induce(const T *s, int *sa, int m, const SLTypes &t) {
  const int n = t.size();
  memcpy(cur + 1, freq, sizeof(int) * (m - 1));
  for (int i = 0; i < n; ++i) {
    int p = sa[i] - 1;
    if (p >= 0 && t[p])
      pushL(p);
  }
  memcpy(cur, freq, sizeof(int) * m);
  for (int i = n - 1; i > 0; --i) {
    int p = sa[i] - 1;
    if (p >= 0 && !t[p])
      pushS(p);
  }
}

template <class T> void SuffixArray::sa_is(const T *s, int *sa, int n, int m) {
  SLTypes t(n);
  memset(sa, 0, sizeof(int) * n);
  for (int i = n - 2; ~i; --i) {
    t[i] = (s[i] == s[i + 1]) ? t[i + 1] : s[i] > s[i + 1];
  }
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = 1; i < n; ++i)
    if (t[i - 1] > t[i])
      pushS(i);
  induce(s, sa, m, t);
  int n1 = 0, order = 0;
  for (int i = 0, p; i < n; ++i) {
    if ((p = sa[i]) && t[p - 1] > t[p])
      sa[n1++] = p;
  }
  int *s1 = sa + n1;
  memset(s1, -1, sizeof(int) * (n - n1));
  s1[(sa[0] - 1) / 2] = order++;
  for (int i = 1; i < n1; ++i) {
    bool diff = true;
    for (int x = sa[i - 1], y = sa[i];; ++x, ++y) {
      if (s[x] != s[y] || t[x] != t[y])
        break;
      else if (t[x] > t[x + 1] && t[y] > t[y + 1]) {
        diff = (s[x + 1] != s[y + 1]);
        break;
      }
    }
    s1[(sa[i] - 1) / 2] = (order += diff) - 1;
  }
  for (int i = 0, x = 0; i < n - n1; ++i) {
    if (~s1[i])
      s1[x++] = s1[i];
  }
  if (order != n1) {
    sa_is<int>(s1, sa, n1, order);
    for (int i = 0; i < n1; ++i)
      s1[sa[i]] = i;
  }
  for (int i = 1, j = 0; i < n; ++i) {
    if (t[i - 1] > t[i])
      sa[s1[j++]] = -i;
  }
  memset(s1, 0, sizeof(int) * (n - n1));
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = n1 - 1; ~i; --i)
    pushS(-sa[i]);
  induce(s, sa, m, t);
}

// random
std::string gen_rand(int n, int c) {
  std::string s(n, 'a');
  for (int i = 0; i < n; ++i) {
    s[i] = 'a' + rnd.next(0, c - 1);
  }
  return s;
}

// antihash string
std::string gen_thue_morse(int n, int m) {
  std::string s(n, 'a');
  for (int i = 1; i <= n; ++i) {
    int w = 0, j = i - 1;
    while (j) {
      w = (w + j) % m;
      j /= m;
    }
    s[i - 1] = w + 'a';
  }
  return s;
}

// prefix of fibonacci word
std::string gen_fib(int n) {
  std::string s(n, 'a');
  s[0] = s[1] = rnd.next(0, 25) + 'a';
  while (s[0] == s[1]) {
    s[1] = rnd.next(0, 25) + 'a';
  }
  int a = 1, b = 2;
  for (int i = 3; i <= n; ++i) {
    if (a + b < i) {
      a += b;
      std::swap(a, b);
    }
    s[i - 1] = s[i - b - 1];
  }
  return s;
}

// string with period p
std::string gen_period(int n, const std::string &p) {
  std::string s(n, 'a');
  for (int i = 0; i < n; ++i)
    s[i] = p[i % p.size()];
  return s;
}

// the probability of letter p is \frac{1}{m^p}
std::string gen_geo(int n, int m) {
  std::vector<char> letters;
  for (char i = 'a'; i <= 'z'; ++i) {
    letters.push_back(i);
  }
  shuffle(letters.begin(), letters.end());
  std::string s(n, 'a');
  for (int i = 1; i <= n; ++i) {
    int p = 0;
    while (p < 25 && !rnd.next(0, m - 1))
      ++p;
    s[i - 1] = letters[p];
  }
  return s;
}

// i-th character is a + ctz(i)
std::string gen_abacaba(int n, int c) {
  std::vector<char> letters;
  for (char i = 'a'; i <= 'z'; ++i) {
    letters.push_back(i);
  }
  shuffle(letters.begin(), letters.end());
  std::string s(n, 'a');
  for (int i = 1; i <= n; ++i) {
    s[i - 1] = letters[std::min(__builtin_ctz(i), c)];
  }
  return s;
}

// string with many borders
std::string gen_border(int n, const std::vector<int> &diff) {
  std::string s = "a";
  for (auto d : diff) {
    std::string p = s;
    s = "";
    for (int j = 0; j < d; ++j)
      s += p;
    s.back()++;
  }
  s.pop_back();
  return s;
}

const int N = 1e6 + 10;

std::vector<int> edges[N];
int subtree_size[N];
int pi[N];

void dfs(int u) {
  subtree_size[u] = 1;
  for (auto &v : edges[u]) {
    dfs(v);
    subtree_size[u] += subtree_size[v];
  }
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int N = 1000000;
  int type = std::atoi(argv[1]);
  int min_n = std::atoi(argv[2]);
  int max_n = std::atoi(argv[3]);
  int t_type = std::atoi(argv[4]);
  std::vector<int> ns;
  while (N >= min_n) {
    ns.emplace_back(rnd.next(min_n, std::min(N, max_n)));
    N -= ns.back();
  }
  if (N)
    ns.emplace_back(N);
  for (int i = 0; i < (int)ns.size(); ++i) {
    int n = ns[i];
    std::string s, t;
    if (type == 1) {
      int c = std::atoi(argv[5]);
      s = gen_rand(n, c);
    } else if (type == 2) {
      int c = std::atoi(argv[5]);
      s = gen_thue_morse(n, c);
    } else if (type == 3) {
      s = gen_fib(n);
    } else if (type == 4) {
      std::string period = std::string(argv[5]);
      s = gen_period(n, period);
    } else if (type == 5) {
      int c = std::atoi(argv[5]);
      s = gen_geo(n, c);
    } else if (type == 6) {
      int c = std::atoi(argv[5]);
      s = gen_abacaba(n, c);
    } else if (type == 7) {
      std::vector<int> diff;
      for (int i = 5; i < argc - 1; ++i) {
        diff.push_back(std::atoi(argv[i]));
      }
      s = gen_border(n, diff);
    }

    n = s.size();

    if (t_type == 0) {
      int l = rnd.next(s.size());
      int r = rnd.next(s.size());
      if (l > r)
        std::swap(l, r);
      t = s.substr(l, r - l + 1);
    } else {
      SuffixArray sa;
      sa.build(s.data(), s.size());
      for (int i = 0; i <= n; ++i) {
        edges[i].clear();
        subtree_size[i] = 0;
      }
      pi[0] = -1;
      for (int i = 1, j = -1; i < n; ++i) {
        while (j >= 0 && s[j + 1] != s[i])
          j = pi[j];
        pi[i] = (s[j + 1] == s[i]) ? ++j : j;
      }
      for (int i = 0; i < n; ++i) {
        edges[pi[i] + 1].push_back(i + 1);
      }
      dfs(0);

      int m = rnd.next(n / 4, n / 3);
      i64 best_sum = -1;
      int best_pos = 0;
      for (int i = 1, j; i <= n; i = j) {
        i64 sum = subtree_size[sa.sa[i]];
        for (j = i + 1; j <= n && sa.lcp[j] >= m; ++j) {
          sum += subtree_size[sa.sa[j]];
        }
        if (n - sa.sa[i] >= m && sum > best_sum) {
          best_sum = sum;
          best_pos = sa.sa[i];
        }
      }
      t = s.substr(best_pos, m);
      fprintf(stderr, "%lld\n", best_sum);
    }
    printf("%s\n", s.c_str());
    printf("%s\n", t.c_str());
  }
  return 0;
}
