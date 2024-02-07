#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define MAX_USER 500
#define MAX_CHANNEL 500
#define MAX_NEWS 30000

struct News {
  int newsId;
  int channelId;
  int time;
  bool isDeleted;

  News() {
    newsId = -1;
    channelId = -1;
    time = -1;
    isDeleted = false;
  };

  News(int newsId, int channelId, int time) {
    this->newsId = newsId;
    this->channelId = channelId;
    this->time = time;
    isDeleted = false;
  };
};

struct cmp {
  bool operator()(const News* a, const News* b) {
    if (a->time == b->time) {
      return a->newsId > b->newsId;
    } else {
      return a->time > b->time;
    }
  }
};

int poolIndex;
News newsPool[MAX_NEWS];

News* newsList[MAX_NEWS];
vector<int> channelList[MAX_CHANNEL];
vector<News*> userList[MAX_USER];
priority_queue<News*, vector<News*>, cmp> pq;

unordered_map<int, int> nMapper;
unordered_map<int, int> cMapper;
unordered_map<int, int> uMapper;

void init(int N, int K) {
  poolIndex = 0;

  nMapper.clear();
  cMapper.clear();
  uMapper.clear();

  for (int i = 0; i < MAX_CHANNEL; i++) {
    channelList[i].clear();
    userList[i].clear();
  }

  pq = priority_queue<News*, vector<News*>, cmp>();
}

void sendNews(int mTime) {
  while (!pq.empty() && pq.top()->time <= mTime) {
    News* news = pq.top();

    pq.pop();

    if (news->isDeleted) {
      continue;
    }

    for (auto user : channelList[news->channelId]) {
      userList[user].push_back(news);
    }
  }
}

inline int compress(unordered_map<int, int>& mapper, int key) {
  if (!mapper.count(key)) {
    mapper[key] = mapper.size();
  }

  return mapper[key];
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[]) {
  sendNews(mTime);

  int userId = compress(uMapper, mUID);

  for (int i = 0; i < mNum; i++) {
    int channelId = compress(cMapper, mChannelIDs[i]);

    channelList[channelId].push_back(userId);
  }
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID) {
  int newsId = compress(nMapper, mNewsID);
  int channelId = compress(cMapper, mChannelID);

  News* news = &newsPool[poolIndex++];
  news->newsId = mNewsID;
  news->channelId = channelId;
  news->time = mTime + mDelay;
  news->isDeleted = false;

  newsList[newsId] = news;
  pq.emplace(news);

  return channelList[channelId].size();
}

void cancelNews(int mTime, int mNewsID) {
  sendNews(mTime);

  int newsId = compress(nMapper, mNewsID);

  newsList[newsId]->isDeleted = true;
}

int checkUser(int mTime, int mUID, int mRetIDs[]) {
  sendNews(mTime);

  int userId = compress(uMapper, mUID);
  int cnt = 0;

  while (!userList[userId].empty()) {
    News* news = userList[userId].back();

    if (news->isDeleted) {
      userList[userId].pop_back();

      continue;
    } else {
      if (cnt < 3) {
        mRetIDs[cnt] = news->newsId;
      }

      userList[userId].pop_back();
      cnt++;
    }
  }

  return cnt;
}
