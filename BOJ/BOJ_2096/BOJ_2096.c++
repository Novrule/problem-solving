#include <algorithm>
#include <iostream>

using namespace std;

int N;
int input[3] = {
    0,
};
int min_arr[3] = {
    0,
};
int max_arr[3] = {
    0,
};

void solve() {
  int tmp_0, tmp_1, tmp_2;

  cin >> N;

  cin >> max_arr[0] >> max_arr[1] >> max_arr[2];
  min_arr[0] = max_arr[0];
  min_arr[1] = max_arr[1];
  min_arr[2] = max_arr[2];

  for (int i = 1; i < N; i++) {
    cin >> input[0] >> input[1] >> input[2];

    tmp_0 = max_arr[0];
    tmp_1 = max_arr[1];
    tmp_2 = max_arr[2];

    max_arr[0] = max(tmp_0, tmp_1) + input[0];
    max_arr[1] = max(tmp_0, max(tmp_1, tmp_2)) + input[1];
    max_arr[2] = max(tmp_1, tmp_2) + input[2];

    tmp_0 = min_arr[0];
    tmp_1 = min_arr[1];
    tmp_2 = min_arr[2];

    min_arr[0] = min(tmp_0, tmp_1) + input[0];
    min_arr[1] = min(tmp_0, min(tmp_1, tmp_2)) + input[1];
    min_arr[2] = min(tmp_1, tmp_2) + input[2];
  }

  cout << max(max_arr[0], max(max_arr[1], max_arr[2])) << " "
       << min(min_arr[0], min(min_arr[1], min_arr[2])) << '\n';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  solve();

  return 0;
}