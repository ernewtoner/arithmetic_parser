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
#include <utility>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <regex>

#include "Tokenizer.hpp"

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
using std::pair;
using std::make_pair;

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
    evalExpression("");
    evalExpression("(()");
    evalExpression("(())");

    //evalExpression("1");
    //evalExpression("-100");

    Tokenizer t("1 + 1");
    pair<string, string> t1 = t.getCurToken();
    cout << "getCurToken() : " << t1.first << " " << t1.second << '\n';
    t.advanceToNext();
    pair<string, string> tk2 = t.getCurToken();
    cout << "getCurToken() : " << tk2.first << " " << tk2.second << '\n';
    t.advanceToNext();
    pair<string, string> t3 = t.getCurToken();
    cout << "getCurToken() : " << t3.first << " " << t3.second << '\n';
    t.advanceToNext();
    pair<string, string> t4 = t.getCurToken();
    cout << "getCurToken(), #4 should be out : " << t4.first << " " << t4.second << '\n';

    Tokenizer t2("(3 + 4) * 6");
    pair<string, string> tok1 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok1.first << " " << tok1.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok2 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok2.first << " " << tok2.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok3 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok3.first << " " << tok3.second << '\n';
    pair<string, string> tok4 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok4.first << " " << tok4.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok5 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok5.first << " " << tok5.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok6 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok6.first << " " << tok6.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok7 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok7.first << " " << tok7.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok8 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok8.first << " " << tok8.second << '\n';
    t2.advanceToNext();
    pair<string, string> tok9 = t2.getCurToken();
    cout << "Tokenizer current token: " << tok9.first << " " << tok9.second << '\n';

    return 0;
}