#include <algorithm>
#include <iostream>

using namespace std;

int N, M;
int arr[101][101];
long long ans = -1;

void input() {
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%1d", &arr[i][j]);
    }
  }
}

int get_sum(int start_x, int start_y, int end_x, int end_y) {
  int sum = 0;

  for (int i = start_x; i <= end_x; i++) {
    for (int j = start_y; j <= end_y; j++) {
      sum += arr[i][j];
    }
  }

  return sum;
}

void solve() {
  for (int i = 0; i < N - 2; i++) {
    for (int j = i + 1; j < N - 1; j++) {
      long long square_1 = get_sum(0, 0, i, M - 1);
      long long square_2 = get_sum(i + 1, 0, j, M - 1);
      long long square_3 = get_sum(j + 1, 0, N - 1, M - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  for (int i = 0; i < M - 2; i++) {
    for (int j = i + 1; j < M - 1; j++) {
      long long square_1 = get_sum(0, 0, N - 1, i);
      long long square_2 = get_sum(0, i + 1, N - 1, j);
      long long square_3 = get_sum(0, j + 1, N - 1, M - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  for (int i = M - 1; i > 0; i--) {
    for (int j = 0; j < N - 1; j++) {
      long long square_1 = get_sum(0, i, N - 1, M - 1);
      long long square_2 = get_sum(0, 0, j, i - 1);
      long long square_3 = get_sum(j + 1, 0, N - 1, i - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  for (int i = 0; i < M - 1; i++) {
    for (int j = 0; j < N - 1; j++) {
      long long square_1 = get_sum(0, 0, N - 1, i);
      long long square_2 = get_sum(0, i + 1, j, M - 1);
      long long square_3 = get_sum(j + 1, i + 1, N - 1, M - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < M - 1; j++) {
      long long square_1 = get_sum(0, 0, i, M - 1);
      long long square_2 = get_sum(i + 1, 0, N - 1, j);
      long long square_3 = get_sum(i + 1, j + 1, N - 1, M - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  for (int i = N - 1; i > 0; i--) {
    for (int j = 0; j < M - 1; j++) {
      long long square_1 = get_sum(i, 0, N - 1, M - 1);
      long long square_2 = get_sum(0, 0, i - 1, j);
      long long square_3 = get_sum(0, j + 1, i - 1, M - 1);

      ans = max(ans, square_1 * square_2 * square_3);
    }
  }

  cout << ans << endl;
}

int main(void) {
  input();
  solve();

  return 0;
}