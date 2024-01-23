#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int K;
string str;

void input() { cin >> K >> str; }

string solve() {
  string temp = "";
  vector<string> trie;

  for (int i = str.length() - 1; i >= 0; i--) {
    temp = str[i] + temp;
    trie.push_back(temp);
  }

  sort(trie.begin(), trie.end());

  if (K > trie.size()) {
    return "none";
  }

  return trie[K - 1];
}

void output(string ans, int test_case) {
  cout << "#" << test_case << " " << ans << "\n";
}

int main(int argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int test_case;
  int T;

  cin >> T;

  for (test_case = 1; test_case <= T; test_case++) {
    string ans;

    input();
    ans = solve();
    output(ans, test_case);
  }

  return 0;
}