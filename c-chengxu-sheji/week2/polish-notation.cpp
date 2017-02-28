// code is from http://stackoverflow.com/questions/12028960/prefix-recursion-notation-in-c
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <string>

using std::stack;
using std::string;
using std::cerr;

enum Operator {
  operator_none,
  operator_plus,
  operator_minus
};

Operator tokenOperator(const string &token)
{
  if (token=="+") return operator_plus;
  if (token=="-") return operator_minus;
  return operator_none;
}

int applyOperator(Operator op,int x,int y)
{
  switch (op) {
    case operator_plus:  return x+y;
    case operator_minus: return x-y;
    case operator_none:
      break;
  }
  assert(false);
  return 0;
}

bool isValue(const string &token,int &output_value)
{
  char *end = 0;
  errno=0;
  output_value = strtol(token.c_str(),&end,10);
  if (errno!=0) return false;
  return *end=='\0';
}

bool isOperator(const string &token,Operator &output_operator)
{
  output_operator = tokenOperator(token);
  return output_operator!=operator_none;
}

int preeval(stack<string> &stos)
{
  if (stos.empty()) return 0;

  string el = stos.top();
  stos.pop();

  int value = 0;
  Operator op = operator_none;

  if (isValue(el,value)) return value;

  if (isOperator(el,op)) {
    int x = preEval(stos);
    int y = preEval(stos);
    return applyOperator(op,x,y);
  }

  return 0;
}
