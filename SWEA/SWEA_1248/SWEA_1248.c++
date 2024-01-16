#include <iostream>

using namespace std;

typedef struct Node {
  int data;
  int depth;
  Node *left;
  Node *right;
  Node *parent;
} Node;

void input(int *N, int *M, Node **tree) {
  int V, E;

  cin >> V >> E >> *N >> *M;

  *tree = (Node *)malloc(sizeof(Node) * (V + 1));

  for (int i = 1; i <= V; i++) {
    (*tree)[i].data = i;
  }

  for (int i = 0; i < E; i++) {
    int x, y;

    cin >> x >> y;

    if ((*tree)[x].left == NULL) {
      (*tree)[x].left = &(*tree)[y];
    } else {
      (*tree)[x].right = &(*tree)[y];
    }
    (*tree)[y].parent = &(*tree)[x];
  }
}

void getDepth(Node *node) {
  if (node == NULL) {
    return;
  }

  if (node->parent == NULL) {
    node->depth = 1;
  } else {
    node->depth = node->parent->depth + 1;
  }
  getDepth(node->left);
  getDepth(node->right);
}

int getParents(int N, int M, Node *tree) {
  if (tree[N].depth > tree[M].depth) {
    return getParents(tree[N].parent->data, M, tree);
  } else if (tree[N].depth < tree[M].depth) {
    return getParents(N, tree[M].parent->data, tree);
  } else {
    if (N == M) {
      return N;
    } else {
      return getParents(tree[N].parent->data, tree[M].parent->data, tree);
    }
  }
}

void inorder(int *count, Node *node) {
  if (node == NULL) {
    return;
  }

  inorder(count, node->left);
  (*count)++;
  inorder(count, node->right);
}

void output(int parent, int count, int test_case) {
  cout << '#' << test_case << ' ' << parent << ' ' << count << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int N, M, parent, count = 0;
    Node *tree;

    input(&N, &M, &tree);
    getDepth(&tree[1]);
    parent = getParents(N, M, tree);
    inorder(&count, &tree[parent]);
    output(parent, count, test_case);
  }

  return 0;
}