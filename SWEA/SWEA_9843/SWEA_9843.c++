#include <cmath>
#include <iostream>

using namespace std;

void input(long long& N) { cin >> N; }

long long solve(long long N) {
  long long left = 1;
  long long right = sqrt(2 * N);
  long long K = -1;

  while (left <= right) {
    long long mid = left + (right - left) / 2;

    if (mid * (mid + 1) / 2 == N) {
      K = mid;

      break;
    } else if (mid * (mid + 1) / 2 > N) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return K;
}

void output(long long K, int test_case) {
  cout << '#' << test_case << " " << K << '\n';
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    long long N, K;

    input(N);
    K = solve(N);
    output(K, test_case);
  }

  return 0;
}