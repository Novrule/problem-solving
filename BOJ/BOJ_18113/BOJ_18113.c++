#include <iostream>
#include <vector>

using namespace std;

int N, K, M;
vector<int> v;

void input() {
  cin >> N >> K >> M;

  for (int i = 0; i < N; i++) {
    int tmp;

    cin >> tmp;

    if (tmp <= K) {
      tmp = 0;
    } else if (tmp < 2 * K) {
      tmp -= K;
    } else {
      tmp -= 2 * K;
    }

    v.push_back(tmp);
  }
}

int binary_search(int left, int right) {
  int ans = -1;

  while (left <= right) {
    int mid = (left + right) / 2;
    int cnt = 0;

    for (int i = 0; i < N; i++) {
      cnt += v[i] / mid;
    }

    if (cnt < M) {
      right = mid - 1;
    } else {
      left = mid + 1;
      ans = mid;
    }
  }

  return ans;
}

void output() { cout << binary_search(1, 1e9) << '\n'; }

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  output();

  return 0;
}