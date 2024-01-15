#include <iostream>

using namespace std;

int input() {
  int N, result = 1;

  cin >> N;

  for (int i = 0; i < N; i++) {
    int index;
    char data;

    cin >> index >> data;

    if (index * 2 <= N) {
      int left;

      cin >> left;

      if (index * 2 + 1 <= N) {
        int right;

        cin >> right;
      }

      if (data >= '0' && data <= '9') {
        result = 0;
      }
    } else {
      if (data < '0' || data > '9') {
        result = 0;
      }
    }
  }

  return result;
}

void output(int result, int test_case) {
  cout << '#' << test_case << ' ' << result << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++) {
    int result = input();
    output(result, test_case);
  }

  return 0;
}