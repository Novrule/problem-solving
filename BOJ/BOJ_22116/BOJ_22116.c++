#include <iostream>

using namespace std;

int N, ans;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int arr[1010][1010];
int visited[1010][1010];
int dp[1010][1010];

void input() {
  cin >> N;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> arr[i][j];
    }
  }
}

int dfs(int x, int y, int h) {
  int tmp = 0;

  if (x < 1 || y < 1 || x > N || y > N || visited[x][y]) {
    return 0;
  }

  if (y == N && x == N) {
    return 1;
  }

  if (dp[x][y] >= 0) {
    return dp[x][y];
  }

  visited[x][y] = 1;

  for (int i = 0; i < 4; i++) {
    if (abs(arr[x][y] - arr[x + dx[i]][y + dy[i]]) <= h) {
      tmp = max(tmp, dfs(x + dx[i], y + dy[i], h));
    }
  }

  dp[x][y] = tmp;
  visited[x][y] = 0;

  return tmp;
}

void binary_search() {
  int left = 0;
  int right = 1000000000;

  while (left <= right) {
    int mid = (left + right) / 2;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        dp[i][j] = -1;
      }
    }

    if (dfs(1, 1, mid)) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  ans = left;
}

void output() { cout << ans << '\n'; }

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  binary_search();
  output();

  return 0;
}
