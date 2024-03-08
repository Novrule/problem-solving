#include <iostream>
#include <set>

using namespace std;

struct Node {
  int parent;
  set<int> child;

  Node() {
    parent = -1;
    child.clear();
  }
};

int ans = 0;
int root = 0;
int N, M;
Node tree[50];

void input() {
  cin >> N;

  for (int i = 0; i < N; i++) {
    int parent;

    cin >> parent;

    tree[i].parent = parent;

    if (parent == -1) {
      root = i;
    } else {
      tree[parent].child.insert(i);
    }
  }

  cin >> M;
}

void dfs(int node) {
  if (tree[node].child.empty()) {
    ans++;
  } else {
    for (auto child : tree[node].child) {
      dfs(child);
    }
  }
}

void getAns() {
  int parent = tree[M].parent;

  if (parent == -1) {
    return;
  } else {
    tree[parent].child.erase(M);
    dfs(root);
  }
}

void output() { cout << ans << '\n'; }

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  input();
  getAns();
  output();

  return 0;
}
