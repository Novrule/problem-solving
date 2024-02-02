#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> compress;
vector<vector<pair<int, int>>> tree(10001);

inline int compressDevice(int mDevice) {
  if (!compress.count(mDevice)) {
    compress[mDevice] = compress.size();
  }

  return compress[mDevice];
}

void init(int mDevice) {
  compress.clear();

  tree.clear();
  tree.resize(10001);

  compressDevice(mDevice);

  return;
}

void connect(int mOldDevice, int mNewDevice, int mLatency) {
  int oldDevice = compressDevice(mOldDevice);
  int newDevice = compressDevice(mNewDevice);

  tree[oldDevice].emplace_back(make_pair(newDevice, mLatency));
  tree[newDevice].emplace_back(make_pair(oldDevice, mLatency));

  return;
}

int measure(int parentDevice, int curDevice, int targetDevice, int dist) {
  if (curDevice == targetDevice) {
    return dist;
  }

  for (int i = 0; i < tree[curDevice].size(); i++) {
    int nextDevice = tree[curDevice][i].first;
    int nextLatency = tree[curDevice][i].second;

    if (parentDevice != nextDevice) {
      int temp =
          measure(curDevice, nextDevice, targetDevice, dist + nextLatency);

      if (temp) {
        return temp;
      }
    }
  }

  return 0;
}

int measure(int mDevice1, int mDevice2) {
  int device1 = compressDevice(mDevice1);
  int device2 = compressDevice(mDevice2);

  return measure(device1, device1, device2, 0);
}

int test(int parentDevice, int curDevice) {
  int maxLatency = 0;

  for (int i = 0; i < tree[curDevice].size(); i++) {
    int nextDevice = tree[curDevice][i].first;
    int nextLatency = tree[curDevice][i].second;

    if (parentDevice != nextDevice) {
      maxLatency = max(maxLatency, test(curDevice, nextDevice) + nextLatency);
    }
  }

  return maxLatency;
}

int test(int mDevice) {
  int device = compressDevice(mDevice);
  int firstDist = 0;
  int secondDist = 0;

  for (int i = 0; i < tree[device].size(); i++) {
    int nextDevice = tree[device][i].first;
    int nextLatency = tree[device][i].second;
    int temp = test(device, nextDevice) + nextLatency;

    if (temp > firstDist) {
      secondDist = firstDist;
      firstDist = temp;
    } else if (temp > secondDist) {
      secondDist = temp;
    }
  }

  return firstDist + secondDist;
}
