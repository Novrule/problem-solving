#include <iostream>

using namespace std;

int N;
int arr[1000], lis[1000];

void input() {
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
}

int binary_search(int left, int right, int target) {
  int mid;

  while (left < right) {
    mid = (left + right) / 2;

    if (lis[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return right;
}

void solve() {
  int idx = 0;

  lis[0] = arr[0];

  for (int i = 1; i < N; i++) {
    if (lis[idx] < arr[i]) {
      lis[++idx] = arr[i];
    } else {
      lis[binary_search(0, idx, arr[i])] = arr[i];
    }
  }

  cout << idx + 1 << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve();
}