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

  for (test_case = 1; test_case <= T; test_case++) {
    int N, middle, ans = 0;
    priority_queue<int> front;
    priority_queue<int, vector<int>, greater<int>> back;

    cin >> N >> middle;

    for (int i = 0; i < N; i++) {
      int X, Y;

      cin >> X >> Y;

      if (X < middle) {
        front.push(X);
      } else {
        back.push(X);
      }

      if (Y < middle) {
        front.push(Y);
      } else {
        back.push(Y);
      }

      if (front.size() > back.size()) {
        back.push(middle);
        middle = front.top();
        front.pop();
      } else if (front.size() < back.size()) {
        front.push(middle);
        middle = back.top();
        back.pop();
      }

      ans = (ans + middle) % 20171109;
    }

    cout << '#' << test_case << ' ' << ans << '\n';
  }

  return 0;
}