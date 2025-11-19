template <typename T> class stack {
private:
  T *elems_;
  int size_;
  int usedSize_;

  bool resize(int newSize) {
    if (newSize <= size_) {
      return false;
    }
    int preUsed = usedSize_;
    T *temp = new T[newSize];
    for (int i = 0; i < preUsed; i++) {
      temp[i] = elems_[i];
    }
    delete[] elems_;
    this->elems_ = temp;
    size_ = newSize;
    return true;
  }

public:
  stack(int size = 10) : size_(size), usedSize_(0) { elems_ = new T[size_]; }
  ~stack() { delete[] elems_; }
  int size() { return this->usedSize_; }
  bool empty() { return size() == 0; }
  T top() {
    if (empty())
      throw "Stack is empty!";
    return elems_[usedSize_ - 1];
  }
  void pop() {
    if (empty())
      throw "Nothing to pop!";
    usedSize_--;
  }
  bool push(T elem) {
    bool succ = true;
    if (size_ == usedSize_) {
      succ = resize(size_ * 2 + 1);
      if (!succ)
        return false;
    }
    elems_[usedSize_++] = elem;
    return true;
  }
};