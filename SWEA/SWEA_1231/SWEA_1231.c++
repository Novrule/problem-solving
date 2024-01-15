#include <iostream>

using namespace std;

typedef struct Node {
  char data;
  Node *left;
  Node *right;
} Node;

void input(Node **tree) {
  int N;

  cin >> N;

  *tree = (Node *)malloc(sizeof(Node) * (N + 1));

  for (int i = 0; i < N; i++) {
    int index;
    char data;

    cin >> index >> data;

    (*tree)[index].data = data;

    if (index * 2 <= N) {
      int left;

      cin >> left;

      (*tree)[index].left = &(*tree)[left];
    }

    if (index * 2 + 1 <= N) {
      int right;

      cin >> right;

      (*tree)[index].right = &(*tree)[right];
    }
  }
}

void inorder(Node *node) {
  if (node == NULL) {
    return;
  }

  inorder(node->left);
  cout << node->data;
  inorder(node->right);
}

void output(int test_case, Node *tree) {
  cout << '#' << test_case << ' ';
  inorder(&tree[1]);
  cout << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++) {
    Node *tree;

    input(&tree);
    output(test_case, tree);
  }

  return 0;
}