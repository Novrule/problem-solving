#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int input(int& n, int& k, vector<int>& coins) {
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    int coin;

    cin >> coin;
    coins.push_back(coin);
  }

  return 0;
}

int dp(int n, int k, vector<int> coins) {
  int dp[k + 1];

  for (int i = 0; i <= k; i++) {
    dp[i] = 10001;
  }

  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = coins[i]; j <= k; j++) {
      dp[j] = min(dp[j], dp[j - coins[i]] + 1);
    }
  }

  return dp[k];
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, k, result;
  vector<int> coins;

  input(n, k, coins);
  result = dp(n, k, coins);

  if (result == 10001) {
    result = -1;
  }

  cout << result << '\n';

  return 0;
}