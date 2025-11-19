#include "stack.hpp"
#include <iostream>
using namespace std;

template <typename T> class queue {
private:
  stack<T> *in_;
  stack<T> *out_;
  int size_;
  void move() {
    if (out_->empty()) { // 只在 out_ 为空时转移
      while (!in_->empty()) {
        out_->push(in_->top());
        in_->pop();
      }
    }
  }

public:
  queue() : size_(0) {
    in_ = new stack<T>();
    out_ = new stack<T>();
  }
  ~queue() {
    delete in_;
    delete out_;
  }
  int size() { return this->size_; }
  bool empty() { return size() == 0; }
  T front() {
    if (empty()) {
      throw "Queue is empty!";
    }
    move();
    return out_->top();
  }
  void pop() {
    if (empty()) {
      throw "Nothing to pop!";
    }
    move();
    out_->pop();
    size_--;
  }
  bool push(T elem) {
    bool success = in_->push(elem);
    if (success) {
      size_++;
    }
    return success;
  }
};

enum TYPE {
  NONE,       // init
  BRACKETL,   // (
  BRACKETR,   // )
  WHITESPACE, // blank
  DOT,        // .
  NUM,        // 0-9
  NEG,        // -
  MIN,        // -
  ADD,        // +
  MUL,        // *
  MOD,        // %
  DIV,        // /
};

TYPE judgeType(char input, TYPE preType) {
  switch (input) {
  case '(':
    return BRACKETL;
  case ')':
    return BRACKETR;
  case '.':
    return DOT;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return NUM;
  case '-':
    if (preType == BRACKETR || preType == NUM || preType == DOT)
      return MIN;
    else
      return NEG;
  case '+':
    return ADD;
  case '%':
    return MOD;
  case '/':
    return DIV;
  case '*':
    return MUL;
  default:
    return WHITESPACE;
  }
}

int getPriority(TYPE op) {
  switch (op) {
  case NEG:
    return 4;
  case MUL:
  case DIV:
  case MOD:
    return 3;
  case ADD:
  case MIN:
    return 2;
  case BRACKETL:
    return 1;
  default:
    return 0;
  }
}

double getNum(queue<char> &queue) {
  double integerPart = 0.0;
  double decimalPart = 0.0;
  double decimalWeight = 0.1;
  bool hasDot = false;

  while (!queue.empty()) {
    char c = queue.front();
    queue.pop();
    if (c == '.') {
      hasDot = true;
      continue;
    }
    int digit = c - '0';
    if (!hasDot) {
      integerPart = integerPart * 10 + digit;
    } else {
      decimalPart += digit * decimalWeight;
      decimalWeight *= 0.1;
    }
  }
  return integerPart + decimalPart;
}

// Bug 1 修复: calculate() 函数
void calculate(stack<double> &operandStack, TYPE op) {
  if (op == NEG) {
    double val = operandStack.top();
    operandStack.pop();
    operandStack.push(-val);
    return;
  }
  double b = operandStack.top();
  operandStack.pop();
  double a = operandStack.top();
  operandStack.pop();
  double res;
  switch (op) {
  case ADD:
    res = a + b;
    break;
  case MIN:
    res = a - b;
    break;
  case MUL:
    res = a * b;
    break;
  case DIV:
    res = a / b;
    break;
  case MOD:
    res = (int)a % (int)b;
    break;
  default:
    break;
  }

  operandStack.push(res);
}

int main() {
  stack<double> operandStack;
  stack<TYPE> operatorStack;
  queue<char> digitQueue;
  char input;
  TYPE preType = NONE;

  while (std::cin.get(input)) { // 使用 get() 而不是 >>
    if (input == '\n')
      break; // 遇到换行符停止

    TYPE curType = judgeType(input, preType);
    if (curType == WHITESPACE)
      continue;
    preType = curType;

    if (curType == DOT || curType == NUM) {
      digitQueue.push(input);
      continue;
    }

    if (!digitQueue.empty()) {
      operandStack.push(getNum(digitQueue));
    }

    switch (curType) {
    case BRACKETL:
      operatorStack.push(BRACKETL);
      break;
    case BRACKETR:
      while (operatorStack.top() != BRACKETL) {
        calculate(operandStack, operatorStack.top());
        operatorStack.pop();
      }
      operatorStack.pop();
      break;
    case ADD:
    case MIN:
    case MUL:
    case DIV:
    case MOD:
    case NEG:
      while (!operatorStack.empty() && operatorStack.top() != BRACKETL) {
        TYPE topOp = operatorStack.top();
        int curPri = getPriority(curType), topPri = getPriority(topOp);
        if ((curType != NEG && topPri >= curPri) ||
            (curType == NEG && topPri > curPri)) {
          calculate(operandStack, operatorStack.top());
          operatorStack.pop();
        } else
          break;
      }
      operatorStack.push(curType);
      break;
    default:
      break;
    }
  }

  if (!digitQueue.empty()) {
    operandStack.push(getNum(digitQueue));
  }

  while (!operatorStack.empty()) {
    calculate(operandStack, operatorStack.top());
    operatorStack.pop();
  }

  printf("%.2f\n", operandStack.top());
  return 0;
}