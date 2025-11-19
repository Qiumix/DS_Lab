#include "stack.hpp"
#include <iostream>
using namespace std;
#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2

char CHAR[HEX];

void char_init() {
  for (int i = 0; i < DEC; i++) {
    CHAR[i] = i + 48;
  }
  for (int i = 10; i < HEX; i++) {
    CHAR[i] = i + 87;
  }
}

void hex_print(long long decimal) {
  cout << "hex version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }

  stack<char> stk;
  unsigned long long pos;
  if (decimal > 0) {
    pos = decimal;
  } else {
    pos = -decimal;
  }

  while (pos) {
    stk.push(CHAR[pos % HEX]);
    pos /= HEX;
  }

  if (decimal < 0)
    cout << "-";

  while (!stk.empty()) {
    cout << stk.top();
    stk.pop();
  }
  cout << endl;
}
void oct_print(long long decimal) {
  cout << "oct version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }

  stack<char> stk;
  unsigned long long pos;
  if (decimal > 0) {
    pos = decimal;
  } else {
    pos = -decimal;
  }

  while (pos) {
    stk.push(CHAR[pos % OCT]);
    pos /= OCT;
  }

  if (decimal < 0)
    cout << "-";

  while (!stk.empty()) {
    cout << stk.top();
    stk.pop();
  }
  cout << endl;
}
void bin_print(long long decimal) {
  cout << "bin version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }

  stack<char> stk;
  unsigned long long pos;
  if (decimal > 0) {
    pos = decimal;
  } else {
    pos = -decimal;
  }

  while (pos) {
    stk.push(CHAR[pos % BIN]);
    pos /= BIN;
  }

  if (decimal < 0)
    cout << "-";

  while (!stk.empty()) {
    cout << stk.top();
    stk.pop();
  }
  cout << endl;
}

int main() {
  char_init();
  long long decimal;
  cout << "input the decimal number\n";
  cin >> decimal;
  cout << "the decimal number you input is: " << decimal << "\n";
  hex_print(decimal);
  oct_print(decimal);
  bin_print(decimal);
}