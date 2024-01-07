#include <cmath>
#include <iostream>

using namespace std;

int findFloor(int num) {
  int floor = 1;

  while (floor * (floor + 1) / 2 < num) {
    floor++;
  }

  return floor;
}

float findLocation(int floor, int num) {
  int first, last;
  float middle, location;

  last = floor * (floor + 1) / 2;
  first = last - floor + 1;
  middle = (first + last) / 2.0;
  location = num - middle;

  return location;
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    int s, e;

    cin >> s >> e;

    int sFloor = findFloor(s);
    int eFloor = findFloor(e);
    int height = abs(sFloor - eFloor);
    float sLocation = findLocation(sFloor, s);
    float eLocation = findLocation(eFloor, e);
    int width = static_cast<int>(fabs(sLocation - eLocation) - (0.5 * height));

    if (width < 0) {
      width = 0;
    }

    int result = height + width;

    cout << "#" << test_case << " " << result << '\n';
  }

  return 0;
}