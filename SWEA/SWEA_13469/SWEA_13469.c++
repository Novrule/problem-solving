#include <deque>

using namespace std;

deque<char> memo[303];
int cnt[303][26];
int h, w, curR, curC, len;

void init(int H, int W, char mStr[]) {
  h = H;
  w = W;
  curR = 0;
  curC = 0;
  len = 0;

  for (int i = 0; i < 303; i++) {
    memo[i].clear();

    for (int j = 0; j < 26; j++) {
      cnt[i][j] = 0;
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (mStr[len]) {
        memo[i].push_back(mStr[len]);
        cnt[i][mStr[len++] - 'a']++;
      } else {
        break;
      }
    }
  }
}

void insert(char mChar) {
  int temp = curR;

  memo[curR].insert(memo[curR].begin() + curC, mChar);
  cnt[curR][mChar - 'a']++;
  curC++;
  len++;

  if (curC == w) {
    curR++;
    curC = 0;
  }

  while (memo[temp].size() > w) {
    char c = memo[temp].back();

    memo[temp].pop_back();
    cnt[temp][c - 'a']--;

    temp++;

    memo[temp].push_front(c);
    cnt[temp][c - 'a']++;
  }
}

char moveCursor(int mRow, int mCol) {
  mRow--;
  mCol--;

  if (mRow * w + mCol >= len) {
    curR = len / w;
    curC = len % w;

    return '$';
  } else {
    curR = mRow;
    curC = mCol;

    return memo[curR][curC];
  }
}

int countCharacter(char mChar) {
  int ans = 0;
  int row = curR;
  int col = curC;

  if (col) {
    for (int i = col; i < memo[row].size(); i++) {
      ans += memo[row][i] == mChar;
    }

    ++row;
  }

  for (int i = row; i < h; i++) {
    ans += cnt[i][mChar - 'a'];
  }

  return ans;
}
