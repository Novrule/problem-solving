#include <list>
#include <string>
#include <unordered_map>

using namespace std;

struct nation {
  int x;
  int y;
  int cnt;
};

int n, total;
int parent[10000];
int map[26][26];
nation nations[8625];
list<int> unionList[625];
list<int> enemyList[625];
unordered_map<string, int> nationInfo;

int findParent(int x) {
  if (parent[x] < 0) {
    return x;
  } else {
    return parent[x] = findParent(parent[x]);
  }
}

void unionParent(int x, int y) {
  x = findParent(x);
  y = findParent(y);

  if (parent[x] < parent[y]) {
    parent[y] = x;
    unionList[x].splice(unionList[x].end(), unionList[y]);
    enemyList[x].splice(enemyList[x].end(), enemyList[y]);
  } else {
    parent[x] = y;
    unionList[y].splice(unionList[y].end(), unionList[x]);
    enemyList[y].splice(enemyList[y].end(), enemyList[x]);
  }
}

int isSame(int x, int y) {
  x = findParent(x);
  y = findParent(y);

  if (x == y) {
    return 1;
  } else {
    return 0;
  }
}

int isEnemy(int x, int y) {
  x = findParent(x);
  y = findParent(y);

  for (auto enemy : enemyList[x]) {
    if (findParent(enemy) == y) {
      return 1;
    }
  }

  return 0;
}

void setEnemy(int x, int y) {
  x = findParent(x);
  y = findParent(y);

  if (x == y) {
    return;
  }

  if (isEnemy(x, y)) {
    return;
  }

  enemyList[x].push_back(y);
  enemyList[y].push_back(x);
}

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {
  int index = 0;

  n = N;

  nationInfo.clear();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      parent[index] = -1;

      map[i][j] = index;

      nations[index].cnt = mSoldier[i][j];
      nations[index].x = j;
      nations[index].y = i;

      unionList[index].clear();
      unionList[index].push_back(index);

      enemyList[index].clear();

      nationInfo[mMonarch[i][j]] = index;

      index++;
    }
  }

  total = n * n;
}

void destroy() {}

int ally(char mMonarchA[11], char mMonarchB[11]) {
  int a = nationInfo[mMonarchA];
  int b = nationInfo[mMonarchB];

  if (isSame(a, b)) {
    return -1;
  }
  if (isEnemy(a, b)) {
    return -2;
  }

  unionParent(a, b);

  return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
  int a = nationInfo[mMonarchA], b = nationInfo[mMonarchB];

  int bossA = findParent(a), bossB = findParent(b);

  if (bossA == bossB) {
    return -1;
  }

  int sx = nations[b].x - 1;
  int ex = nations[b].x + 1;
  int sy = nations[b].y - 1;
  int ey = nations[b].y + 1;
  bool isThereEnemy = false;

  if (sx < 0) {
    sx = 0;
  }

  if (sy < 0) {
    sy = 0;
  }

  if (ex > n - 1) {
    ex = n - 1;
  }

  if (ey > n - 1) {
    ey = n - 1;
  }

  for (int j = sy; j <= ey; j++) {
    for (int i = sx; i <= ex; i++) {
      if (bossA == findParent(map[j][i])) {
        isThereEnemy = true;
        j = n;

        break;
      }
    }
  }

  if (isThereEnemy == false) {
    return -2;
  }

  setEnemy(bossA, bossB);

  int moveNum;
  int totalSolA = 0;
  int totalSolB = nations[b].cnt;

  nations[b].cnt = 0;

  for (int j = sy; j <= ey; j++) {
    for (int i = sx; i <= ex; i++) {
      if (bossA == findParent(map[j][i])) {
        moveNum = nations[map[j][i]].cnt / 2;
        nations[map[j][i]].cnt -= moveNum;
        totalSolA += moveNum;
      } else if (bossB == findParent(map[j][i])) {
        moveNum = nations[map[j][i]].cnt / 2;
        nations[map[j][i]].cnt -= moveNum;
        totalSolB += moveNum;
      }
    }
  }

  if (totalSolB >= totalSolA) {
    nations[b].cnt = totalSolB - totalSolA;

    return 0;
  }

  unionList[bossB].remove(b);

  nations[b].cnt = totalSolA - totalSolB;
  nations[total] = nations[b];

  map[nations[total].y][nations[total].x] = total;

  nationInfo[mGeneral] = total;

  parent[total] = bossA;
  unionList[bossA].push_back(total);

  total++;

  return 1;
}

int recruit(char mMonarch[11], int mNum, int mOption) {
  int sum = 0;

  if (mOption == 0) {
    int a = nationInfo[mMonarch];

    nations[a].cnt += mNum;
    sum = nations[a].cnt;
  } else {
    int boss = findParent(nationInfo[mMonarch]);

    for (auto nation : unionList[boss]) {
      nations[nation].cnt += mNum;
      sum += nations[nation].cnt;
    }
  }

  return sum;
}