#include <iostream>
#include <vector>

using namespace std;

void input(int &M, vector<int> &vec) {
  int N;

  cin >> N;

  for (int i = 0; i < N; i++) {
    int temp;

    cin >> temp;
    vec.push_back(temp);
  }

  cin >> M;
}

void edit(int M, vector<int> &vec) {
  for (int i = 0; i < M; i++) {
    char command;

    cin >> command;

    if (command == 'I') {
      int x, y;

      cin >> x >> y;

      vector<int> new_vec;

      for (int j = 0; j < y; j++) {
        int temp;

        cin >> temp;
        new_vec.push_back(temp);
      }

      vec.insert(vec.begin() + x, new_vec.begin(), new_vec.end());
    } else if (command == 'D') {
      int x, y;

      cin >> x >> y;

      vec.erase(vec.begin() + x, vec.begin() + x + y);
    } else if (command == 'A') {
      int y;

      cin >> y;

      vector<int> new_vec;

      for (int j = 0; j < y; j++) {
        int temp;

        cin >> temp;
        new_vec.push_back(temp);
      }

      vec.insert(vec.end(), new_vec.begin(), new_vec.end());
    }
  }
}

void output(int test_case, vector<int> &vec) {
  cout << "#" << test_case << " ";

  for (int i = 0; i < 10; i++) {
    cout << vec[i] << " ";
  }

  cout << "\n";
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T = 10;

  for (test_case = 1; test_case <= T; test_case++) {
    int M;
    vector<int> vec;

    input(M, vec);
    edit(M, vec);
    output(test_case, vec);
  }

  return 0;
}