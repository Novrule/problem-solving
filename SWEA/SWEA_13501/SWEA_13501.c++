#include <iostream>
#include <vector>

using namespace std;

void input(int &M, int &L, vector<int> &vec) {
  int N;

  cin >> N >> M >> L;

  for (int i = 0; i < N; i++) {
    int temp;

    cin >> temp;
    vec.push_back(temp);
  }
}

void edit(int M, vector<int> &vec) {
  for (int i = 0; i < M; i++) {
    char command;

    cin >> command;

    if (command == 'I') {
      int index, num;

      cin >> index >> num;

      vec.insert(vec.begin() + index, num);
    } else if (command == 'D') {
      int index;

      cin >> index;

      vec.erase(vec.begin() + index);
    } else if (command == 'C') {
      int index, num;

      cin >> index >> num;

      vec[index] = num;
    }
  }
}

void output(int L, int test_case, vector<int> &vec) {
  if (L >= vec.size()) {
    cout << '#' << test_case << ' ' << "-1\n";
  } else {
    cout << '#' << test_case << ' ' << vec[L] << '\n';
  }
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    int M, L;
    vector<int> vec;

    input(M, L, vec);
    edit(M, vec);
    output(L, test_case, vec);
  }

  return 0;
}