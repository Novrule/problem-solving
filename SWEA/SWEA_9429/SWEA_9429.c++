#include <array>
#include <iostream>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

using namespace std;

struct Directory {
  int treeSize, childCount, parent;
  long long name;
  array<int, 30> childs;
};

Directory pool[50050];
int root, index = 0;

int newDirectory(long long name) {
  pool[index].name = name;
  pool[index].treeSize = 0;
  pool[index].childCount = 0;
  pool[index].parent = -1;

  return index++;
}

int copyDirectory(int target) {
  int copy = newDirectory(pool[target].name);

  pool[copy].treeSize = pool[target].treeSize;

  for (int i = 0; i < pool[target].childCount; i++) {
    int child = copyDirectory(pool[target].childs[i]);

    pool[copy].childs[pool[copy].childCount++] = child;
    pool[child].parent = copy;
  }

  return copy;
}

int findIndex(char path[PATH_MAXLEN + 1]) {
  int temp = root;

  for (int i = 1; path[i];) {
    int j = i;
    long long name = 0;

    while (path[j] != '/') {
      name <<= 5;
      name += (path[j] - 'a' + 1);
      j++;
    }

    int left = 0;
    int right = pool[temp].childCount - 1;

    while (left < right) {
      int mid = (left + right) / 2;

      if (pool[pool[temp].childs[mid]].name >= name) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    temp = pool[temp].childs[right];
    i = j + 1;
  }

  return temp;
}

inline void insert(array<int, 30> &childs, int &childCount, int node) {
  childs[childCount] = node;

  for (int i = childCount - 1; i >= 0; --i) {
    if (pool[childs[i]].name > pool[childs[i + 1]].name) {
      swap(childs[i], childs[i + 1]);
    } else {
      break;
    }
  }

  childCount++;
}

void updateTreeSize(int node, int size) {
  while (node != -1) {
    pool[node].treeSize += size;
    node = pool[node].parent;
  }
}

void init(int n) {
  index = 0;
  root = newDirectory(0);
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
  int temp = findIndex(path);
  long long newName = 0;

  updateTreeSize(temp, 1);
  for (int i = 0; name[i]; ++i) {
    newName <<= 5;
    newName += (name[i] - 'a' + 1);
  }

  int newIndex = newDirectory(newName);

  insert(pool[temp].childs, pool[temp].childCount, newIndex);
  pool[newIndex].parent = temp;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
  int node = findIndex(path);
  int parent = pool[node].parent;
  int left = 0;
  int right = pool[parent].childCount - 1;

  while (left < right) {
    int mid = (left + right) / 2;

    if (pool[pool[parent].childs[mid]].name >= pool[node].name) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  for (int i = right; i < pool[parent].childCount - 1; i++) {
    pool[parent].childs[i] = pool[parent].childs[i + 1];
  }

  pool[parent].childCount--;
  updateTreeSize(parent, -(pool[node].treeSize + 1));
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
  int src = findIndex(srcPath);
  int dst = findIndex(dstPath);

  updateTreeSize(dst, pool[src].treeSize + 1);

  int copy = copyDirectory(src);

  insert(pool[dst].childs, pool[dst].childCount, copy);
  pool[copy].parent = dst;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
  int src = findIndex(srcPath);
  int dst = findIndex(dstPath);

  updateTreeSize(dst, pool[src].treeSize + 1);
  cmd_rm(srcPath);
  insert(pool[dst].childs, pool[dst].childCount, src);
  pool[src].parent = dst;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
  return pool[findIndex(path)].treeSize;
}