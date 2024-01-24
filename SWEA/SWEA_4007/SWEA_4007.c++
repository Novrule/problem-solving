#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M, X;
vector<vector<pair<int, int>>> forwardMap;
vector<vector<pair<int, int>>> backwardMap;

void input() {
  cin >> N >> M >> X;

  forwardMap.clear();
  forwardMap.resize(N + 1);
  backwardMap.clear();
  backwardMap.resize(N + 1);

  for (int i = 0; i < M; i++) {
    int s, e, t;

    cin >> s >> e >> t;

    forwardMap[s].emplace_back(make_pair(e, t));
    backwardMap[e].emplace_back(make_pair(s, t));
  }
}

struct cmp {
  bool operator()(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
  }
};

int dijkstra() {
  int ans = INT_MIN;
  vector<int> forwardDist(N + 1, INT_MAX);
  vector<int> backwardDist(N + 1, INT_MAX);
  priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

  forwardDist[X] = 0;
  pq.push(make_pair(X, 0));

  while (!pq.empty()) {
    int cur_node = pq.top().first;
    int cur_cost = pq.top().second;

    pq.pop();

    if (forwardDist[cur_node] < cur_cost) {
      continue;
    }

    for (int i = 0; i < forwardMap[cur_node].size(); i++) {
      int next_node = forwardMap[cur_node][i].first;
      int next_cost = forwardMap[cur_node][i].second;

      if (forwardDist[next_node] > forwardDist[cur_node] + next_cost) {
        forwardDist[next_node] = forwardDist[cur_node] + next_cost;
        pq.push(make_pair(next_node, forwardDist[next_node]));
      }
    }
  }

  backwardDist[X] = 0;
  pq.push(make_pair(X, 0));

  while (!pq.empty()) {
    int cur_node = pq.top().first;
    int cur_cost = pq.top().second;

    pq.pop();

    if (backwardDist[cur_node] < cur_cost) {
      continue;
    }

    for (int i = 0; i < backwardMap[cur_node].size(); i++) {
      int next_node = backwardMap[cur_node][i].first;
      int next_cost = backwardMap[cur_node][i].second;

      if (backwardDist[next_node] > backwardDist[cur_node] + next_cost) {
        backwardDist[next_node] = backwardDist[cur_node] + next_cost;
        pq.push(make_pair(next_node, backwardDist[next_node]));
      }
    }
  }

  for (int i = 1; i < N + 1; i++) {
    if (ans < forwardDist[i] + backwardDist[i]) {
      ans = forwardDist[i] + backwardDist[i];
    }
  }

  return ans;
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
    int ans;

    input();
    ans = dijkstra();
    output(ans, test_case);
  }

  return 0;
}