#include <iostream>
#include <vector>

using namespace std;

int input(int &n, int &last, vector<int> &arr) {
  cin >> n;

  for (int i = 0; i < n; i++) {
    int a, b;

    cin >> a >> b;
    arr[a] = b;

    if (last < a) {
      last = a;
    }
  }

  return 0;
}

int dp(int n, int last, vector<int> &arr) {
  int temp = 0;
  vector<int> dp(last + 1, 1);

  for (int i = 1; i <= last; i++) {
    for (int j = 1; j < i; j++) {
      if (arr[i] == -1 || arr[j] == -1) {
        continue;
      }

      if (arr[i] > arr[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }

    temp = max(temp, dp[i]);
  }

  cout << n - temp << '\n';

  return 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, last = 0;
  vector<int> arr(501, -1);

  input(n, last, arr);
  dp(n, last, arr);

  return 0;
}