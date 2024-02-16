#include <climits>
#include <cmath>
#include <queue>
#include <vector>

#define MAX_N 350

using namespace std;

struct point {
  int distance, to;
};

bool operator<(const point &a, const point &b) {
  return a.distance > b.distance;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, range, map[MAX_N][MAX_N], who[MAX_N][MAX_N];
vector<pair<int, int>> graph[200];
pair<int, int> pos[200];

void init(int N, int mRange, int mMap[MAX_N][MAX_N]) {
  n = N;
  range = mRange;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      map[i][j] = mMap[i][j];
      who[i][j] = -1;
    }
  }

  for (int i = 0; i < 200; i++) {
    graph[i].clear();
  }

  return;
}

void add(int mID, int mRow, int mCol) {
  bool visited[MAX_N][MAX_N] = {
      false,
  };
  queue<pair<int, int>> q;

  visited[mRow][mCol] = true;
  q.push({mRow, mCol});

  for (int i = 0; i <= range && !q.empty(); i++) {
    int size = q.size();

    while (size--) {
      int x = q.front().first;
      int y = q.front().second;

      q.pop();

      if (who[x][y] != -1) {
        int cur = who[x][y];

        graph[cur].push_back({mID, i});
        graph[mID].push_back({cur, i});
      }

      if (i < range) {
        for (int j = 0; j < 4; j++) {
          int nextX = x + dx[j];
          int nextY = y + dy[j];

          if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n) {
            if (!visited[nextX][nextY] && !map[nextX][nextY]) {
              visited[nextX][nextY] = true;
              q.push({nextX, nextY});
            }
          }
        }
      }
    }
  }

  who[mRow][mCol] = mID;
  pos[mID] = {mRow, mCol};

  return;
}

inline int getDistance(int id1, int id2) {
  int x1 = pos[id1].first;
  int y1 = pos[id1].second;
  int x2 = pos[id2].first;
  int y2 = pos[id2].second;

  return abs(x1 - x2) + abs(y1 - y2);
}

int distance(int mFrom, int mTo) {
  vector<int> dist(200, INT_MAX);
  priority_queue<point> pq;

  dist[mFrom] = 0;

  pq.push({getDistance(mFrom, mTo), mFrom});

  while (!pq.empty()) {
    int distance = pq.top().distance;
    int cur = pq.top().to;

    pq.pop();

    distance -= getDistance(cur, mTo);

    if (dist[cur] < distance) {
      continue;
    }

    if (cur == mTo) {
      return distance;
    }

    for (auto &next : graph[cur]) {
      int nextID = next.first;
      int nextDistance = next.second;

      if (dist[nextID] > distance + nextDistance) {
        dist[nextID] = distance + nextDistance;
        pq.push({dist[nextID] + getDistance(nextID, mTo), nextID});
      }
    }
  }

  return -1;
}