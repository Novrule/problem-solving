#include <iostream>
#include <string>

using namespace std;

typedef struct Node {
  string data;
  Node *left;
  Node *right;
} Node;

bool isOperator(string data) {
  return data == "+" || data == "-" || data == "*" || data == "/";
}

void input(Node **tree) {
  int N;

  cin >> N;

  *tree = (Node *)malloc(sizeof(Node) * (N + 1));

  for (int i = 0; i < N; i++) {
    int index;
    string data;

    cin >> index >> data;

    (*tree)[index].data = data;

    if (isOperator(data)) {
      int left, right;

      cin >> left >> right;

      (*tree)[index].left = &(*tree)[left];
      (*tree)[index].right = &(*tree)[right];
    }
  }
}

double caculate(double a, string op, double b) {
  if (op == "+") {
    return a + b;
  } else if (op == "-") {
    return a - b;
  } else if (op == "*") {
    return a * b;
  } else if (op == "/") {
    return a / b;
  }
}

double postorder(Node *node) {
  if (!isOperator(node->data)) {
    return stod(node->data);
  }

  return caculate(postorder(node->left), node->data, postorder(node->right));
}

void output(int test_case, Node *tree) {
  cout << '#' << test_case << ' ';
  cout << static_cast<int>(postorder(&tree[1])) << '\n';
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