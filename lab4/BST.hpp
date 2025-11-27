#include <queue>
#include <stack>
using namespace std;

template <typename T> class BST {
public:
  BST(T val = T(), BST<T> *left = NULL, BST<T> *right = NULL)
      : value_(val), left_(left), right_(right) {}
  T value_;
  BST<T> *left_, *right_;
  ~BST() {
    if (left_) {
      left_->~BST();
      delete left_;
    }
    if (right_) {
      right_->~BST();
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
    std::queue<T> q;
    q.push(this);
    while (!q.empty()) {
      BST<T> *cur = q.front();
      q.pop();
      cout << q << endl;
      if (cur->left_) {
        q.push(cur->left_);
      }
      if (cur->right_) {
        q.push(cur->right_);
      }
    }
  }
  void innerIter() {
    std::stack<T> stk;
    BST<T> *t = this;
    while (t || !stk.empty()) {
      while (t) {
        stk.push(t);
        t = t->left_;
      }
      t = stk.top();
      stk.pop();
      cout << t->value_;
      t = t->right_;
    }
  }
  void preIter() {
    std::stack<BST<T> *> stk;
    BST<T> *t = this;
    while (t || !stk.empty()) {
      while (t) {
        cout << t->value_ << endl;
        stk.push(t);
        t = t->left_;
      }
      t = stk.top();
      stk.pop();
      t = t->right_;
    }
  }

  void postIter() {
    std::stack<BST *> stk;
    BST<T> *t = this, last;
    while (t || !stk.empty()) {
      while (t) {
        stk.push(t);
        t = t->left_;
      }
      t = stk.pop();
      stk.pop();
      if (!t->right_ || t->right_ == last) {
        cout << t->value_ << endl;
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
    cout << cur->value_ << endl;
    RecInnerIter(cur->right);
  }

  void RecPreIter(BST<T> *cur) {
    if (cur == NULL) {
      return;
    }
    cout << cur->value_ << endl;
    RecPreIter(cur->left_);
    RecPreIter(cur->right);
  }

  void RecPostIter(BST<T> *cur) {
    if (cur == NULL) {
      return;
    }
    RecPostIter(cur->left_);
    RecPostIter(cur->right);
    cout << cur->value_ << endl;
  }
};