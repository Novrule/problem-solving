#include <iostream>

using namespace std;

int input(int &N, int &K) {
  cin >> N >> K;

  return 0;
}

int dp(int N, int K) {
  int dp[N + 1][K + 1];

  for (int i = 0; i <= N; i++) {
    dp[i][0] = 0;
  }

  for (int i = 0; i <= K; i++) {
    dp[0][i] = 1;
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= K; j++) {
      dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 1000000000;
    }
  }

  cout << dp[N][K] << '\n';

  return 0;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N, K;

  input(N, K);
  dp(N, K);

  return 0;
}
