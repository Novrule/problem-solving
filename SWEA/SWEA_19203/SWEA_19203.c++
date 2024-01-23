#include <deque>
#include <iostream>
#include <vector>

using namespace std;

bool isReverse;
vector<int> hashCnt(1 << 20);
deque<char> dq;

void calcFront(int count) {
  int hash = 0;
  int temp = 1;

  for (int i = 0; i < 4 && i < dq.size(); i++) {
    hash += temp * (dq[i] - 'a' + 1);
    temp <<= 5;
    hashCnt[hash] += count;
  }
}

void calcBack(int count) {
  int hash = 0;

  for (int i = dq.size() - 1, j = 0; i >= 0 && j < 4; i--, j++) {
    hash <<= 5;
    hash += (dq[i] - 'a' + 1);
    hashCnt[hash] += count;
  }
}

void pushFront(char c) {
  dq.push_front(c);
  calcFront(1);
}

void popFront() {
  calcFront(-1);
  dq.pop_front();
}

void pushBack(char c) {
  dq.push_back(c);
  calcBack(1);
}

void popBack() {
  calcBack(-1);
  dq.pop_back();
}

void init(char mStr[]) {
  isReverse = false;
  dq.clear();

  for (int i = 0; i < hashCnt.size(); i++) {
    hashCnt[i] = 0;
  }

  for (int i = 0; mStr[i]; i++) {
    pushBack(mStr[i]);
  }
}

void appendWord(char mWord[]) {
  if (isReverse) {
    for (int i = 0; mWord[i]; i++) {
      pushFront(mWord[i]);
    }
  } else {
    for (int i = 0; mWord[i]; i++) {
      pushBack(mWord[i]);
    }
  }
}

void cut(int k) {
  if (isReverse) {
    for (int i = 0; i < k; i++) {
      popFront();
    }
  } else {
    for (int i = 0; i < k; i++) {
      popBack();
    }
  }
}

void reverse() { isReverse = !isReverse; }

int countOccurrence(char mWord[]) {
  int hash = 0;

  if (isReverse) {
    for (int i = 0; mWord[i]; i++) {
      hash <<= 5;
      hash += (mWord[i] - 'a' + 1);
    }

  } else {
    int temp = 1;

    for (int i = 0; mWord[i]; i++) {
      hash += (mWord[i] - 'a' + 1) * temp;
      temp <<= 5;
    }
  }

  return hashCnt[hash];
}
