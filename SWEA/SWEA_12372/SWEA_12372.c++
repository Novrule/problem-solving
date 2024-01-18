struct User {
  int uID;
  int height;

  User() {
    uID = 0;
    height = 0;
  }

  User(int uID, int height) {
    this->uID = uID;
    this->height = height;
  }
};

int index = 0;
User heap[100001];

bool cmp(User& a, User& b) {
  if (a.height > b.height) {
    return true;
  } else if (a.height < b.height) {
    return false;
  } else {
    return a.uID < b.uID;
  }
}

void swap(User& a, User& b) {
  User temp = a;

  a = b;
  b = temp;
}

void push(int uID, int height) {
  index++;
  heap[index].uID = uID;
  heap[index].height = height;

  int child = index;
  int parent = child / 2;

  while (parent > 0) {
    if (cmp(heap[child], heap[parent])) {
      swap(heap[child], heap[parent]);
    } else {
      break;
    }

    child = parent;
    parent = child / 2;
  }
}

int pop(int& index, User heap[]) {
  int result = heap[1].uID;

  heap[1] = heap[index];
  heap[index].uID = 0;
  heap[index].height = 0;
  index--;

  int parent = 1;
  int large = parent;
  int left = parent * 2;
  int right = parent * 2 + 1;

  while (true) {
    if (left <= index && cmp(heap[left], heap[large])) {
      large = left;
    }

    if (right <= index && cmp(heap[right], heap[large])) {
      large = right;
    }

    if (large == parent) {
      break;
    } else {
      swap(heap[parent], heap[large]);

      parent = large;
      left = parent * 2;
      right = parent * 2 + 1;
    }
  }

  return result;
}

void init() {
  for (int i = 0; i < index + 1; i++) {
    heap[i].uID = 0;
    heap[i].height = 0;
  }

  index = 0;
}

void addUser(int uID, int height) { push(uID, height); }

int getTop10(int result[10]) {
  int res = 10;
  User* copyHeap = new User[index + 1];
  int copyIndex = index;

  for (int i = 1; i < index + 1; i++) {
    copyHeap[i].uID = heap[i].uID;
    copyHeap[i].height = heap[i].height;
  }

  if (index < 10) {
    for (int i = 0; i < index; i++) {
      result[i] = pop(copyIndex, copyHeap);
    }

    res = index;
  } else {
    for (int i = 0; i < 10; i++) {
      result[i] = pop(copyIndex, copyHeap);
    }
  }

  delete[] copyHeap;

  return res;
}
