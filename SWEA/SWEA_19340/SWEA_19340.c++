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
