/* Eric Newton 
*  5/26/2020
*
*  Program that parses and evaluates arithmetic expressions.
*  Supports +, -, *, /, ^ and parethensized expressions.
*  Does not support parsing negative numbers or decimals, but can evaluate to them.
* 
*  Program consists of a Tokenizer class and Evaluator class, string input is passed through a 
*  Tokenizer object to be validated and codified, then the Evaluator object evaluates the expression
*  Token by Token.
*   
*/
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

/* testEvaluator(Evaluator E): Small test suite for the program as a whole */
void testEvaluator(Evaluator E) {
  // Evaluator's computed result if anything goes wrong
  double inf = numeric_limits<double>::infinity();

  // +, *, /, - and parenthesized expressions
  assert(E.eval("1 + 1") == 2);
  assert(E.eval("10 + 100") == 110);
  assert(E.eval("3 * 3") == 9);
  assert(E.eval("(3 + 4) * 6") == 42);
  assert(E.eval("(1 * 4) + (5 * 2)") == 14);
  assert(E.eval("6 * (3 + 2)") == 30);
  assert(E.eval("3 / 3") == 1);
  assert(E.eval("(3 / 4) * 6") == 4.5);
  assert(E.eval("(1 - 4) + (5 - 2)") == 0);
  assert(E.eval("(3) + (4) - (5 + 5)") == -3);

  // ^ and parenthesized expressions
  assert(E.eval("2^2^2") == 16);
  assert(E.eval("(3^2) + (4^2) - (5^2)") == 0);
  assert(E.eval("5 * ((3^2) - 100)") == -455);
  assert(E.eval("100 + 10 ^ 5") == 100100);
  assert(E.eval("10^5 * 10^5 * 10^5") == 1e+15);

  // Single numbers and invalid input
  assert(E.eval("()") == inf);
  assert(E.eval("5") == 5);
  assert(E.eval("5 5 5") == 555);
  assert(E.eval("(((()") == inf);
  assert(E.eval("(((())))") == inf);
  assert(E.eval("a b c d e f(((())))9 3 5 85") == inf);
  assert(E.eval("(-10 + 10) + (-100 + 100)") == inf);
  assert(E.eval("-50 + -100") == inf);
  assert(E.eval("3 / 0") == inf);
  assert(E.eval("* / (-(-(-(-50)))) + + -100") == inf);
  assert(E.eval("(()3))(") == inf);
  assert(E.eval("((3))") == 3);
}

int main(int argc, char** argv)
{
  Evaluator E;

  if (argc < 2 || argc > 2)
    cout << "Usage: ./evalArithmeticExpression \"expression\" or ./evalArithmeticExpression -t or -test" << endl;
  else if (argc == 2 && strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-test") == 0)
    testEvaluator(E);
  else if (argc == 2)
    E.eval(string(argv[1]));
  
  return 0;
}