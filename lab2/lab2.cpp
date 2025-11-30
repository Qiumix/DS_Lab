#include <iostream>

using namespace std;

template <typename T> class Node {
public:
  T val;
  Node *next;
  Node(T v = T(), Node<T> *n = NULL) : val(v), next(n) {};
};

template <typename T> class LinkedList {
private:
  int size_;
  Node<T> *head_;
  Node<T> *tail_;

public:
  LinkedList() : size_(0), head_(NULL), tail_(NULL) {}
  ~LinkedList() {
    auto temp = head_;
    while (temp) {
      auto temp2 = temp;
      temp = temp->next;
      delete temp2;
    }
  }

  int size() { return this->size_; }
  bool isEmpty() { return size() == 0; }
  void insert(T val) {
    Node<T> *newNode = new Node<T>(val);
    if (isEmpty()) {
      head_ = tail_ = newNode;
      newNode->next = newNode;
    } else {
      newNode->next = tail_->next;
      tail_->next = newNode;
      tail_ = newNode;
    }
    this->size_++;
  }

  Node<T> *getHead() { return this->head_; }
  Node<T> *getTail() { return this->tail_; }

  bool deleteNext(Node<T> *node) {
    if (isEmpty()) {
      return false;
    }
    Node<T> *nxt = node->next;
    node->next = node->next->next;
    delete nxt;
    size_--;
    if (isEmpty()) {
      head_ = tail_ = NULL;
    }
    return true;
  }

  void printSelf() {
    Node<T> *temp = head_;
    for (int i = 0; i < size(); i++) {
      cout << temp->val;
      temp = temp->next;
      cout << " ";
    }
    cout << endl;
  }
};

template <typename T> class Pair {
public:
  int num;
  T value;
  Pair(int n, T v) : num(n), value(v) {};
};

int main() {
  LinkedList<Pair<int> > llist;
  int size, m;
  cin >> m;
  cin >> size;
  for (int i = 0; i < size; i++) {
    int temp;
    cin >> temp;
    llist.insert(Pair<int>(i + 1, temp));
  }
  Node<Pair<int> > *pre;
  pre = llist.getTail();
  while (!llist.isEmpty()) {
    for (int i = 0; i < m - 1; i++) {
      pre = pre->next;
    }
    cout << pre->next->val.num << " ";
    m = pre->next->val.value;
    llist.deleteNext(pre);
  }
  return 0;
}