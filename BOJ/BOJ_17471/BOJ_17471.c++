#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int ans = 1000000000;
int N;
int population[11];
bool map[11][11];
bool check[11];
bool visit[11];

void input() {
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> population[i];
  }

  for (int i = 1; i <= N; i++) {
    int cur;

    cin >> cur;

    for (int j = 0; j < cur; j++) {
      int tmp;

      cin >> tmp;

      map[i][tmp] = true;
      map[tmp][i] = true;
    }
  }
}

bool bfs(vector<int> vec, bool flag) {
  int cnt = 1;
  queue<int> q;

  memset(visit, false, sizeof(visit));

  visit[vec[0]] = true;
  q.push(vec[0]);

  while (!q.empty()) {
    int tmp = q.front();

    q.pop();

    for (int i = 1; i <= N; i++) {
      if (map[tmp][i] == true && check[i] == flag && visit[i] == false) {
        visit[i] = true;
        q.push(i);
        cnt++;
      }
    }
  }

  if (vec.size() == cnt) {
    return true;
  } else {
    return false;
  }
}

void calculate_group() {
  int group_a = 0;
  int group_b = 0;
  int res;

  for (int i = 1; i <= N; i++) {
    if (check[i] == true) {
      group_a += population[i];
    } else {
      group_b += population[i];
    }
  }

  res = abs(group_a - group_b);
  ans = min(ans, res);
}

bool check_group() {
  vector<int> a, b;

  for (int i = 1; i <= N; i++) {
    if (check[i] == true) {
      a.push_back(i);
    } else {
      b.push_back(i);
    }
  }

  if (bfs(a, true) != true) {
    return false;
  }

  if (bfs(b, false) != true) {
    return false;
  }

  return true;
}

void dfs(int x, int cnt) {
  if (cnt >= 1) {
    if (check_group() == true) {
      calculate_group();
    }
  }

  if (cnt == N - 1) {
    return;
  }

  for (int i = x; i <= N; i++) {
    if (check[i] == true) {
      continue;
    }

    check[i] = true;
    dfs(i, cnt + 1);
    check[i] = false;
  }
}

void output() {
  if (ans == 1000000000) {
    cout << -1;
  } else {
    cout << ans;
  }
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  dfs(1, 0);
  output();

  return 0;
}
