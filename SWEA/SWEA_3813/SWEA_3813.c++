#include <iostream>

using namespace std;

int N, K;
int data[200000];
int drive[200000];

void input(int &max) {
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> drive[i];

    if (drive[i] > max) {
      max = drive[i];
    }
  }

  for (int i = 0; i < K; i++) {
    cin >> data[i];
  }
}

int solve(int max) {
  int ans;
  int left = 1;
  int right = max;

  while (left <= right) {
    int mid = (left + right) / 2;
    int idx = 0;

    for (int i = 0; i < N; i++) {
      if (drive[i] > mid) {
        continue;
      }

      int start = i;
      int end = i + data[idx];

      for (int j = start; j < end && j < N; j++) {
        if (drive[j] > mid) {
          i = j;

          break;
        }

        if (j == end - 1) {
          i = j;
          idx++;
        }
      }

      if (idx == K) {
        break;
      }
    }

    if (idx == K) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return ans;
}

void output(int ans, int test_case) {
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
    int max = 0;

    input(max);
    ans = solve(max);
    output(ans, test_case);
  }

  return 0;
}