#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef pair<int, int> pii;

using namespace std;

void input(int &N, int &K, vector<int> &vec) {
  cin >> N;

  for (int i = 0; i < N; i++) {
    int cur;

    cin >> cur;

    vec.push_back(cur);
  }

  cin >> K;
}

int solve(int &N, int &K, vector<int> &vec) {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push(make_pair(0, K));

  while (pq.top().second) {
    int cnt = pq.top().first;
    int cur = pq.top().second;

    pq.pop();
    pq.push(make_pair(cnt + cur, 0));

    for (int i = 0; i < N; i++) {
      pq.push(make_pair(cnt + cur % vec[i], cur / vec[i]));
    }
  }

  return pq.top().first;
}

void output(int &ans, int &test_case) {
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
    int N, K, ans;
    vector<int> vec;

    input(N, K, vec);
    ans = solve(N, K, vec);
    output(ans, test_case);
  }

  return 0;
}