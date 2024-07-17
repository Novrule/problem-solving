#include <iostream>

using namespace std;

int input(int &n, int &m) {
  cin >> n >> m;

  return 0;
}

int getParent(int *arr, int num) {
  if (arr[num] == num) {
    return num;
  }

  return arr[num] = getParent(arr, arr[num]);
}

int findParent(int *arr, int a, int b) {
  if (getParent(arr, a) == getParent(arr, b)) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }

  return 0;
}

int unionParent(int *arr, int a, int b) {
  arr[getParent(arr, a)] = getParent(arr, b);

  return 0;
}

int group(int n, int m) {
  int arr[n + 1];

  for (int i = 1; i <= n; i++) {
    arr[i] = i;
  }

  while (m--) {
    int cal, a, b;

    cin >> cal >> a >> b;

    if (cal) {
      findParent(arr, a, b);
    } else {
      unionParent(arr, a, b);
    }
  }

  return 0;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m;

  input(n, m);
  group(n, m);

  return 0;
}
