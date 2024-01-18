#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void input(int &c1, int &c2, vector<int> &cow, vector<int> &horse) {
  int N, M;

  cin >> N >> M >> c1 >> c2;

  for (int i = 0; i < N; i++) {
    int temp;

    cin >> temp;
    cow.push_back(temp);
  }

  for (int i = 0; i < M; i++) {
    int temp;

    cin >> temp;
    horse.push_back(temp);
  }
}

void solve(int &minimum, int &cnt, vector<int> &cow, vector<int> &horse) {
  sort(cow.begin(), cow.end());

  for (int i = 0; i < horse.size(); i++) {
    int left = 0;
    int right = cow.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;

      if (abs(horse[i] - cow[mid]) < minimum) {
        minimum = abs(horse[i] - cow[mid]);
        cnt = 1;
      } else if (abs(horse[i] - cow[mid]) == minimum) {
        cnt++;
      }

      if (horse[i] > cow[mid]) {
        left = mid + 1;
      } else if (horse[i] < cow[mid]) {
        right = mid - 1;
      } else {
        break;
      }
    }
  }
}

void output(int minimum, int cnt, int c1, int c2, int test_case) {
  minimum += abs(c1 - c2);

  cout << '#' << test_case << ' ' << minimum << ' ' << cnt << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int c1, c2, ans;
    int minimum = INT_MAX;
    int cnt = 0;
    vector<int> cow, horse;

    input(c1, c2, cow, horse);
    solve(minimum, cnt, cow, horse);
    output(minimum, cnt, c1, c2, test_case);
  }

  return 0;
}