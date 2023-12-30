#include <iostream>

using namespace std;

int input(int &N, int &M, int &r, int &c, int &d, int **&arr) {
  cin >> N >> M;
  cin >> r >> c >> d;

  arr = new int *[N];
  for (int i = 0; i < N; i++) {
    arr[i] = new int[M];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> arr[i][j];
    }
  }

  return 0;
}

int clean(int N, int M, int r, int c, int d, int **arr) {
  int result = 0;

  while (1) {
    if (arr[r][c] == 0) {
      arr[r][c] = 2;
      result++;
    }

    if (arr[r - 1][c] && arr[r + 1][c] && arr[r][c - 1] && arr[r][c + 1]) {
      if (d == 0) {
        r++;
      } else if (d == 1) {
        c--;
      } else if (d == 2) {
        r--;
      } else if (d == 3) {
        c++;
      }

      if (arr[r][c] == 1) {
        break;
      }
    } else {
      d = (d + 3) % 4;

      if (d == 0 && !arr[r - 1][c]) {
        r--;
      } else if (d == 1 && !arr[r][c + 1]) {
        c++;
      } else if (d == 2 && !arr[r + 1][c]) {
        r++;
      } else if (d == 3 && !arr[r][c - 1]) {
        c--;
      }
    }
  }

  cout << result << '\n';

  return 0;
}

int main(void) {
  int N, M, r, c, d, **arr, result;

  input(N, M, r, c, d, arr);
  clean(N, M, r, c, d, arr);

  return 0;
}