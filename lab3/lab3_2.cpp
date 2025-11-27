#include "stack.hpp"
#include <iostream>
#include <vector>
using namespace std;

int row, col;
vector<vector<int>> dp;
vector<vector<int>> matrix;
stack<pair<int, int>> stk;
int minSteps = -1;
bool judge(pair<int, int> pos, int currentSteps) {
  int i = pos.first, j = pos.second;

  if (i <= 0 || j <= 0) {
    return false;
  }
  if (i > row || j > col) {
    return false;
  }
  if (matrix[i][j] != 0) {
    return false;
  }
  if (dp[i][j] != 0 && dp[i][j] <= currentSteps) {
    return false;
  }
  return true;
}

int main() {
  cout << "input row and col: \n";
  cin >> row >> col;

  dp.resize(row + 2);
  matrix.resize(row + 2);
  for (int i = 0; i <= row; i++) {
    dp[i].resize(col + 2, 0);
    matrix[i].resize(col + 2, 0);
  }

  cout << "input the matrix (0=path, 1=wall): \n";
  cout << "the matrix is:\n" << endl;
  for (int i = 1; i <= row; i++) {
    for (int j = 1; j <= col; j++) {
      cin >> matrix[i][j];
      cout << matrix[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;

  stack<pair<pair<int, int>, int>> searchStack; // {{x,y}, steps}
  pair<int, int> start = {1, 1};
  pair<pair<int, int>, int> startState = {start, 1};
  searchStack.push(startState);
  dp[1][1] = 1;

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  while (!searchStack.empty()) {
    auto current = searchStack.top();
    searchStack.pop();

    int x = current.first.first;
    int y = current.first.second;
    int steps = current.second;

    if (x == row && y == col) {
      if (minSteps == -1 || steps < minSteps) {
        minSteps = steps;
      }
      continue;
    }

    // cut branch
    if (minSteps != -1 && steps >= minSteps) {
      continue;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      pair<int, int> nextPos = make_pair(nx, ny);

      if (judge(nextPos, steps + 1)) {
        dp[nx][ny] = steps + 1;
        pair<pair<int, int>, int> nextState = make_pair(nextPos, steps + 1);
        searchStack.push(nextState);
      }
    }
  }

  if (minSteps == -1) {
    cout << "No path found!" << endl;
  } else {
    cout << "Minimum steps: " << minSteps << endl;
  }

  return 0;
}
