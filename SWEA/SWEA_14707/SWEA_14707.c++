#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
  int cnt;
  map<char, int> child;

  Node() {
    this->cnt = 0;
    this->child.clear();
  }
};

int index, res;
vector<Node> trie;
const int ROOT = 0;

void init() {
  index = 1;
  trie.clear();
  trie.push_back(Node());

  return;
}

int add(char str[]) {
  int cur = ROOT;

  for (int i = 0; str[i]; i++) {
    if (!trie[cur].child.count(str[i])) {
      trie[cur].child[str[i]] = index++;
      trie.push_back(Node());
    }

    cur = trie[cur].child[str[i]];
  }

  return ++trie[cur].cnt;
}

void recursiveRemove(int cur, char str[]) {
  if (str[0] == '\0') {
    res += trie[cur].cnt;
    trie[cur].cnt = 0;

    return;
  } else if (str[0] == '?') {
    map<char, int>::iterator it = trie[cur].child.begin();

    while (it != trie[cur].child.end()) {
      recursiveRemove(it->second, str + 1);
      it++;
    }
  } else {
    if (!trie[cur].child.count(str[0])) {
      return;
    }

    recursiveRemove(trie[cur].child[str[0]], str + 1);
  }
}

int remove(char str[]) {
  res = 0;
  recursiveRemove(ROOT, str);

  return res;
}

void recursiveSearch(int cur, char str[]) {
  if (str[0] == '\0') {
    res += trie[cur].cnt;

    return;
  } else if (str[0] == '?') {
    map<char, int>::iterator it = trie[cur].child.begin();

    while (it != trie[cur].child.end()) {
      recursiveSearch(it->second, str + 1);
      it++;
    }
  } else {
    if (!trie[cur].child.count(str[0])) {
      return;
    }

    recursiveSearch(trie[cur].child[str[0]], str + 1);
  }
}

int search(char str[]) {
  res = 0;
  recursiveSearch(ROOT, str);

  return res;
}
