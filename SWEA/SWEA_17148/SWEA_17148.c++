#include <vector>

using namespace std;

int size, sum;
vector<int> tree;
vector<int> type;
vector<int> time;

int initTree(int index, int left, int right) {
  if (left == right) {
    return tree[index] = time[left];
  }

  int mid = (left + right) / 2;
  int leftTree = initTree(index * 2, left, mid);
  int rightTree = initTree(index * 2 + 1, mid + 1, right);

  return tree[index] = leftTree + rightTree;
}

int updateValue(int index, int left, int right, int target, int value) {
  if (target < left || right < target) {
    return tree[index];
  }

  if (left == right) {
    return tree[index] = value;
  }

  int mid = (left + right) / 2;
  int leftTree = updateValue(index * 2, left, mid, target, value);
  int rightTree = updateValue(index * 2 + 1, mid + 1, right, target, value);

  return tree[index] = leftTree + rightTree;
}

int updateRatio(int index, int left, int right, int target, int mRatio256) {
  if (target < left || right < target) {
    return tree[index];
  }

  if (left == right) {
    tree[index] = tree[index] * mRatio256 / 256;
    sum += tree[index];

    return tree[index];
  }

  int mid = (left + right) / 2;
  int leftTree = updateRatio(index * 2, left, mid, target, mRatio256);
  int rightTree = updateRatio(index * 2 + 1, mid + 1, right, target, mRatio256);

  return tree[index] = leftTree + rightTree;
}

int queryTree(int index, int left, int right, int start, int end) {
  if (end < left || right < start) {
    return 0;
  }

  if (start <= left && right <= end) {
    return tree[index];
  }

  int mid = (left + right) / 2;
  int leftTree = queryTree(index * 2, left, mid, start, end);
  int rightTree = queryTree(index * 2 + 1, mid + 1, right, start, end);

  return leftTree + rightTree;
}

void init(int N, int M, int mType[], int mTime[]) {
  size = N;

  tree.clear();
  tree.resize(size * 4);
  type.clear();
  time.clear();

  type.push_back(0);
  time.push_back(0);

  for (int i = 0; i < N; i++) {
    type.push_back(mType[i]);
    time.push_back(mTime[i]);
  }

  initTree(1, 1, size);
}

void destroy() {}

void update(int mID, int mNewTime) {
  updateValue(1, 1, size, mID + 1, mNewTime);
}

int updateByType(int mTypeID, int mRatio256) {
  sum = 0;

  for (int i = 1; i < size; i++) {
    if (type[i] == mTypeID) {
      updateRatio(1, 1, size, i, mRatio256);
    }
  }

  return sum;
}

int calculate(int mA, int mB) {
  if (mA < mB) {
    return queryTree(1, 1, size, mA + 1, mB);
  } else {
    return queryTree(1, 1, size, mB + 1, mA);
  }
}