#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

int T, k;
map<int, int> cnt_map;
priority_queue<int, vector<int>, greater<int>> min_pq;
priority_queue<int, vector<int>, less<int>> max_pq;

void input() { cin >> T; }

void init() {
  while (!min_pq.empty()) {
    min_pq.pop();
  }

  while (!max_pq.empty()) {
    max_pq.pop();
  }

  cnt_map.clear();
}

void insert(int n) {
  cnt_map[n]++;
  min_pq.push(n);
  max_pq.push(n);
}

void delete_min() {
  if (!min_pq.empty()) {
    cnt_map[min_pq.top()]--;
    min_pq.pop();
  }
}

void delete_max() {
  if (!max_pq.empty()) {
    cnt_map[max_pq.top()]--;
    max_pq.pop();
  }
}

void clean_pq() {
  while (!min_pq.empty() && cnt_map[min_pq.top()] == 0) {
    min_pq.pop();
  }
  while (!max_pq.empty() && cnt_map[max_pq.top()] == 0) {
    max_pq.pop();
  }
}

void solve() {
  while (T--) {
    init();

    cin >> k;

    for (int i = 0; i < k; i++) {
      int n;
      char cmd;

      cin >> cmd >> n;

      if (cmd == 'I') {
        insert(n);
      } else {
        if (n == 1) {
          delete_max();
        } else {
          delete_min();
        }

        clean_pq();
      }
    }

    clean_pq();

    if (max_pq.empty() || min_pq.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << max_pq.top() << ' ' << min_pq.top() << '\n';
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve();

  return 0;
}