#include <iostream>

using namespace std;

int N;
int inorder[100001];
int postorder[100001];
int index[100001];

void input() {
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> inorder[i];

    index[inorder[i]] = i;
  }

  for (int i = 1; i <= N; i++) {
    cin >> postorder[i];
  }
}

void solve(int start_inorder, int end_inorder, int start_postorder,
           int end_postorder) {
  if (start_inorder > end_inorder || start_postorder > end_postorder) {
    return;
  }

  int root = postorder[end_postorder];
  int root_index = index[root];
  int split = root_index - start_inorder;

  cout << root << " ";

  solve(start_inorder, root_index - 1, start_postorder,
        start_postorder + split - 1);
  solve(root_index + 1, end_inorder, start_postorder + split,
        end_postorder - 1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve(1, N, 1, N);
}
