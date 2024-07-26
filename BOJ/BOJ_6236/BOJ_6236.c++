#include <iostream>
#include <vector>

using namespace std;

int res = 0;
int N, M;
vector<int> vec;

void input() {
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    int tmp;

    cin >> tmp;
    vec.emplace_back(tmp);
  }
}

bool check(int mid) {
  int tmp = mid;
  int cnt = 1;

  for (int i = 0; i < N; i++) {
    if (vec[i] <= mid) {
      mid -= vec[i];
    } else {
      mid = tmp;
      cnt++;

      if (vec[i] > mid) {
        return false;
      } else {
        mid -= vec[i];
      }
    }
  }

  return cnt <= M;
}

void binary_search() {
  int left = 1;
  int right = 1000000000;

  while (left <= right) {
    int mid = (left + right) / 2;

    if (check(mid)) {
      res = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
}

void output() { cout << res << '\n'; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  binary_search();
  output();
}