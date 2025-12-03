#include <bitset>
#include <iostream>
#include <set>
#include <stack>
#include <stddef.h>
#include <vector>

using namespace std;

template <typename T> class Node {
private:
public:
  int par_index_;
  int left_index_;
  int right_index_;
  int weight_;
  T value_;
  Node(T v = T())
      : par_index_(-1), left_index_(-1), right_index_(-1), weight_(-1),
        value_(v) {}
  Node(T v, int weight)
      : par_index_(-1), left_index_(-1), right_index_(-1), weight_(weight),
        value_(v) {}
  Node(T v, int weight, int l, int r)
      : par_index_(-1), left_index_(l), right_index_(r), weight_(weight),
        value_(v) {}
};

template <typename T> class HFMTree {
private:
  set<int> build_helper;
  int root;

  vector<Node<T> /**/> nodes_; // 万恶的c++03把泛型识别成位移
  pair<int, int> find_smallest() {
    int s1 = -1, s2 = -1;
    int weight = 0x3f3f3f3f;
    for (int i = 0; i < nodes_.size(); i++) {
      Node<T> node = nodes_[i];
      if (build_helper.find(i) != build_helper.end()) {
        continue;
      }
      if (node.weight_ < weight) {
        weight = node.weight_;
        s1 = i;
      }
    }
    weight = 0x3f3f3f3f;
    for (int i = 0; i < nodes_.size(); i++) {
      Node<T> node = nodes_[i];
      if (build_helper.find(i) != build_helper.end() || i == s1) {
        continue;
      }
      if (node.weight_ < weight) {
        weight = node.weight_;
        s2 = i;
      }
    }
    build_helper.insert(s1);
    build_helper.insert(s2);
    return pair<int, int>(s1, s2);
  }

public:
  HFMTree(int size = 10) : root(-1) { nodes_.resize(size * 2); }
  void insert(T v, int weight) { nodes_.push_back(Node<T>(v, weight)); }
  void build() {
    for (int i = 0; i < nodes_.size(); i++) {
      pair<int, int> indexes = find_smallest();
      int weight =
          nodes_[indexes.first].weight_ + nodes_[indexes.second].weight_;
      nodes_[indexes.first].par_index_ = nodes_.size();
      nodes_[indexes.second].par_index_ = nodes_.size();
      nodes_.push_back(Node<T>(T(), weight, indexes.first, indexes.second));
    }
    root = nodes_.size() - 1;
  }

  // 返回对应index所表示节点的编码的string
  string encoding(int index) {
    string path(nodes_.size() / 2);
    char one = '1';
    char zero = '0';
    stack<int> indexes;
    while (index != -1) {
      indexes.push(index);
      index = nodes_[index].par_index_;
    }
    index = root;
    while (true) {
      int i = indexes.top();
      indexes.pop();
      if (nodes_[index].left_index_ == i) {
        path.push_back(zero);
      } else if (nodes_[index].right_index_ == i) {
        path.push_back(one);
      } else {
        break;
      }
      index = i;
    }
    return path;
  }
};

int main(int argc, char const *argv[]) {
  int size;
  HFMTree<char> tree;
  cout << "please type in the number of node\n";
  cin >> size;
  cout << "please type in the node pairs\n";
  char c;
  int weight;
  for (int i = 0; i < size; i++) {
    cin >> weight >> c;
    tree.insert(c, weight);
  }
  tree.build();

  return 0;
}
