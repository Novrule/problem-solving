#include <iostream>

using namespace std;

void hanoi(int N, int from, int by, int to) {
  if (N == 1) {
    cout << from << ' ' << to << '\n';

    return;
  }

  hanoi(N - 1, from, to, by);
  cout << from << ' ' << to << '\n';
  hanoi(N - 1, by, from, to);
}

int main(void) {
  int N;

  cin >> N;
  cout << (1 << N) - 1 << '\n';
  hanoi(N, 1, 2, 3);

  return 0;
}