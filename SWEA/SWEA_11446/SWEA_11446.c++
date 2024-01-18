#include <iostream>
#include <vector>

using namespace std;

void input(long long &N, long long &M, long long &maximum,
           vector<long long> &candy) {
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    long long temp;

    if (temp > maximum) {
      maximum = temp;
    }

    cin >> temp;
    candy.push_back(temp);
  }
}

long long solve(long long &N, long long &M, long long &maximum,
                vector<long long> &candy) {
  long long ans = 0;
  long long left = 1;
  long long right = maximum;

  while (left <= right) {
    long long mid = left + (right - left) / 2;
    long long sum = 0;

    for (int i = 0; i < candy.size(); i++) {
      sum += candy[i] / mid;
    }

    if (sum >= M) {
      ans = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return ans;
}

void output(long long ans, int test_case) {
  cout << '#' << test_case << " " << ans << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    long long N, M, maximum, ans;
    vector<long long> candy;

    input(N, M, maximum, candy);
    ans = solve(N, M, maximum, candy);
    output(ans, test_case);
  }

  return 0;
}