#include <iostream>
#include <unordered_set>

using namespace std;

int main(void) {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while (1) {
    int N, L;
    int cnt = 0;
    unordered_set<int> s;

    cin >> N >> L;

    if (N == 0 && L == 0) {
      break;
    }

    if (N > L) {
      for (int i = 0; i < N; i++) {
        int cur;

        cin >> cur;
        s.insert(cur);
      }

      for (int i = 0; i < L; i++) {
        int cur;

        cin >> cur;

        if (!s.count(cur)) {
          cnt++;
        }
      }
    } else {
      for (int i = 0; i < L; i++) {
        int cur;

        cin >> cur;
        s.insert(cur);
      }

      for (int i = 0; i < N; i++) {
        int cur;

        cin >> cur;

        if (!s.count(cur)) {
          cnt++;
        }
      }
    }

    cout << cnt << '\n';
  }

  return 0;
}