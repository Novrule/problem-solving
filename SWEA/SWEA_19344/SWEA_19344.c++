#include <algorithm>
#include <cstring>

using namespace std;

constexpr int MAXIMUM = 1 << 17;

int n;
int maxTree[MAXIMUM << 1];

void init(int N) {
  n = N;

  memset(maxTree, 0, sizeof maxTree);
}

int getMaximum() {
  int cur = 1;

  while (cur < MAXIMUM) {
    if (maxTree[cur * 2] < maxTree[cur * 2 + 1]) {
      cur = cur * 2 + 1;
    } else {
      cur = cur * 2;
    }
  }

  return cur - MAXIMUM;
}

int getLeft(int index, int cur = 1, int left = 0, int right = MAXIMUM - 1) {
  if (right < index) {
    return n;
  }

  if (index <= left) {
    if (maxTree[cur] <= maxTree[MAXIMUM + index]) {
      return n;
    }

    while (cur < MAXIMUM) {
      if (maxTree[cur * 2] > maxTree[MAXIMUM + index])
        cur = cur * 2;
      else
        cur = 2 * cur + 1;
    }

    return cur - MAXIMUM;
  }

  int mid = (left + right) / 2;
  int temp = getLeft(index, cur * 2, left, mid);

  if (temp != n) {
    return temp;
  } else {
    return getLeft(index, cur * 2 + 1, mid + 1, right);
  }
}

int getRight(int index, int cur = 1, int left = 0, int right = MAXIMUM - 1) {
  if (index < left) {
    return -1;
  }

  if (right <= index) {
    if (maxTree[cur] <= maxTree[MAXIMUM + index]) {
      return -1;
    }

    while (cur < MAXIMUM) {
      if (maxTree[cur * 2 + 1] > maxTree[MAXIMUM + index]) {
        cur = cur * 2 + 1;
      } else {
        cur = cur * 2;
      }
    }

    return cur - MAXIMUM;
  }

  int mid = (left + right) / 2;
  int temp = getRight(index, cur * 2 + 1, mid + 1, right);

  if (temp != -1) {
    return temp;
  } else {
    return getRight(index, cur * 2, left, mid);
  }
}

int getAns() {
  int ans = 0;
  int mid = getMaximum();

  for (int i = 0; i < mid;) {
    int next = min(getLeft(i), mid) - 1;

    ans += maxTree[MAXIMUM + i] * (next - i + 1);
    i = next + 1;
  }

  for (int i = n - 1; i >= mid;) {
    int next = max(getRight(i) + 1, mid);

    ans += maxTree[MAXIMUM + i] * (i - next + 1);
    i = next - 1;
  }

  return ans;
}

int stock(int mLoc, int mBox) {
  mLoc += MAXIMUM - 1;
  maxTree[mLoc] += mBox;

  while (mLoc >>= 1) {
    maxTree[mLoc] = max(maxTree[mLoc * 2], maxTree[mLoc * 2 + 1]);
  }

  return getAns();
}

int ship(int mLoc, int mBox) {
  mLoc += MAXIMUM - 1;
  maxTree[mLoc] -= mBox;

  while (mLoc >>= 1) {
    maxTree[mLoc] = max(maxTree[mLoc * 2], maxTree[mLoc * 2 + 1]);
  }

  return getAns();
}

int getHeight(int mLoc) {
  mLoc += MAXIMUM - 1;

  return maxTree[mLoc];
}