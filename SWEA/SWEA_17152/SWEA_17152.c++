#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Result {
  int mOrder;
  int mRank;
};

struct Node {
  int index;
  map<char, int> children;

  Node() {
    this->index = -1;
    this->children = map<char, int>();
  }
};

struct str {
  int parent;
  int cnt;
  string mStr;

  str(string mStr) {
    this->parent = -1;
    this->cnt = 0;
    this->mStr = mStr;
  }
};

struct res {
  int cnt;
  string mStr;

  res(int cnt, string mStr) {
    this->cnt = cnt;
    this->mStr = mStr;
  }
};

bool operator<(const res &a, const res &b) {
  if (a.cnt == b.cnt) {
    return a.mStr > b.mStr;
  } else {
    return a.cnt < b.cnt;
  }
}

vector<Node> trie;
vector<str> strList;
unordered_map<string, int> strMap;
priority_queue<res> pq;

int compress(char mStr[]) {
  string cur = string(mStr);

  if (!strMap.count(cur)) {
    strMap[cur] = strList.size();
    strList.push_back(str(cur));
  }

  return strMap[cur];
}

int findParent(int mIndex) {
  if (strList[mIndex].parent < 0) {
    return mIndex;
  } else {
    return strList[mIndex].parent = findParent(strList[mIndex].parent);
  }
}

int unionParent(int mIndex1, int mIndex2) {
  int mParent1 = findParent(mIndex1);
  int mParent2 = findParent(mIndex2);

  if (mParent1 < mParent2) {
    strList[mParent1].parent += strList[mParent2].parent;
    strList[mParent1].cnt += strList[mParent2].cnt;
    strList[mParent2].parent = mParent1;

    return strList[mParent1].cnt;
  } else if (mParent1 > mParent2) {
    strList[mParent2].parent += strList[mParent1].parent;
    strList[mParent2].cnt += strList[mParent1].cnt;
    strList[mParent1].parent = mParent2;

    return strList[mParent2].cnt;
  } else {
    return strList[mParent1].cnt;
  }
}

void init() {
  trie.clear();
  trie.push_back(Node());

  strList.clear();

  strMap.clear();
}

void search(char mStr[], int mCount) {
  int index = compress(mStr);
  int cur = 0;

  if (strList[index].parent < 0) {
    strList[index].cnt += mCount;
  } else {
    strList[findParent(index)].cnt += mCount;
  }

  for (int i = 0; mStr[i] != '\0'; i++) {
    if (!trie[cur].children.count(mStr[i])) {
      trie[cur].children[mStr[i]] = trie.size();
      trie.push_back(Node());
    }

    cur = trie[cur].children[mStr[i]];
  }

  trie[cur].index = index;
}

void circuit(int mCur) {
  if (trie[mCur].index != -1) {
    int index = findParent(trie[mCur].index);

    pq.push(res(strList[index].cnt, strList[trie[mCur].index].mStr));
  }

  for (auto i : trie[mCur].children) {
    circuit(i.second);
  }
}

Result recommend(char mStr[]) {
  int cur = 0;
  Result ret = {0, 0};

  pq = priority_queue<res>();
  circuit(cur);

  for (int i = 0; i < 5; i++) {
    if (pq.empty()) {
      break;
    }

    res temp = pq.top();
    pq.pop();

    if (temp.mStr == string(mStr)) {
      ret.mOrder = 0;
      ret.mRank = i + 1;

      strList[findParent(compress(mStr))].cnt++;

      return ret;
    }
  }

  for (int i = 0; i < mStr[i] != '\0'; i++) {
    pq = priority_queue<res>();
    cur = trie[cur].children[mStr[i]];
    circuit(cur);

    for (int j = 0; j < 5; j++) {
      if (pq.empty()) {
        break;
      }

      res temp = pq.top();
      pq.pop();

      if (temp.mStr == string(mStr)) {
        ret.mOrder = i + 1;
        ret.mRank = j + 1;

        strList[findParent(compress(mStr))].cnt++;

        return ret;
      }
    }
  }
}

int relate(char mStr1[], char mStr2[]) {
  int index1 = compress(mStr1);
  int index2 = compress(mStr2);

  return unionParent(index1, index2);
}

void rank(char mPrefix[], int mRank, char mReturnStr[]) {
  int cur = 0;

  pq = priority_queue<res>();

  for (int i = 0; mPrefix[i] != '\0'; i++) {
    cur = trie[cur].children[mPrefix[i]];
  }

  circuit(cur);

  for (int i = 0; i < mRank - 1; i++) {
    pq.pop();
  }

  res temp = pq.top();

  for (int i = 0; i < temp.mStr.size(); i++) {
    mReturnStr[i] = temp.mStr[i];
  }
  mReturnStr[temp.mStr.size()] = '\0';

  return;
}