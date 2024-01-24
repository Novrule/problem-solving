#include <climits>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> compress;
vector<vector<pair<int, int>>> forwardMap, backwardMap;

inline int getCompress(int v) {
  if (compress.count(v)) {
    return compress[v];
  } else {
    compress[v] = compress.size();

    return compress[v];
  }
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
  compress.clear();
  forwardMap.clear();
  forwardMap.resize(N);
  backwardMap.clear();
  backwardMap.resize(N);

  for (int i = 0; i < N; i++) {
    int s = getCompress(sCity[i]);
    int e = getCompress(eCity[i]);

    forwardMap[s].emplace_back(make_pair(e, mCost[i]));
    backwardMap[e].emplace_back(make_pair(s, mCost[i]));
  }

  return compress.size();
}

void add(int sCity, int eCity, int mCost) {
  int s = getCompress(sCity);
  int e = getCompress(eCity);

  forwardMap[s].emplace_back(make_pair(e, mCost));
  backwardMap[e].emplace_back(make_pair(s, mCost));
}

struct cmp {
  bool operator()(pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
  }
};

int dijkstra(int m) {
  int sum = 0;
  vector<int> forwardDist(compress.size(), INT_MAX);
  vector<int> backwardDist(compress.size(), INT_MAX);
  priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

  forwardDist[m] = 0;
  pq.push(make_pair(m, 0));

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

      if (forwardDist[next_node] > cur_cost + next_cost) {
        forwardDist[next_node] = cur_cost + next_cost;
        pq.push(make_pair(next_node, forwardDist[next_node]));
      }
    }
  }

  backwardDist[m] = 0;
  pq.push(make_pair(m, 0));

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

      if (backwardDist[next_node] > cur_cost + next_cost) {
        backwardDist[next_node] = cur_cost + next_cost;
        pq.push(make_pair(next_node, backwardDist[next_node]));
      }
    }
  }

  for (int i = 0; i < compress.size(); i++) {
    sum += forwardDist[i];
    sum += backwardDist[i];
  }

  return sum;
}

int cost(int mHub) {
  int m = getCompress(mHub);

  return dijkstra(m);
}
