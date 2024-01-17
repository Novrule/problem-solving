#include <iostream>
#include <vector>

using namespace std;

int findParent(int x, vector<int>& parent) {
  if (parent[x] < 0) {
    return x;
  }

  return parent[x] = findParent(parent[x], parent);
}

void unionParent(int x, int y, vector<int>& parent) {
  int aParent = findParent(x, parent);
  int bParent = findParent(y, parent);

  if (aParent < bParent) {
    parent[aParent] += parent[bParent];
    parent[bParent] = aParent;
  } else if (bParent < aParent) {
    parent[bParent] += parent[aParent];
    parent[aParent] = bParent;
  }
}

void input(vector<int>& parent) {
  int N, M;

  cin >> N >> M;

  parent.resize(N + 1, -1);

  for (int i = 0; i < M; i++) {
    int x, y;

    cin >> x >> y;
    unionParent(x, y, parent);
  }
}

void output(int test_case, vector<int>& parent) {
  int cnt = 0;

  for (int i = 1; i < parent.size(); i++) {
    if (parent[i] < 0) {
      cnt++;
    }
  }

  cout << '#' << test_case << ' ' << cnt << '\n';
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    vector<int> parent;

    input(parent);
    output(test_case, parent);
  }

  return 0;
}