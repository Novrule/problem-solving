#include <iostream>
#include <vector>

using namespace std;

int input(vector<vector<int>> &gear, int &K) {
  string temp;

  for (int i = 0; i < 4; i++) {
    cin >> temp;

    for (int j = 0; j < 8; j++) {
      gear[i][j] = temp[j] - '0';
    }
  }

  cin >> K;

  return 0;
}

int rollGear(vector<vector<int>> &gear, int gearNum, int dir) {
  if (dir == 1) {
    int temp = gear[gearNum][7];

    for (int i = 7; i > 0; i--) {
      gear[gearNum][i] = gear[gearNum][i - 1];
    }

    gear[gearNum][0] = temp;
  } else {
    int temp = gear[gearNum][0];

    for (int i = 0; i < 7; i++) {
      gear[gearNum][i] = gear[gearNum][i + 1];
    }

    gear[gearNum][7] = temp;
  }

  return 0;
}

int leftGear(vector<vector<int>> &gear, int gearNum, int dir) {
  if (gearNum > 0) {
    if (gear[gearNum][6] != gear[gearNum - 1][2]) {
      leftGear(gear, gearNum - 1, -dir);
    }
  }

  rollGear(gear, gearNum, dir);

  return 0;
}

int rightGear(vector<vector<int>> &gear, int gearNum, int dir) {
  if (gearNum < 3) {
    if (gear[gearNum][2] != gear[gearNum + 1][6]) {
      rightGear(gear, gearNum + 1, -dir);
    }
  }

  rollGear(gear, gearNum, dir);

  return 0;
}

int output(vector<vector<int>> gear) {
  int result = 0;

  for (int i = 0; i < 4; i++) {
    if (gear[i][0] == 1) {
      result += (1 << i);
    }
  }

  cout << result << '\n';

  return 0;
}

int main(void) {
  int K;
  vector<vector<int>> gear(4, vector<int>(8));

  input(gear, K);

  while (K--) {
    int gearNum, dir;

    cin >> gearNum >> dir;

    leftGear(gear, gearNum - 1, dir);
    rollGear(gear, gearNum - 1, -dir);
    rightGear(gear, gearNum - 1, dir);
  }
  output(gear);

  return 0;
}