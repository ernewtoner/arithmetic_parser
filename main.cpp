/*
Write a program to parse and evaluate arithmetic expressions.

Your problem should support addition and multiplication at a minimum.

You input will be text similar to the following:

1 + 1

(3 + 4) * 6

(1 * 4) + (5 * 2)

Your output should be the computed value of the expression.

Write your program in an Object Oriented fashion and be prepared to show us your code and discuss your solution.   
Do not use the "Shunting Yard" algorithm.
*/

// ""
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <regex>
#include <string.h>
#include <assert.h>
#include <limits>

#include "Tokenizer.hpp"
#include "Evaluator.hpp"

using std::string;
using std::vector;
using std::count;
using std::cout;
using std::endl;
using std::stoi;
using std::regex;
using std::sregex_iterator;
using std::remove_if;
using std::all_of;
using std::numeric_limits;

void testEvaluator(Evaluator E) {
  // Evaluator's result if anything goes wrong
  double infinity = numeric_limits<double>::infinity();

  assert(E.eval("1 + 1") == 2);
  assert(E.eval("10 + 100") == 110);
  assert(E.eval("3 * 3") == 9);
  assert(E.eval("(3 + 4) * 6") == 42);
  assert(E.eval("(1 * 4) + (5 * 2)") == 14);
  assert(E.eval("3 / 3") == 1);
  assert(E.eval("(3 / 4) * 6") == 4.5);
  assert(E.eval("(1 - 4) + (5 - 2)") == 0);
  assert(E.eval("(3) + (4) - (5 + 5)") == -3);
  assert(E.eval("()") == infinity);
  assert(E.eval("5") == 5);
  assert(E.eval("5 5 5") == 555);
  assert(E.eval("(((()") == infinity);
  assert(E.eval("(((())))") == infinity);
  assert(E.eval("a b c d e f(((())))9 3 5 85") == infinity);
  assert(E.eval("(-10 + 10) + (-100 + 100)") == infinity);
  assert(E.eval("-50 + -100") == infinity);
  assert(E.eval("3 / 0") == infinity);
  assert(E.eval("* / (-(-(-(-50)))) + + -100") == infinity);
  assert(E.eval("(()3))(") == infinity);
  assert(E.eval("((3))") == 3);
}

int main(int argc, char** argv)
{
  Evaluator E;

  if (argc < 2)
    cout << "Usage: ./evalExpression \"expression\" or ./evalExpression -test" << endl;
  else if (argc == 2 && strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-test") == 0)
    testEvaluator(E);
  else if (argc == 2)
    E.eval(string(argv[1]));

  return 0;
}