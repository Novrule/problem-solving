#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

struct block {
  int prev, next, height;
  int hash[5];
  bool removed;

  block() {
    prev = next = height = -1;
    removed = false;
  }

  block(int prev, int next, int height) {
    this->prev = prev;
    this->next = next;
    this->height = height;
    removed = false;
  }
};

int index = 0;
vector<int> answers;
vector<block> blocks(100000);
priority_queue<int> hashMap[10][10][10][10][10];

void init() {
  index = 0;

  answers.clear();

  for (int i = 0; i < 100000; i++) {
    blocks[i] = block();
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        for (int l = 0; l < 10; l++) {
          for (int m = 0; m < 10; m++) {
            hashMap[i][j][k][l][m] = priority_queue<int>();
          }
        }
      }
    }
  }
}

int findPrev(int temp) {
  temp--;

  while (temp >= 0 && blocks[temp].removed) {
    if (temp == 0) {
      return -1;
    }

    temp--;
  }

  return temp;
}

int findMin(int temp) {
  if (temp < 0) {
    return -1;
  }

  int min = INT_MAX;

  for (int i = 0; i < 5; i++) {
    if (blocks[temp].height < min) {
      min = blocks[temp].height;
    }

    if (i != 4 && blocks[temp].next == -1) {
      return -1;
    } else {
      temp = blocks[temp].next;
    }
  }

  return min;
}

void addHash(int temp, int min) {
  int cur = blocks[temp].height - min;
  int next = blocks[blocks[temp].next].height - min;
  int nnext = blocks[blocks[blocks[temp].next].next].height - min;
  int nnnext = blocks[blocks[blocks[blocks[temp].next].next].next].height - min;
  int nnnnext =
      blocks[blocks[blocks[blocks[blocks[temp].next].next].next].next].height -
      min;

  blocks[temp].hash[0] = cur;
  blocks[temp].hash[1] = next;
  blocks[temp].hash[2] = nnext;
  blocks[temp].hash[3] = nnnext;
  blocks[temp].hash[4] = nnnnext;

  hashMap[cur][next][nnext][nnnext][nnnnext].push(temp);
}

void makeWall(int mHeights[5]) {
  for (int i = 0; i < 5; i++) {
    int prev = findPrev(index);

    blocks[index] = block(prev, -1, mHeights[i]);

    if (prev != -1) {
      blocks[prev].next = index;
    }

    index++;
  }

  int temp = index - 1;

  for (int i = 0; i < 9; i++) {
    int min = findMin(temp);

    if (min != -1) {
      addHash(temp, min);
    }

    if (blocks[temp].prev == -1) {
      break;
    } else {
      temp = blocks[temp].prev;
    }
  }
}

int findMax(int mHeights[5]) {
  int max = INT_MIN;

  for (int i = 0; i < 5; i++) {
    if (mHeights[i] > max) {
      max = mHeights[i];
    }
  }

  return max;
}

bool checkHash(int temp, int max, int mHeights[5]) {
  for (int i = 0; i < 5; i++) {
    if (blocks[temp].hash[i] != max - mHeights[4 - i]) {
      return false;
    }
  }

  return true;
}

int matchPiece(int mHeights[5]) {
  int max = findMax(mHeights);
  priority_queue<int> &cur =
      hashMap[max - mHeights[4]][max - mHeights[3]][max - mHeights[2]]
             [max - mHeights[1]][max - mHeights[0]];

  while (!cur.empty()) {
    int temp = cur.top();

    cur.pop();

    if (!blocks[temp].removed && checkHash(temp, max, mHeights)) {
      int ans = temp;

      for (int i = 0; i < 5; i++) {
        blocks[temp].removed = true;

        if (blocks[temp].next == -1) {
          break;
        } else {
          temp = blocks[temp].next;
        }
      }

      if (blocks[ans].prev != -1) {
        blocks[blocks[ans].prev].next = temp;
        blocks[temp].prev = blocks[ans].prev;
      } else {
        blocks[temp].prev = blocks[ans].prev;
      }

      temp = ans;

      for (int i = 0; i < 4; i++) {
        if (blocks[temp].prev == -1) {
          break;
        } else {
          temp = blocks[temp].prev;
        }

        int min = findMin(temp);

        if (min == -1) {
          continue;
        } else {
          addHash(temp, min);
        }
      }

      answers.push_back(ans);
      sort(answers.begin(), answers.end());

      return ans -
             ((lower_bound(answers.begin(), answers.end(), ans) -
               answers.begin()) *
              5) +
             1;
    }
  }

  return -1;
}