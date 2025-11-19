#include "stack.hpp"
#include <iostream>
#include <vector>
using namespace std;

int row, col;
vector<vector<int> /* */> dp(row);
vector<vector<int> /* */> matrix(row);
// comment to prevent c++03 generic error
stack<pair<int, int> /* */> stk;
bool judge(pair<int, int> pos) {
  if (pos.first <= 0 || pos.second <= 0) {
    return false;
  }
  if (pos.first > row || pos.second > col) {
    return false;
  }
  if (matrix[pos.first][pos.second] != 0) {
    return false;
  }
  if (dp[pos.first][pos.second] != 0) {
    return false;
  }
  return true;
}

int main() {
  cout << "input row and col: \n";
  cin >> row >> col;

  for (int i = 0; i < row + 1; i++) {
    vector<int> temp1(col);
    vector<int> temp2(col);
    dp[i] = temp1;
    matrix[i] = temp2;
  }

  cout << "input the matirx: \n";
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      cin >> matrix[i][j];
    }
  }
  stk.push({0, 0});
}
