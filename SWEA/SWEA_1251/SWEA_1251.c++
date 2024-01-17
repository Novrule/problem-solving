#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void input(int &N, double &E, vector<pair<int, int>> &island) {
  cin >> N;

  island.resize(N);

  for (int i = 0; i < N; i++) {
    cin >> island[i].first;
  }

  for (int i = 0; i < N; i++) {
    cin >> island[i].second;
  }

  cin >> E;
}

inline long long getDist(int &a, int &b, vector<pair<int, int>> &island) {
  long long x = static_cast<long long>(island[a].first - island[b].first);
  long long y = static_cast<long long>(island[a].second - island[b].second);

  return x * x + y * y;
}

long long prim(int &N, long long &ans, vector<pair<int, int>> &island) {
  int cur = 0;
  long long temp;
  vector<long long> dist(N, LLONG_MAX);
  vector<bool> visit(N, false);

  visit[cur] = true;
  ans = 0;

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N; j++) {
      dist[j] = min(dist[j], getDist(cur, j, island));
    }

    temp = LLONG_MAX;

    for (int j = 0; j < N; j++) {
      if (visit[j]) {
        continue;
      }

      if (dist[j] < temp) {
        temp = dist[j];
        cur = j;
      }
    }

    ans += temp;
    visit[cur] = true;
  }
}

void output(double &E, long long &ans, int &test_case) {
  long long result = static_cast<long long>(ans * E + 0.5);

  cout << "#" << test_case << " " << result << "\n";
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int N;
    double E;
    long long ans = 0;
    vector<pair<int, int>> island;

    input(N, E, island);
    prim(N, ans, island);
    output(E, ans, test_case);
  }

  return 0;
}