#include <iostream>
#include "BST.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  // 创建二叉搜索树，根节点为 50
  BST<int> *tree = new BST<int>(50);
  
  // 插入节点构建测试树
  //          50
  //        /    \
  //      30      70
  //     /  \    /  \
  //   20   40  60  80
  tree->insert(30);
  tree->insert(70);
  tree->insert(20);
  tree->insert(40);
  tree->insert(60);
  tree->insert(80);
  
  cout << "=== 递归遍历 ===" << endl;
  cout << "先序遍历 (Pre-order):" << endl;
  tree->pre();
  cout << endl;
  
  cout << "\n中序遍历 (In-order):" << endl;
  tree->inner();
  cout << endl;
  
  cout << "\n后序遍历 (Post-order):" << endl;
  tree->post();
  cout << endl;
  
  cout << "\n=== 非递归遍历 ===" << endl;
  cout << "先序遍历 (Pre-order Iterative):" << endl;
  tree->preIter();
  cout << endl;
  
  cout << "\n中序遍历 (In-order Iterative):" << endl;
  tree->innerIter();
  cout << endl;
  
  cout << "\n后序遍历 (Post-order Iterative):" << endl;
  tree->postIter();
  cout << endl;
  
  cout << "\n层序遍历 (Level-order):" << endl;
  tree->layerIter();
  cout << endl;
  
  delete tree;
  return 0;
}
