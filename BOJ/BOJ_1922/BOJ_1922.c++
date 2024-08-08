#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int N, M, ans;
int parent[1001];
vector<pair<int, pair<int, int>>> graph;

void input() {
  cin >> N >> M;

  graph.resize(M);

  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;

    graph[i] = {c, {a, b}};
  }

  sort(graph.begin(), graph.end());

  for (int i = 1; i <= N; i++) {
    parent[i] = i;
  }
}

int get_parent(int num) {
  if (num == parent[num]) {
    return num;
  }

  return parent[num] = get_parent(parent[num]);
}

void union_parent(int a, int b) {
  a = get_parent(a);
  b = get_parent(b);

  if (a != b) {
    parent[a] = b;
  }
}

bool find_parent(int a, int b) {
  a = get_parent(a);
  b = get_parent(b);

  if (a == b) {
    return true;
  } else {
    return false;
  }
}

void solve() {
  for (int i = 0; i < M; i++) {
    int cost = graph[i].first;
    int a = graph[i].second.first;
    int b = graph[i].second.second;

    if (!find_parent(a, b)) {
      ans += cost;
      union_parent(a, b);
    }
  }
}

void output() { cout << ans << '\n'; }

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve();
  output();

  return 0;
}