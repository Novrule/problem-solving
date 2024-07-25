#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int N;
int arr[100100];
int tree[400400];

int init(int index, int left, int right) {
  if (left == right) {
    return tree[index] = left;
  }

  int mid = (left + right) / 2;
  int leftMin = init(index * 2, left, mid);
  int rightMin = init(index * 2 + 1, mid + 1, right);

  return tree[index] = (arr[leftMin] < arr[rightMin]) ? leftMin : rightMin;
}

int query(int index, int left, int right, int start, int end) {
  if (left >= start && right <= end) {
    return tree[index];
  }

  if (left > end || right < start) {
    return -1;
  }

  int mid = (left + right) / 2;
  int leftMin = query(index * 2, left, mid, start, end);
  int rightMin = query(index * 2 + 1, mid + 1, right, start, end);

  if (leftMin == -1) {
    return rightMin;
  }
  if (rightMin == -1) {
    return leftMin;
  } else {
    return (arr[leftMin] < arr[rightMin]) ? leftMin : rightMin;
  }
}

void input() {
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
}

long long solve(int left, int right, int n) {
  int minimum = query(1, 0, n - 1, left, right);
  long long res = (long long)(right - left + 1) * (long long)arr[minimum];

  if (left < minimum) {
    long long tmp = solve(left, minimum - 1, n);
    if (tmp > res) {
      res = tmp;
    }
  }

  if (minimum < right) {
    long long tmp = solve(minimum + 1, right, n);
    if (tmp > res) {
      res = tmp;
    }
  }

  return res;
}

void output() { cout << solve(0, N - 1, N) << '\n'; }

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  input();
  init(1, 0, N - 1);
  output();

  return 0;
}