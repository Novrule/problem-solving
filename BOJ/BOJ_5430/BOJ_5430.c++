#include <deque>
#include <iostream>
#include <string>

using namespace std;

deque<int> input(int n, string arr) {
  deque<int> dq;

  if (n) {
    string tmp = "";

    for (int i = 1; i < arr.length(); i++) {
      if (arr[i] == ',' || arr[i] == ']') {
        dq.push_back(stoi(tmp));
        tmp = "";
      } else {
        tmp += arr[i];
      }
    }
  }

  return dq;
}

int AC(deque<int>& dq, string p) {
  int flag = 1;

  for (int i = 0; i < p.length(); i++) {
    if (p[i] == 'R') {
      flag = (flag + 1) % 2;
    } else {
      if (dq.empty()) {
        flag = -1;

        break;
      } else {
        if (flag) {
          dq.pop_front();
        } else {
          dq.pop_back();
        }
      }
    }
  }

  return flag;
}

int output(deque<int> dq, int flag) {
  if (flag == -1) {
    cout << "error\n";
  } else if (dq.empty()) {
    cout << "[]\n";
  } else {
    cout << "[";

    if (flag) {
      for (int i = 0; i < dq.size() - 1; i++) {
        cout << dq[i] << ",";
      }

      cout << dq[dq.size() - 1];
    } else {
      for (int i = dq.size() - 1; i > 0; i--) {
        cout << dq[i] << ",";
      }

      cout << dq[0];
    }

    cout << "]\n";
  }

  return 0;
}

int main(void) {
  int T;

  cin >> T;

  while (T--) {
    int n, flag;
    string p, arr;
    deque<int> dq;

    cin >> p >> n >> arr;

    dq = input(n, arr);
    flag = AC(dq, p);
    output(dq, flag);
  }

  return 0;
}