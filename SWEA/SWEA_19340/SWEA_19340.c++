#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
  int parent;
  int cnt;
  unordered_set<int> children;

  Node() {
    this->parent = -1;
    this->cnt = 0;
    this->children = unordered_set<int>();
  }
};

vector<int> head;
vector<Node> tree(18000);
unordered_map<int, int> index;

int compress(int mId) {
  if (!index.count(mId)) {
    index[mId] = index.size();
  }

  return index[mId];
}

void init(int N, int mId[], int mNum[]) {
  head.clear();
  tree.clear();
  tree.resize(18000);
  index.clear();

  for (int i = 0; i < N; i++) {
    int id = compress(mId[i]);

    head.push_back(id);
    tree[id].cnt = mNum[i];
  }

  return;
}

int add(int mId, int mNum, int mParent) {
  int id = compress(mId);
  int parentId = compress(mParent);
  int cnt = -1;

  if (tree[parentId].children.size() >= 3) {
    return -1;
  } else {
    tree[id].parent = parentId;
    tree[id].cnt = mNum;
    tree[parentId].children.insert(id);
    tree[parentId].cnt += mNum;
    cnt = tree[parentId].cnt;

    id = parentId;
    parentId = tree[parentId].parent;

    while (parentId != -1) {
      tree[parentId].cnt += mNum;

      id = parentId;
      parentId = tree[parentId].parent;
    }

    return cnt;
  }
}

void removeParent(int id) {
  int parentId = tree[id].parent;
  int cnt = tree[id].cnt;

  tree[parentId].children.erase(id);

  while (parentId != -1) {
    tree[parentId].cnt -= cnt;

    id = parentId;
    parentId = tree[parentId].parent;
  }

  return;
}

void removeChild(int id) {
  for (auto& child : tree[id].children) {
    removeChild(child);
  }

  tree[id] = Node();

  return;
}

int remove(int mId) {
  int id = compress(mId);

  if (tree[id].parent == -1) {
    return -1;
  } else {
    int cnt = tree[id].cnt;

    removeParent(id);
    removeChild(id);

    return cnt;
  }
}

int binarySearch(int K, int max) {
  int result = 0;
  int left = 0;
  int right = max;

  while (left <= right) {
    int mid = (left + right) / 2;
    int cnt = 0;

    for (auto& i : head) {
      if (tree[i].cnt > mid) {
        cnt += mid;
      } else {
        cnt += tree[i].cnt;
      }
    }

    if (cnt <= K) {
      result = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return result;
}

int distribute(int K) {
  int cnt = 0;
  int max = 0;

  for (auto& i : head) {
    cnt += tree[i].cnt;

    if (tree[i].cnt > max) {
      max = tree[i].cnt;
    }
  }

  if (cnt <= K) {
    return max;
  } else {
    return binarySearch(K, max);
  }
}

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int mId[], int mNum[]);
extern int add(int mId, int mNum, int mParent);
extern int remove(int mId);
extern int distribute(int K);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_DISTRIBUTE 4

static bool run() {
  int q;
  scanf("%d", &q);

  static int midArr[1000], mnumArr[1000];
  int mid, mnum, mparent, n, k;
  int cmd, ans, ret = 0;
  bool okay = false;

  for (int i = 0; i < q; ++i) {
    scanf("%d", &cmd);
    switch (cmd) {
      case CMD_INIT:
        scanf("%d", &n);
        for (int j = 0; j < n; ++j) {
          scanf("%d %d", &midArr[j], &mnumArr[j]);
        }
        init(n, midArr, mnumArr);
        okay = true;
        break;
      case CMD_ADD:
        scanf("%d %d %d %d", &mid, &mnum, &mparent, &ans);
        ret = add(mid, mnum, mparent);
        if (ans != ret) okay = false;
        break;
      case CMD_REMOVE:
        scanf("%d %d", &mid, &ans);
        ret = remove(mid);
        if (ans != ret) okay = false;
        break;
      case CMD_DISTRIBUTE:
        scanf("%d %d", &k, &ans);
        ret = distribute(k);
        if (ans != ret) okay = false;
        break;
      default:
        okay = false;
        break;
    }
  }
  return okay;
}

int main() {
  setbuf(stdout, NULL);
  // freopen("sample_input.txt", "r", stdin);

  int T, MARK;
  scanf("%d %d", &T, &MARK);

  for (int tc = 1; tc <= T; tc++) {
    int score = run() ? MARK : 0;
    printf("#%d %d\n", tc, score);
  }

  return 0;
}