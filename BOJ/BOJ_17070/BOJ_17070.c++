#include <iostream>
#include <vector>

using namespace std;

int N, result = 0;
int dx[3] = {0, 1, 1};
int dy[3] = {1, 0, 1};
vector<vector<int>> house;

int input() {
  cin >> N;

  house.resize(N, vector<int>(N));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> house[i][j];
    }
  }

  return 0;
}

int dfs(int x, int y, int dir) {
  if (x == N - 1 && y == N - 1) {
    result++;

    return 0;
  }

  for (int i = 0; i < 3; i++) {
    if ((dir == 0 && i == 1) || (dir == 1 && i == 0)) {
      continue;
    }

    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx > N - 1 || ny > N - 1 || house[nx][ny] == 1) {
      continue;
    }

    if (i == 2 && (house[nx - 1][ny] == 1 || house[nx][ny - 1] == 1)) {
      continue;
    }

    dfs(nx, ny, i);
  }

  return 0;
}

int output() {
  cout << result << '\n';

  return 0;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  input();
  dfs(0, 1, 0);
  output();

  return 0;
}