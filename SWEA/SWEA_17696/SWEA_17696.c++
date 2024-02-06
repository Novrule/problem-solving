#include <vector>

using namespace std;

struct Result {
  int top;
  int count;
};

long long total;
int width;
vector<int> minTree;
vector<int> maxTree;
vector<int> lazy;

void init(int C) {
  total = 0;
  width = C;

  minTree.clear();
  maxTree.clear();
  lazy.clear();

  minTree.resize(C * 4);
  maxTree.resize(C * 4);
  lazy.resize(C * 4);
}

void updateLazy(int index, int left, int right) {
  if (lazy[index] != 0) {
    minTree[index] += lazy[index];
    maxTree[index] += lazy[index];

    if (left != right) {
      lazy[index * 2] += lazy[index];
      lazy[index * 2 + 1] += lazy[index];
    }

    lazy[index] = 0;
  }
}

void updateTree(int index, int left, int right, int start, int end, int diff) {
  updateLazy(index, left, right);

  if (left > end || right < start) {
    return;
  } else if (start <= left && right <= end) {
    minTree[index] += diff;
    maxTree[index] += diff;

    if (left != right) {
      lazy[index * 2] += diff;
      lazy[index * 2 + 1] += diff;
    }
  } else {
    int mid = (left + right) / 2;

    updateTree(index * 2, left, mid, start, end, diff);
    updateTree(index * 2 + 1, mid + 1, right, start, end, diff);

    minTree[index] = min(minTree[index * 2], minTree[index * 2 + 1]);
    maxTree[index] = max(maxTree[index * 2], maxTree[index * 2 + 1]);
  }
}

Result dropBlocks(int mCol, int mHeight, int mLength) {
  Result ret;

  total += mHeight * mLength;

  updateTree(1, 1, width, mCol + 1, mCol + mLength, mHeight);

  int min = minTree[1];
  int max = maxTree[1];

  ret.top = max - min;
  ret.count = (total - static_cast<long long>(min * width)) % 1000000;

  return ret;
}
