#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

bool cmp(vector<int>& a, vector<int>& b) { return a[3] < b[3]; }

int findIndex(int agents, int xIndex) {
  for (int i = 0; i < 3; i++) {
    if (i != xIndex && i != agents) {
      return i;
    }
  }
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int ans = 0;
    int sum = 0;
    int n;

    cin >> n;

    vector<vector<int>> agents(n, vector<int>(5));
    vector<int> chosen(3, 0);

    for (int i = 0; i < n; i++) {
      int a, b, c;

      cin >> a >> b >> c;

      agents[i][0] = b + c;
      agents[i][1] = a + c;
      agents[i][2] = a + b;

      if (agents[i][0] == agents[i][1] && agents[i][1] == agents[i][2]) {
        agents[i][3] = 3;
      } else if (agents[i][0] == agents[i][1] || agents[i][1] == agents[i][2] ||
                 agents[i][0] == agents[i][2]) {
        agents[i][3] = 2;
      } else {
        agents[i][3] = 1;
      }
    }

    sort(agents.begin(), agents.end(), cmp);

    for (int i = 0; i < n; i++) {
      int minimum = min(agents[i][0], min(agents[i][1], agents[i][2]));
      int temp = -1;

      ans += minimum;

      for (int j = 0; j < 3; j++) {
        if (minimum == agents[i][j] && temp == -1) {
          chosen[j]++;
          temp = j;
          agents[i][4] = j;
        } else if (minimum == agents[i][j] && temp != -1) {
          if (chosen[temp] > chosen[j]) {
            chosen[temp]--;
            chosen[j]++;
            temp = j;
            agents[i][4] = j;
          }
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      if (chosen[i] != 0) {
        sum++;
      }
    }

    if (n < 3) {
      ans = -1;
    } else if (sum == 2) {
      int index1, index2, temp;
      int cor = INT_MAX;

      for (int i = 0; i < 3; i++) {
        if (chosen[i] == 0) {
          index1 = i;

          break;
        }
      }

      for (int i = 0; i < n; i++) {
        if (cor > agents[i][index1] - agents[i][agents[i][4]]) {
          cor = agents[i][index1] - agents[i][agents[i][4]];
          index2 = agents[i][4];
          temp = i;
        }
      }

      if (chosen[index2] == 1) {
        int cor1 = INT_MAX;
        int cor2 = INT_MAX;

        for (int i = 0; i < n; i++) {
          if (i == temp) {
            continue;
          }

          cor1 = min(cor1, agents[i][index2] - agents[i][agents[i][4]]);
        }

        for (int i = 0; i < n; i++) {
          if (i == temp) {
            continue;
          }

          cor2 = min(cor2, agents[i][index1] - agents[i][agents[i][4]]);
        }

        ans += min(cor1 + cor, cor2);
      } else {
        ans += cor;
      }
    } else if (sum == 1) {
      int temp;

      for (int i = 0; i < 3; i++) {
        if (chosen[i] != 0) {
          temp = i;

          break;
        }
      }

      int aIndex, bIndex;
      int a = (temp + 1) % 3;
      int b = (temp + 2) % 3;
      int aCor = INT_MAX;
      int bCor = INT_MAX;

      for (int i = 0; i < n; i++) {
        int aMinimum = agents[i][a] - agents[i][temp];
        int bMinimum = agents[i][b] - agents[i][temp];

        if (aCor > aMinimum) {
          aCor = aMinimum;
          aIndex = i;
        }

        if (bCor > bMinimum) {
          bCor = bMinimum;
          bIndex = i;
        }
      }

      if (aIndex == bIndex) {
        int aStay = INT_MAX;
        int bStay = INT_MAX;

        for (int i = 0; i < n; i++) {
          if (i == aIndex) {
            continue;
          }

          aStay = min(aStay, agents[i][b] - agents[i][temp]);
          bStay = min(bStay, agents[i][a] - agents[i][temp]);
        }

        aStay += aCor;
        bStay += bCor;

        ans += min(aStay, bStay);
      } else {
        ans += aCor + bCor;
      }
    }

    cout << '#' << test_case << ' ' << ans << '\n';
  }

  return 0;
}