#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

char str[3] = {'m', 'o', 'o'};
int N;
char ans;

void input() { cin >> N; }

void output() { cout << ans << '\n'; }

void solve(int N, int cur, int len) {
  int new_len = len * 2 + cur + 3;

  if (N <= 3) {
    ans = str[N - 1];
    output();

    exit(0);
  }

  if (new_len < N) {
    solve(N, cur + 1, new_len);
  } else {
    if (N > len && N <= len + cur + 3) {
      if (N - len != 1) {
        ans = 'o';
      } else {
        ans = 'm';
      }
      output();

      exit(0);
    } else {
      solve(N - (len + cur + 3), 1, 3);
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve(N, 1, 3);
}