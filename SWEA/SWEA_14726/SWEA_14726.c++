#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int n, q;
vector<int> arr;
vector<int> minTree;
vector<int> maxTree;

void input() {
  arr.clear();
  arr.push_back(0);
  minTree.clear();
  maxTree.clear();

  cin >> n >> q;

  minTree.resize(n * 4);
  maxTree.resize(n * 4);

  for (int i = 0; i < n; i++) {
    int temp;

    cin >> temp;
    arr.push_back(temp);
  }
}

int initMin(int index, int left, int right) {
  if (left == right) {
    return minTree[index] = arr[left];
  }

  int mid = (left + right) / 2;
  int leftMin = initMin(index * 2, left, mid);
  int rightMin = initMin(index * 2 + 1, mid + 1, right);

  return minTree[index] = min(leftMin, rightMin);
}

int initMax(int index, int left, int right) {
  if (left == right) {
    return maxTree[index] = arr[left];
  }

  int mid = (left + right) / 2;
  int leftMax = initMax(index * 2, left, mid);
  int rightMax = initMax(index * 2 + 1, mid + 1, right);

  return maxTree[index] = max(leftMax, rightMax);
}

int updateMin(int index, int left, int right, int target, int value) {
  if (left > target || right < target) {
    return minTree[index];
  }

  if (left == right) {
    return minTree[index] = value;
  }

  int mid = (left + right) / 2;
  int leftMin = updateMin(index * 2, left, mid, target, value);
  int rightMin = updateMin(index * 2 + 1, mid + 1, right, target, value);

  return minTree[index] = min(leftMin, rightMin);
}

int updateMax(int index, int left, int right, int target, int value) {
  if (left > target || right < target) {
    return maxTree[index];
  }

  if (left == right) {
    return maxTree[index] = value;
  }

  int mid = (left + right) / 2;
  int leftMax = updateMax(index * 2, left, mid, target, value);
  int rightMax = updateMax(index * 2 + 1, mid + 1, right, target, value);

  return maxTree[index] = max(leftMax, rightMax);
}

int queryMin(int index, int left, int right, int start, int end) {
  if (left >= start && right <= end) {
    return minTree[index];
  }

  if (left > end || right < start) {
    return INT_MAX;
  }

  int mid = (left + right) / 2;
  int leftMin = queryMin(index * 2, left, mid, start, end);
  int rightMin = queryMin(index * 2 + 1, mid + 1, right, start, end);

  return min(leftMin, rightMin);
}

int queryMax(int index, int left, int right, int start, int end) {
  if (left >= start && right <= end) {
    return maxTree[index];
  }

  if (left > end || right < start) {
    return INT_MIN;
  }

  int mid = (left + right) / 2;
  int leftMax = queryMax(index * 2, left, mid, start, end);
  int rightMax = queryMax(index * 2 + 1, mid + 1, right, start, end);

  return max(leftMax, rightMax);
}

int output(int test_case) {
  cout << '#' << test_case;

  initMin(1, 1, n);
  initMax(1, 1, n);

  for (int i = 0; i < q; i++) {
    int a, b, c;

    cin >> a >> b >> c;

    if (a == 1) {
      int minVal = queryMin(1, 1, n, b + 1, c);
      int maxVal = queryMax(1, 1, n, b + 1, c);

      cout << ' ' << maxVal - minVal;
    } else {
      updateMin(1, 1, n, b + 1, c);
      updateMax(1, 1, n, b + 1, c);
    }
  }

  cout << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    input();
    output(test_case);
  }

  return 0;
}