#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

struct point {
  int start;
  int end;
};

int n, total;
map<int, int> section;
unordered_map<int, vector<point>> files;

void init(int N) {
  n = N;
  total = 0;

  section.clear();
  section = {{-1, -1}, {n, n}};

  files.clear();
  files.reserve(13000);
}

int add(int mId, int mSize) {
  if (total + mSize > n) {
    return -1;
  }

  int ans = section.begin()->second + 1;
  auto &temp = files[mId];

  total += mSize;

  for (auto i = section.begin(), j = next(section.begin());
       mSize && j != section.end();) {
    int from = i->second + 1;

    if (j->first - 1 <= from + mSize - 1) {
      int to = j->first - 1;

      i->second = j->second;
      j = section.erase(j);
      temp.push_back({from, to});
      mSize -= (to - from + 1);
    } else {
      i->second = from + mSize - 1;
      temp.push_back({from, from + mSize - 1});

      break;
    }
  }

  return ans + 1;
}

int remove(int mId) {
  auto &temp = files[mId];
  int ans = temp.size();

  for (auto &point : temp) {
    int start = point.start;
    int end = point.end;
    auto it = --section.upper_bound(start);

    total -= end - start + 1;

    if (end < it->second) {
      section.insert({end + 1, it->second});
    }

    if (it->first < start) {
      it->second = start - 1;
    } else {
      section.erase(it);
    }
  }

  files.erase(mId);

  return ans;
}

int count(int mStart, int mEnd) {
  int ans = 0;

  --mStart;
  --mEnd;

  for (auto &file : files) {
    int id = file.first;
    auto &temp = file.second;

    int left = 0;
    int right = temp.size();

    while (left < right) {
      int mid = (left + right) / 2;

      if (temp[mid].start > mStart) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    if (right != temp.size() && temp[right].start <= mEnd) {
      ++ans;
    } else if (right != 0 && temp[right - 1].end >= mStart) {
      ++ans;
    }
  }

  return ans;
}