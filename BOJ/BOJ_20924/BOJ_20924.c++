#include <iostream>
#include <vector>

using namespace std;

int giga_node = 0;
int giga_prev = 0;
int max_leaf = 0;
int N, R;
vector<int> tree;
vector<vector<pair<int, int>>> vec;

void dfs(int cur, int prev) {
  for (int i = 0; i < vec[cur].size(); i++) {
    if (vec[cur][i].first == prev) {
      continue;
    }

    tree[cur]++;
    dfs(vec[cur][i].first, cur);
  }
}

int find_giga(int cur, int prev, int total) {
  if (tree[cur] > 1) {
    giga_node = cur;
    giga_prev = prev;

    return total;
  };

  for (int i = 0; i < vec[cur].size(); i++) {
    if (vec[cur][i].first == prev) {
      continue;
    }

    return find_giga(vec[cur][i].first, cur, total + vec[cur][i].second);
  }

  return total;
}

void find_leaf(int cur, int prev, int total) {
  max_leaf = max(max_leaf, total);

  for (int i = 0; i < vec[cur].size(); i++) {
    if (vec[cur][i].first == prev) {
      continue;
    }

    find_leaf(vec[cur][i].first, cur, total + vec[cur][i].second);
  }
}

void input() {
  int a, b, c;

  cin >> N >> R;

  tree.resize(N + 1, 0);
  vec.resize(N + 1, vector<pair<int, int>>());

  for (int i = 0; i < N - 1; i++) {
    cin >> a >> b >> c;

    vec[a].push_back({b, c});
    vec[b].push_back({a, c});
  }
}

void output() {
  dfs(R, 0);
  cout << find_giga(R, 0, 0) << " ";

  find_leaf(giga_node, giga_prev, 0);
  cout << max_leaf;
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  output();

  return 0;
}