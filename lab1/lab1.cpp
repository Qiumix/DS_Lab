#include <iostream>
using namespace std;

template <typename T> class SqList {
private:
  // 物理大小
  int _physicsSize;
  // 逻辑大小
  int _size;
  // 起始索引，偏移这个变量实现O(1)的insertHead
  int _startIndex;
  // 所有元素，一个指针，指向对应数组，析构函数会自动回收
  T *_elems;
  // 扩容物理大小来容纳更多元素，自动重置起始索引
  void resize(int newSize) {
    if (newSize <= _physicsSize) {
      throw "new size too small";
    }
    T *newElems = new T[newSize];
    for (int i = 0; i < _size; i++) {
      newElems[i] = get(i);
    }
    delete[] _elems;
    this->_elems = newElems;
    this->_physicsSize = newSize;
    this->_startIndex = 0;
  }
  T safeGet(int index) { return _elems[(index + _startIndex) % _physicsSize]; }
  // 给定逻辑索引，返回物理索引，多加个物理索引防止取模负数
  int getTrueIndex(int index) {
    return (_physicsSize + index + _startIndex) % _physicsSize;
  }
  void set(T elem, int index) {
    if (index >= _size || index < 0) {
      throw "out of range";
    }
    _elems[getTrueIndex(index)] = elem;
  }
  // 将给定逻辑索引后的元素后移，辅助方法
  void moveBack(int index) {
    for (int i = _size; i > index; i--) {
      int des = getTrueIndex(i);
      int src = getTrueIndex(i - 1);
      _elems[des] = _elems[src];
    }
  }

  static T min(T a, T b) { return a < b ? a : b; }
  static T max(T a, T b) { return a > b ? a : b; }

  void swap(int i, int j) {
    T temp = get(i);
    set(get(j), i);
    set(temp, j);
  }

  static SqList<T> *pureSingleHelper( //
      SqList<T> *origin, SqList<T> *target, int fromIndex = 0) {
    for (int index = fromIndex; index < origin->size(); index++) {
      T v = origin->get(index);
      if (target->isEmpty() || !(target->get(target->size() - 1) == v)) {
        target->insert(v);
      }
    }
    return target;
  }

public:
  // 构造函数，接受一个参数n为默认物理大小
  SqList(int n = 10) : _physicsSize(n), _startIndex(0), _size(0) {
    _elems = new T[n];
  }

  SqList(T *elems, int size)
      : _physicsSize(size * 2), _startIndex(0), _size(0) {
    _elems = new T[_physicsSize];
    for (int i = 0; i < size; i++) {
      insert(elems[i]);
    }
  }

  // 析构函数，自动回收内存
  ~SqList() { delete[] _elems; }

  int size() { return _size; }

  T get(int index) {
    if (index >= _size || index < 0) {
      throw "index out of range";
    }
    return _elems[(index + _startIndex) % _physicsSize];
  }

  bool isEmpty() { return size() == 0; }

  // 插入尾部
  void insertTail(T elem) {
    if (_size == _physicsSize) {
      resize(2 * _physicsSize);
    }
    _elems[getTrueIndex(_size++)] = elem;
  };

  void insertHead(T elem) {
    if (_size == _physicsSize) {
      resize(2 * _physicsSize);
    }
    _startIndex = (_startIndex - 1 + _physicsSize) % _physicsSize;
    _elems[_startIndex] = elem;
    _size++;
  }

  void insert(T elem) { insertTail(elem); }

  void insert(T elem, int index) {
    if (index > size() || index < 0) {
      throw "index out of range";
    }
    if (size() == _physicsSize) {
      resize(2 * _physicsSize);
    }
    moveBack(index);
    _elems[getTrueIndex(index)] = elem;
    _size++;
  }

  void reverse() {
    for (int i = 0; i < _size / 2; i++) {
      swap(i, _size - 1 - i);
    }
  }

  T max() {
    if (_size == 0) {
      throw "sqlist is empty";
    }
    T temp = get(0);
    for (int i = 0; i < _size; i++) {
      if (get(i) > temp)
        temp = get(i);
    }
    return temp;
  }

  T min() {
    if (_size == 0) {
      throw "sqlist is empty";
    }
    T temp = get(0);
    for (int i = 0; i < _size; i++) {
      if (get(i) < temp)
        temp = get(i);
    }
    return temp;
  }

  void printSelf() {
    for (int i = 0; i < size(); i++) {
      cout << get(i) << " ";
    }
    cout << endl;
  }

  void sort() {
    for (int i = 0; i < _size - 1; i++)
      for (int j = 0; j < _size - 1 - i; j++)
        if (get(j) > get(j + 1))
          swap(j, j + 1);
  }

  static SqList<T> *pureMerge(SqList<T> *listA, SqList<T> *listB) {
    SqList<T> *newList = new SqList(2 * (listA->size() + listB->size()));
    if (listA->isEmpty() && listB->isEmpty()) {
      return newList;
    } else if (listA->isEmpty() && !listB->isEmpty()) {
      return pureSingleHelper(listB, newList);
    } else if (!listA->isEmpty() && listB->isEmpty()) {
      return pureSingleHelper(listA, newList);
    }
    int indexA = 0, indexB = 0;
    while (true) {
      if (listA->size() <= indexA) {
        return pureSingleHelper(listB, newList);
      }
      if (listB->size() <= indexB) {
        return pureSingleHelper(listA, newList);
      }
      T a = listA->get(indexA);
      T b = listB->get(indexB);
      T x = min(a, b);

      if (newList->isEmpty() || newList->get(newList->size() - 1) == x)
        newList->insert(x);

      while (indexA < listA->size() && listA->get(indexA) == x)
        indexA++;
      while (indexB < listB->size() && listB->get(indexB) == x)
        indexB++;
    }
  }
};

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
