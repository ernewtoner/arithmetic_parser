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
using std::ispunct;

void checkIfValidExpression(string expr) 
{
    if (expr.length() == 0)
        cout << "Error: Empty expression" << endl;

    int leftParenCount = count(expr.begin(), expr.end(), '(');
    int rightParenCount = count(expr.begin(), expr.end(), ')');

    if (leftParenCount != rightParenCount) {
        cout << "Error: " << expr << " is malformed." << endl;
        //exit(1);
    }

    // If operator count != number of operands - 1
    //     malformed
}

void evalExpression(string expr)
{
    //cout << expr << endl;
    //cout << expr.length() << endl;

    if (expr.length() == 1)
        cout << stoi(expr) << endl; // Expression in int form

    checkIfValidExpression(expr);

}

int main(int argc, char** argv)
{
    //evalExpression("");
    //evalExpression("(()");
    //evalExpression("(())");

    //evalExpression("1");
    //evalExpression("-100");

   /* Tokenizer t("1 + 1");
    Token t1 = t.getCurToken();
    cout << "getCurToken() : " << t1.type << " " << t1.value << '\n';
    t.advanceToNext();
    Token tk2 = t.getCurToken();
    cout << "getCurToken() : " << tk2.type << " " << tk2.value << '\n';
    t.advanceToNext();
    Token t3 = t.getCurToken();
    cout << "getCurToken() : " << t3.type << " " << t3.value << '\n';
    t.advanceToNext();
    Token t4 = t.getCurToken();
    cout << "getCurToken(), #4 should be out : " << t4.type << " " << t4.value << '\n' << '\n';*/

    Evaluator e;
    Tokenizer* t2 = new Tokenizer("1 + 1");
    double result = e.compute_expr(t2, 1);
    cout << ">>>> 1 + 1 result <<<< " << result << endl;

    Tokenizer* t3 = new Tokenizer("3 * 3");
    result = e.compute_expr(t3, 1);
    cout << ">>>> 3 * 3 result <<<< " << result << endl;

    Tokenizer* t4 = new Tokenizer("(3 + 4) * 6");
    result = e.compute_expr(t4, 1);
    cout << ">>>> (3 + 4) * 6 result <<<< " << result << endl;

    Tokenizer t5("(1 * 4) + (5 * 2)");
    result = e.compute_expr(&t5, 1);
    cout << ">>>> (1 * 4) + (5 * 2) result <<<< " << result << endl;

    Tokenizer* t6 = new Tokenizer("3 / 3");
    result = e.compute_expr(t6, 1);
    cout << ">>>> 3 / 3 result <<<< " << result << endl;

    Tokenizer* t7 = new Tokenizer("(3 / 4) * 6");
    result = e.compute_expr(t7, 1);
    cout << ">>>> (3 / 4) * 6 result <<<< " << result << endl;

    Tokenizer t8("(1 - 4) + (5 - 2)");
    result = e.compute_expr(&t8, 1);
    cout << ">>>> (1 - 4) + (5 - 2) result <<<< " << result << endl;

    //Tokenizer t5("(1 * 4) + (5 * 2)");
    //t5->getCurToken();
    //t5.advanceToNext();
    //t5->getCurToken();

   /* Tokenizer t2("(3 + 4) * 6");
    Token tok1 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok1.type << " " << tok1.value << '\n';
    t2.advanceToNext();
    Token tok2 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok2.type << " " << tok2.value << '\n';
    t2.advanceToNext();
    Token tok3 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok3.type << " " << tok3.value << '\n';
    Token tok4 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok4.type << " " << tok4.value << '\n';
    t2.advanceToNext();
    Token tok5 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok5.type << " " << tok5.value << '\n';
    t2.advanceToNext();
    Token tok6 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok6.type << " " << tok6.value << '\n';
    t2.advanceToNext();
    Token tok7 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok7.type << " " << tok7.value << '\n';
    t2.advanceToNext();
    Token tok8 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok8.type << " " << tok8.value << '\n';
    t2.advanceToNext();
    Token tok9 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok9.type << " " << tok9.value << '\n';*/

    return 0;
}