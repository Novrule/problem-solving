#include <unordered_map>

#define MAX 10000

using namespace std;

struct Node {
  int parent;
  int total;
  int cnt;
  int left;
  int right;

  Node() {
    parent = -1;
    total = 0;
    cnt = 0;
    left = -1;
    right = -1;
  }

  Node(int parent, int cnt) {
    this->parent = parent;
    this->total = cnt;
    this->cnt = cnt;
    this->left = -1;
    this->right = -1;
  }
};

int root, total, m, k;
Node tree[MAX];
unordered_map<int, int> compress;

int compressId(int mId) {
  if (!compress.count(mId)) {
    compress[mId] = compress.size();
  }

  return compress[mId];
}

void init(int mId, int mNum) {
  for (int i = 0; i < MAX; i++) {
    tree[i] = Node();
  }

  compress.clear();

  int id = compressId(mId);

  root = id;

  tree[id].total = mNum;
  tree[id].cnt = mNum;

  return;
}

int add(int mId, int mNum, int mParent) {
  int parentId = compressId(mParent);

  if (tree[parentId].left != -1 && tree[parentId].right != -1) {
    return -1;
  } else {
    int id = compressId(mId);
    int ans = tree[parentId].total + mNum;

    if (tree[parentId].left == -1) {
      tree[parentId].left = id;
    } else {
      tree[parentId].right = id;
    }

    tree[id] = Node(parentId, mNum);

    while (parentId != -1) {
      tree[parentId].total += mNum;
      parentId = tree[parentId].parent;
    }

    return ans;
  }
}

void removeId(int id) {
  if (tree[id].left != -1) {
    removeId(tree[id].left);
  }

  if (tree[id].right != -1) {
    removeId(tree[id].right);
  }

  tree[id] = Node();
}

int remove(int mId) {
  int id = compressId(mId);

  if (tree[id].parent == -1) {
    return -1;
  } else {
    int parentId = tree[id].parent;
    int ans = tree[id].total;

    if (tree[parentId].left == id) {
      tree[parentId].left = -1;
    } else {
      tree[parentId].right = -1;
    }

    while (parentId != -1) {
      tree[parentId].total -= ans;
      parentId = tree[parentId].parent;
    }

    removeId(id);

    return ans;
  }
}

int solve(int id) {
  if (total > m || tree[id].cnt > k) {
    total = m + 1;

    return 0;
  }

  int temp = tree[id].cnt;
  int left = 0;
  int right = 0;

  if (tree[id].left != -1) {
    left = solve(tree[id].left);
  }

  if (tree[id].right != -1) {
    right = solve(tree[id].right);
  }

  if (total <= m) {
    if (temp + left > k) {
      total++;
      left = 0;
    }

    if (temp + right > k) {
      total++;
      right = 0;
    }

    if (temp + left + right > k) {
      total++;

      if (left > right) {
        left = 0;
      } else {
        right = 0;
      }
    }

    return temp + left + right;
  }

  return 0;
}

int reorganize(int M, int K) {
  total = 1;
  m = M;
  k = K;

  solve(root);

  if (total <= m) {
    return 1;
  } else {
    return 0;
  }
}