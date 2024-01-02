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
  int dp[k + 1] = {
      0,
  };

  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = coins[i]; j <= k; j++) {
      dp[j] += dp[j - coins[i]];
    }
  }

  return dp[k];
}

int main(void) {
  int n, k, result;
  vector<int> coins;

  input(n, k, coins);
  result = dp(n, k, coins);

  cout << result << '\n';

  return 0;
}