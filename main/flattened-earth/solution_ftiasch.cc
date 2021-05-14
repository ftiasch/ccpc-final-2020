#include <bits/stdc++.h>

struct Event {
  int begin, end, weight;
};

bool operator<(const Event &a, const Event &b) { return a.begin < b.begin; }

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<Event> events;
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      if (a != b) {
        if (a > b) {
          std::swap(a, b);
        }
        events.push_back(Event{0, a, b - a});
        events.push_back(Event{a + 1, b, a + n - b});
        if (b + 1 < n) {
          events.push_back(Event{b + 1, n - 1, b - a});
        }
      }
    }
    std::sort(events.begin(), events.end());
    std::priority_queue<std::pair<int, int>> pq;
    int result = INT_MAX;
    for (int i = 0, j = 0; i < n; ++i) {
      while (j < static_cast<int>(events.size()) && events[j].begin == i) {
        pq.emplace(events[j].weight, events[j].end);
        j++;
      }
      while (!pq.empty() && pq.top().second < i) {
        pq.pop();
      }
      result = std::min(result, pq.empty() ? 0 : pq.top().first);
    }
    printf("%d\n", result);
  }
}
