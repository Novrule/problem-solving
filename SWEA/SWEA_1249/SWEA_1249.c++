#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, MAX = 100;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
vector<vector<int>> map(100, vector<int>(100, 0));

void input() {
  cin >> N;

  for (int i = 0; i < N; i++) {
    string str;

    cin >> str;

    for (int j = 0; j < N; j++) {
      map[i][j] = str[j] - '0';
    }
  }
}

int bfs() {
  vector<vector<int>> dist(N, vector<int>(N, INT_MAX));
  queue<pair<int, int>> q;

  dist[0][0] = 0;
  q.push(make_pair(0, 0));

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;

    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
        if (dist[nx][ny] > dist[x][y] + map[nx][ny]) {
          dist[nx][ny] = dist[x][y] + map[nx][ny];
          q.push(make_pair(nx, ny));
        }
      }
    }
  }

  return dist[N - 1][N - 1];
}

void output(int &ans, int &test_case) {
  cout << "#" << test_case << " " << ans << "\n";
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
    ans = bfs();
    output(ans, test_case);
  }

  return 0;
}