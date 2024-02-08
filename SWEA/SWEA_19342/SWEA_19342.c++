#include <climits>
#include <queue>
#include <vector>

using namespace std;

struct Road {
  int cost;
  int cnt;
  int index;
};

bool operator<(const Road &a, const Road &b) {
  int aCost = static_cast<int>(a.cost / a.cnt);
  int bCost = static_cast<int>(b.cost / b.cnt);

  if (aCost == bCost) {
    return a.index > b.index;
  } else {
    return aCost < bCost;
  }
}

vector<int> city;
vector<int> costs;
priority_queue<Road> pq;

void init(int N, int mPopulation[]) {
  city.clear();
  city.resize(N);

  costs.clear();
  costs.resize(N - 1);

  pq = priority_queue<Road>();

  for (int i = 0; i < N; i++) {
    city[i] = mPopulation[i];

    if (i < N - 1) {
      costs[i] = mPopulation[i] + mPopulation[i + 1];
      pq.push({costs[i], 1, i});
    }
  }

  return;
}

int expand(int M) {
  int ans;

  while (M--) {
    Road road = pq.top();
    pq.pop();

    int cost = road.cost;
    int cnt = road.cnt + 1;
    int index = road.index;

    ans = static_cast<int>(cost / cnt);
    costs[index] = ans;
    pq.push({cost, cnt, index});
  }

  return ans;
}

int calculate(int mFrom, int mTo) {
  int from = min(mFrom, mTo);
  int to = max(mFrom, mTo);
  int ans = 0;

  for (int i = from; i < to; i++) {
    ans += costs[i];
  }

  return ans;
}

int divide(int mFrom, int mTo, int K) {
  int ans;
  int left = 1;
  int right = INT_MAX;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    int cnt = 0;

    for (int i = mFrom; i <= mTo && cnt <= K; cnt++) {
      int j = i;
      int sum = 0;

      while (j <= mTo && sum + city[j] <= mid) {
        sum += city[j++];
      }

      i = j;
    }

    if (cnt <= K) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return ans;
}
