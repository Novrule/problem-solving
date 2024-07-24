#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int ans = 10000;
int N, M, L;
vector<int> vec;

void input() {
  cin >> N >> M >> L;

  for (int i = 0; i < N; i++) {
    int tmp;

    cin >> tmp;

    vec.emplace_back(tmp);
  }

  vec.push_back(0);
  vec.push_back(L);

  sort(vec.begin(), vec.end());
}

void binary_search(int left, int right) {
  while (left <= right) {
    int mid = (left + right) / 2;
    int cnt = 0;

    for (int i = 1; i < vec.size(); i++) {
      int len = vec[i] - vec[i - 1];

      if (len > mid) {
        if (len % mid == 0) {
          cnt += len / mid - 1;
        } else {
          cnt += len / mid;
        }
      }
    }

    if (cnt > M) {
      left = mid + 1;
    } else {
      right = mid - 1;
      ans = min(ans, mid);
    }
  }
}

void output() { cout << ans << '\n'; }

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  binary_search(1, L - 1);
  output();
}