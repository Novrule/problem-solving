#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    int N;
    priority_queue<int> pq;

    cin >> N;

    cout << '#' << test_case << ' ';

    for (int i = 0; i < N; i++) {
      int cur;

      cin >> cur;

      if (cur == 1) {
        int x;

        cin >> x;

        pq.push(x);
      } else {
        if (pq.empty()) {
          cout << "-1" << ' ';
        } else {
          cout << pq.top() << ' ';
          pq.pop();
        }
      }
    }

    cout << '\n';
  }

  return 0;
}