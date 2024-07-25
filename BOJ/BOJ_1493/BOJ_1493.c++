#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int ans = 0;
int length, width, height, a, b, N, cube[21];

void input() {
  cin >> length >> width >> height >> N;

  for (int i = 0; i < N; i++) {
    cin >> a >> b;

    cube[a] = b;
  }
}

void output() { cout << ans << '\n'; }

void solve(int x, int y, int z) {
  if (x == 0 || y == 0 || z == 0) {
    return;
  }

  int index = (int)log2(min(x, min(y, z)));
  bool flag = false;
  int len;

  for (int i = index; i >= 0; i--) {
    if (cube[i] > 0) {
      flag = true;
      index = i;

      break;
    }
  }

  if (!flag) {
    ans = -1;
    output();

    exit(0);
  }

  ans++;
  cube[index]--;
  len = 1 << index;

  solve(x - len, y, z);
  solve(len, y - len, len);
  solve(len, y, z - len);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input();
  solve(length, width, height);
  output();
}