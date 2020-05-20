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

class Tokenizer
{
private:
    vector<pair<string, string>> tokens;
    int curIndex;
    pair<string, string> curToken;
public:
    Tokenizer(string expr);
    pair<string, string> getCurToken();
    pair<string, string> getNextToken();
};

Tokenizer::Tokenizer(string expr)
{
    // Erase expression's whitespace
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

    // Match numbers, operators, and parentheses 
    // Store matched string tokens in object's vector
    regex r ("\\s*(?:(\\d+)|(.))"); 
    for (sregex_iterator it(expr.begin(), expr.end(), r), end_it; it != end_it; ++it) {
        string cur = it->str();

        if (all_of(cur.begin(), cur.end(), ::isdigit))
            tokens.emplace_back(make_pair("NUMBER", cur));
        else if (cur == "+" || cur == "*")
            tokens.emplace_back(make_pair("OPERATOR", cur));
        else if (cur == "(")
            tokens.emplace_back(make_pair("LEFTPAREN", cur));
        else if (cur == ")")
            tokens.emplace_back(make_pair("RIGHTPAREN", cur));
        else 
            // throw error
            perror("Malformed expression.");
    }

    for (pair<string, string> p : tokens)
        cout << p.first << " " << p.second << endl;

    curIndex = 0;
    curToken = tokens[0];
}

pair<string, string> Tokenizer::getCurToken() { return curToken; }
pair<string, string> Tokenizer::getNextToken() 
{
   if (curIndex != tokens.size() - 1) {
        curIndex += 1;
        curToken = tokens[curIndex];
        return curToken;
    }

    return make_pair("ERROR", "End of tokens reached.");
}

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
    cout << "Tokenizer current token: " << t.getCurToken().first << " " << t.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t.getNextToken().first << " " << t.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t.getNextToken().first << " " << t.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t.getNextToken().first << " " << t.getCurToken().second << endl;

    Tokenizer t2("(3 + 4) * 6");
    cout << "Tokenizer current token: " << t2.getCurToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;
    cout << "Tokenizer current token: " << t2.getNextToken().first << " " << t2.getCurToken().second << endl;

    return 0;
}