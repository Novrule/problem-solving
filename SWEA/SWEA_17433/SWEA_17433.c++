#include <climits>
#include <set>
#include <tuple>
#include <unordered_map>

using namespace std;

struct student {
  int id, score;
};

bool operator<(const student &a, const student &b) {
  if (a.score == b.score) {
    return a.id < b.id;
  } else {
    return a.score < b.score;
  }
}

set<student> students[3][2];
unordered_map<int, tuple<int, int, int>> groups;

void init() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      students[i][j].clear();
    }
  }

  groups.clear();

  return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
  mGrade--;

  students[mGrade][mGender[0] == 'f'].insert({mId, mScore});
  groups[mId] = {mGrade, mGender[0] == 'f', mScore};

  return students[mGrade][mGender[0] == 'f'].rbegin()->id;
}

int remove(int mId) {
  if (!groups.count(mId)) {
    return 0;
  }

  int grade, gender, score;

  tie(grade, gender, score) = groups[mId];

  students[grade][gender].erase({mId, score});
  groups.erase(mId);

  if (students[grade][gender].empty()) {
    return 0;
  } else {
    return students[grade][gender].begin()->id;
  }
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7],
          int mScore) {
  student temp{0, INT_MAX};

  for (int i = 0; i < mGradeCnt; ++i) {
    mGrade[i]--;

    for (int j = 0; j < mGenderCnt; ++j) {
      set<student>::iterator it =
          students[mGrade[i]][mGender[j][0] == 'f'].lower_bound({0, mScore});
      if (it != students[mGrade[i]][mGender[j][0] == 'f'].end()) {
        if (*it < temp) {
          temp = *it;
        }
      }
    }
  }

  return temp.id;
}