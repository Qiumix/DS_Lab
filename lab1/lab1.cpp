#include <iostream>
using namespace std;

template <typename T> class SqList {
private:
  int _psize;
  int _size;
  int _startIndex;
  T *_elems;
  void resize(int newSize) {
    if (newSize <= _psize) {
      throw "new size too small";
    }
    T *newElems = new T[newSize];
    for (int i = 0; i < _size; i++) {
      newElems[i] = get(i);
    }
    delete[] _elems;
    this->_elems = newElems;
    this->_psize = newSize;
    this->_startIndex = 0;
  }

public:
  SqList(int n = 10) : _psize(n), _startIndex(0) { _elems = new T[n]; }
  ~SqList() { delete[] _elems; }
  int size() { return _size; }
  T get(int index) {
    if (index >= _size) {
      throw "index out of range";
    }
    return _elems[(index + _startIndex) % _psize];
  }
  bool isEmpty() { return size() == 0; }
  void insert(T elem) {
    if (_size == _psize) {
      resize(2 * _psize);
    }
    _elems[(_startIndex + _size++) % _psize] = elem;
  };
  void insert(T elem, int index) {
    if (index > size()) {
      throw "index out of range";
    }
  }
  void insertHead(T elem) {
    if (_size == _psize) {
      resize(2 * _psize);
    }
    _startIndex = (_startIndex - 1 + _psize) % _psize;
  }
  static SqList pureMerge(SqList *listA, Sqlist *listB) {}
};

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
