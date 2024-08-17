#include <iostream>
#include <stack>

using namespace std;

int N;
stack<pair<int, int>> s;

void input() { cin >> N; }

void solve() {
  for (int i = 0; i < N; i++) {
    int tmp;

    cin >> tmp;

    while (!s.empty()) {
      if (tmp < s.top().second) {
        cout << s.top().first << " ";

        break;
      }

      s.pop();
    }

    if (s.empty()) {
      cout << 0 << " ";
    }

    s.push(make_pair(i + 1, tmp));
  }
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve();

  return 0;
}