#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void input(int &p, vector<int> &study, vector<int> &gap) {
  int n;
  int dayOff = 0;

  cin >> n >> p;

  for (int i = 0; i < n; i++) {
    int temp;

    cin >> temp;
    study.push_back(temp);

    if (i == 0) {
      gap.push_back(dayOff);
    } else {
      dayOff += study[i] - study[i - 1] - 1;

      gap.push_back(dayOff);
    }
  }
}

int solve(int &p, vector<int> &study, vector<int> &gap) {
  int ans = INT_MIN;

  for (int i = 0; i < gap.size(); i++) {
    int left = i;
    int right = gap.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;
      int dayOff = gap[mid] - gap[i];

      if (dayOff > p) {
        right = mid - 1;
      } else {
        ans = max(ans, study[mid] - study[i] + 1 + p - dayOff);
        left = mid + 1;
      }
    }
  }

  return ans;
}

void output(int &ans, int &test_case) {
  cout << '#' << test_case << ' ' << ans << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    int p, ans;
    vector<int> study, gap;

    input(p, study, gap);
    ans = solve(p, study, gap);
    output(ans, test_case);
  }

  return 0;
}