#include <iostream>
#include <vector>

using namespace std;

string B, S;
vector<int> failure;

void input() {
  cin >> B >> S;

  failure.clear();
  failure.resize(S.length(), 0);
}

int kmp() {
  int n = B.length();
  int m = S.length();
  int j = 0;
  int ans = 0;

  for (int i = 1; i < m; i++) {
    while (j > 0 && S[i] != S[j]) {
      j = failure[j - 1];
    }

    if (S[i] == S[j]) {
      failure[i] = ++j;
    }
  }

  j = 0;

  for (int i = 0; i < n; i++) {
    while (j > 0 && B[i] != S[j]) {
      j = failure[j - 1];
    }

    if (B[i] == S[j]) {
      if (j == m - 1) {
        j = failure[j];
        ans++;
      } else {
        j++;
      }
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

    input();
    ans = kmp();
    output(ans, test_case);
  }

  return 0;
}