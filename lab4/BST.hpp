#include <queue>
#include <stack>
#include <iostream>
using namespace std;

template <typename T> class BST {
public:
  BST(T val = T(), BST<T> *left = NULL, BST<T> *right = NULL)
      : value_(val), left_(left), right_(right) {}
  T value_;
  BST<T> *left_, *right_;
  ~BST() {
    if (left_) {
      delete left_;
    }
    if (right_) {
      delete right_;
    }
  }
  bool insert(T value) {
    BST<T> *tp = this;
    bool succ = false;
    while (!succ) {
      if (value > tp->value_) {
        if (tp->right_) {
          tp = tp->right_;
        } else {
          tp->right_ = new BST<T>(value);
          succ = true;
        }
      } else if (value < tp->value_) {
        if (tp->left_) {
          tp = tp->left_;
        } else {
          tp->left_ = new BST<T>(value);
          succ = true;
        }
      } else {
        return false;
      }
    }
    return true;
  }

  void inner() { RecInnerIter(this); }
  void pre() { RecPreIter(this); }
  void post() { RecPostIter(this); }
  void layerIter() {
    std::queue<BST<T>*> q;
    q.push(this);
    while (!q.empty()) {
      BST<T> *cur = q.front();
      q.pop();
      cout << cur->value_ << " ";
      if (cur->left_) {
        q.push(cur->left_);
      }
      if (cur->right_) {
        q.push(cur->right_);
      }
    }
  }
  void innerIter() {
    std::stack<BST<T>*> stk;
    BST<T> *t = this;
    while (t || !stk.empty()) {
      while (t) {
        stk.push(t);
        t = t->left_;
      }
      t = stk.top();
      stk.pop();
      cout << t->value_ << " ";
      t = t->right_;
    }
  }
  void preIter() {
    std::stack<BST<T> *> stk;
    BST<T> *t = this;
    while (t || !stk.empty()) {
      while (t) {
        cout << t->value_ << " ";
        stk.push(t);
        t = t->left_;
      }
      t = stk.top();
      stk.pop();
      t = t->right_;
    }
  }

  void postIter() {
    std::stack<BST<T>*> stk;
    BST<T> *t = this, *last = NULL;
    while (t || !stk.empty()) {
      while (t) {
        stk.push(t);
        t = t->left_;
      }
      t = stk.top();
      stk.pop();
      if (!t->right_ || t->right_ == last) {
        cout << t->value_ << " ";
        last = t;
        t = NULL;
      } else {
        stk.push(t);
        t = t->right_;
      }
    }
  }

private:
  void RecInnerIter(BST<T> *cur) {
    if (cur == NULL) {
      return;
    }
    RecInnerIter(cur->left_);
    cout << cur->value_ << " ";
    RecInnerIter(cur->right_);
  }

  void RecPreIter(BST<T> *cur) {
    if (cur == NULL) {
      return;
    }
    cout << cur->value_ << " ";
    RecPreIter(cur->left_);
    RecPreIter(cur->right_);
  }

  void RecPostIter(BST<T> *cur) {
    if (cur == NULL) {
      return;
    }
    RecPostIter(cur->left_);
    RecPostIter(cur->right_);
    cout << cur->value_ << " ";
  }
};