#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dp[4001][4001];

int main(void) {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int ans = 0;
  string s1, s2;

  cin >> s1 >> s2;

  for (int i = 0; i < s2.length(); i++) {
    for (int j = 0; j < s1.length(); j++) {
      if (s2[i] == s1[j]) {
        dp[i][j] = 1;

        if (i >= 1 && j >= 1) {
          dp[i][j] += dp[i - 1][j - 1];
        }

        ans = max(ans, dp[i][j]);
      }
    }
  }

  cout << ans;

  return 0;
}
