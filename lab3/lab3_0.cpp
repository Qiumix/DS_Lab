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

unsigned long long decimal_hanlder(long long decimal) {
  unsigned long long pos;
  if (decimal > 0) {
    pos = decimal;
  } else {
    pos = -decimal;
  }
  return pos;
}

void print(int pass, long long decimal) {
  stack<char> stk;
  unsigned long long pos = decimal_hanlder(decimal);

  while (pos) {
    stk.push(CHAR[pos % pass]);
    pos /= pass;
  }

  if (decimal < 0)
    cout << "-";

  while (!stk.empty()) {
    cout << stk.top();
    stk.pop();
  }
  cout << endl;
}

void hex_print(long long decimal) {
  cout << "hex version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }
  print(HEX, decimal);
}
void oct_print(long long decimal) {
  cout << "oct version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }
  print(OCT, decimal);
}
void bin_print(long long decimal) {
  cout << "bin version: ";
  if (decimal == 0) {
    cout << "0\n";
    return;
  }
  print(BIN, decimal);
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