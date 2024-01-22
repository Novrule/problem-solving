#include <iostream>
#include <unordered_set>

using namespace std;

int N, M;
unordered_set<string> s;

void input() {
  cin >> N >> M;

  s.clear();

  for (int i = 0; i < N; i++) {
    string str;

    cin >> str;
    s.insert(str);
  }
}

int solve() {
  int ans = 0;

  for (int i = 0; i < M; i++) {
    string str;

    cin >> str;

    if (s.count(str)) {
      ans++;
    }
  }

  return ans;
}

void output(int ans, int test_case) {
  cout << '#' << test_case << ' ' << ans << '\n';
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int ans;

    input();
    ans = solve();
    output(ans, test_case);
  }

  return 0;
}