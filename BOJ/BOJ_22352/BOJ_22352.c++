#include <iostream>
#include <queue>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int N, M;
int before[31][31];
int after[31][31];
bool visited[31][31];

void input() {
  cin >> N >> M;

  for (int n = 0; n < N; n++) {
    for (int m = 0; m < M; m++) {
      cin >> before[n][m];
    }
  }

  for (int n = 0; n < N; n++) {
    for (int m = 0; m < M; m++) {
      cin >> after[n][m];
    }
  }
}

void bfs(int x, int y, int num, int target) {
  queue<pair<int, int>> q;

  q.push({x, y});
  visited[x][y] = true;

  while (!q.empty()) {
    int cur_x = q.front().first;
    int cur_y = q.front().second;

    q.pop();
    before[cur_x][cur_y] = target;

    for (int i = 0; i < 4; i++) {
      int next_x = cur_x + dx[i];
      int next_y = cur_y + dy[i];

      if (next_x < 0 || next_x >= N || next_y < 0 || next_y >= M) {
        continue;
      }

      if (!visited[next_x][next_y] && before[next_x][next_y] == num) {
        q.push({next_x, next_y});
        visited[next_x][next_y] = true;
      }
    }
  }
}

bool solve() {
  bool flag = true;

  for (int n = 0; n < N; n++) {
    for (int m = 0; m < M; m++) {
      if (flag && before[n][m] != after[n][m]) {
        bfs(n, m, before[n][m], after[n][m]);
        flag = false;
      }
    }
  }

  for (int n = 0; n < N; n++) {
    for (int m = 0; m < M; m++) {
      if (before[n][m] != after[n][m]) {
        return false;
      }
    }
  }

  return true;
}

void output() {
  if (solve()) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  output();

  return 0;
}