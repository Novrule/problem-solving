#include <iostream>
#include <stack>
#include <string>

using namespace std;

string str;

void input() { cin >> str; }

int calculate() {
  int ans = 0;
  int temp = 1;
  stack<char> s;

  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '(') {
      temp *= 2;
      s.push('(');
    } else if (str[i] == '[') {
      temp *= 3;
      s.push('[');
    } else if (str[i] == ')') {
      if (s.empty() || s.top() != '(') {
        ans = 0;

        break;
      }

      if (str[i - 1] == '(') {
        ans += temp;
      }

      temp /= 2;
      s.pop();
    } else if (str[i] == ']') {
      if (s.empty() || s.top() != '[') {
        ans = 0;

        break;
      }

      if (str[i - 1] == '[') {
        ans += temp;
      }

      temp /= 3;
      s.pop();
    }
  }

  if (!s.empty()) {
    ans = 0;
  }

  return ans;
}

void output(int ans) { cout << ans << '\n'; }

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int ans;

  input();
  ans = calculate();
  output(ans);

  return 0;
}