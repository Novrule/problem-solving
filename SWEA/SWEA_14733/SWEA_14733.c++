#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int n, q;
vector<int> oddArr;
vector<int> evenArr;
vector<long long> oddTree;
vector<long long> evenTree;

void input() {
  oddArr.clear();
  oddArr.push_back(0);
  evenArr.clear();
  evenArr.push_back(0);
  oddTree.clear();
  evenTree.clear();

  cin >> n >> q;

  oddTree.resize(n * 2);
  evenTree.resize(n * 2);

  for (int i = 1; i < n + 1; i++) {
    int temp;

    cin >> temp;

    if (i % 2 == 0) {
      evenArr.push_back(temp);
    } else {
      oddArr.push_back(temp);
    }
  }
}

long long init(int index, int left, int right, vector<int> &arr,
               vector<long long> &tree) {
  if (left == right) {
    return tree[index] = static_cast<long long>(arr[left]);
  }

  int mid = (left + right) / 2;
  long long leftVal = init(index * 2, left, mid, arr, tree);
  long long rightVal = init(index * 2 + 1, mid + 1, right, arr, tree);

  return tree[index] = leftVal + rightVal;
}

long long update(int index, int left, int right, int target, long long value,
                 vector<long long> &tree) {
  if (left > target || right < target) {
    return tree[index];
  }

  if (left == right) {
    return tree[index] = value;
  }

  int mid = (left + right) / 2;
  long long leftVal = update(index * 2, left, mid, target, value, tree);
  long long rightVal =
      update(index * 2 + 1, mid + 1, right, target, value, tree);

  return tree[index] = leftVal + rightVal;
}

long long query(int index, int left, int right, int start, int end,
                vector<long long> &tree) {
  if (left >= start && right <= end) {
    return tree[index];
  }

  if (left > end || right < start) {
    return 0;
  }

  int mid = (left + right) / 2;
  long long leftVal = query(index * 2, left, mid, start, end, tree);
  long long rightVal = query(index * 2 + 1, mid + 1, right, start, end, tree);

  return leftVal + rightVal;
}

int output(int test_case) {
  cout << '#' << test_case;

  if (n % 2 == 0) {
    init(1, 1, n / 2, oddArr, oddTree);
    init(1, 1, n / 2, evenArr, evenTree);

    for (int i = 0; i < q; i++) {
      int a, b, c;

      cin >> a >> b >> c;

      if (a == 1) {
        b++;
        c++;

        if (b % 2 == 0) {
          if (c % 2 == 0) {
            cout << ' '
                 << query(1, 1, n / 2, b / 2, (c / 2) - 1, evenTree) -
                        query(1, 1, n / 2, (b / 2) + 1, c / 2, oddTree);
          } else {
            cout << ' '
                 << query(1, 1, n / 2, b / 2, c / 2, evenTree) -
                        query(1, 1, n / 2, (b / 2) + 1, c / 2, oddTree);
          }
        } else {
          if (c % 2 == 0) {
            cout << ' '
                 << query(1, 1, n / 2, (b / 2) + 1, c / 2, oddTree) -
                        query(1, 1, n / 2, (b / 2) + 1, (c / 2) - 1, evenTree);
          } else {
            cout << ' '
                 << query(1, 1, n / 2, (b / 2) + 1, c / 2, oddTree) -
                        query(1, 1, n / 2, (b / 2) + 1, c / 2, evenTree);
          }
        }
      } else {
        if (b % 2 == 0) {
          update(1, 1, n / 2, (b / 2) + 1, static_cast<long long>(c), oddTree);
        } else {
          update(1, 1, n / 2, (b / 2) + 1, static_cast<long long>(c), evenTree);
        }
      }
    }
  } else {
    init(1, 1, (n / 2) + 1, oddArr, oddTree);
    init(1, 1, n / 2, evenArr, evenTree);

    for (int i = 0; i < q; i++) {
      int a, b, c;

      cin >> a >> b >> c;

      if (a == 1) {
        b++;
        c++;

        if (b % 2 == 0) {
          if (c % 2 == 0) {
            cout << ' '
                 << query(1, 1, n / 2, b / 2, (c / 2) - 1, evenTree) -
                        query(1, 1, (n / 2) + 1, (b / 2) + 1, c / 2, oddTree);
          } else {
            cout << ' '
                 << query(1, 1, n / 2, b / 2, c / 2, evenTree) -
                        query(1, 1, (n / 2) + 1, (b / 2) + 1, c / 2, oddTree);
          }
        } else {
          if (c % 2 == 0) {
            cout << ' '
                 << query(1, 1, (n / 2) + 1, (b / 2) + 1, c / 2, oddTree) -
                        query(1, 1, n / 2, (b / 2) + 1, (c / 2) - 1, evenTree);
          } else {
            cout << ' '
                 << query(1, 1, (n / 2) + 1, (b / 2) + 1, c / 2, oddTree) -
                        query(1, 1, n / 2, (b / 2) + 1, c / 2, evenTree);
          }
        }
      } else {
        if (b % 2 == 0) {
          update(1, 1, (n / 2) + 1, (b / 2) + 1, static_cast<long long>(c),
                 oddTree);
        } else {
          update(1, 1, n / 2, (b / 2) + 1, static_cast<long long>(c), evenTree);
        }
      }
    }
  }

  cout << '\n';
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    input();
    output(test_case);
  }

  return 0;
}