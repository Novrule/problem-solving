#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M;
vector<vector<pair<int, int>>> map;

void input() {
  cin >> N >> M;

  map.clear();
  map.resize(N + 1);

  for (int i = 0; i < M; i++) {
    int a, b, c;

    cin >> a >> b >> c;

    map[a].emplace_back(make_pair(b, c));
    map[b].emplace_back(make_pair(a, c));
  }
}

struct compare {
  bool operator()(pair<int, long long> a, pair<int, long long> b) {
    if (a.second > b.second) {
      return true;
    } else if (a.second == b.second) {
      return a.first > b.first;
    } else {
      return false;
    }
  }
};

long long dijkstra() {
  long long sum = 0;
  vector<int> edge(N + 1);
  vector<long long> dist(N + 1, LLONG_MAX);
  priority_queue<pair<int, long long>, vector<pair<int, long long>>, compare>
      pq;

  edge[1] = 0;
  dist[1] = 0;
  pq.push(make_pair(1, 0));

  while (!pq.empty()) {
    int cur_node = pq.top().first;
    long long cur_cost = pq.top().second;

    pq.pop();

    if (dist[cur_node] < cur_cost) {
      continue;
    }

    for (int i = 0; i < map[cur_node].size(); i++) {
      int next_node = map[cur_node][i].first;
      long long next_edge = static_cast<long long>(map[cur_node][i].second);

      if (dist[next_node] > cur_cost + next_edge) {
        dist[next_node] = cur_cost + next_edge;
        edge[next_node] = static_cast<int>(next_edge);
        pq.push(make_pair(next_node, dist[next_node]));
      } else if (dist[next_node] == cur_cost + next_edge) {
        edge[next_node] = min(edge[next_node], static_cast<int>(next_edge));
      }
    }
  }

  for (int i = 1; i < N + 1; i++) {
    sum += static_cast<long long>(edge[i]);
  }

  return sum;
}

void output(long long ans, int test_case) {
  cout << '#' << test_case << ' ' << ans << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    long long ans;

    input();
    ans = dijkstra();
    output(ans, test_case);
  }

  return 0;
}