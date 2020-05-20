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
#include <regex>

using std::string;
using std::vector;
using std::count;
using std::cout;
using std::endl;
using std::stoi;
using std::regex;
using std::sregex_iterator;
using std::smatch;
using std::remove_if;

class Tokenizer
{
private:
    vector<string> tokens;
    int curIndex;
    string curToken;
public:
    Tokenizer(string expr);
    string getCurToken();
    string getNextToken();
};

Tokenizer::Tokenizer(string expr)
{
    // Erase expression's whitespace
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

    // Match numbers, operators, and parentheses 
    // Store matched string tokens in object's vector
    regex r ("\\s*(?:(\\d+)|(.))"); 
    for (sregex_iterator it(expr.begin(), expr.end(), r), end_it; it != end_it; ++it)
        tokens.emplace_back(it->str());

    curIndex = 0;
    curToken = tokens[0];
}

string Tokenizer::getCurToken() { return curToken; }
string Tokenizer::getNextToken()
{
    if (curIndex != tokens.size() - 1) {
        curIndex += 1;
        curToken = tokens[curIndex];
        return curToken;
    }

    return "Error: End of tokens reached.";
}

/*void tokenize(string expr)
{
    vector<string> v;
    smatch m;
    regex r ("\\s*(?:(\\d+)|(.))");

    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

    for (sregex_iterator it(expr.begin(), expr.end(), r), end_it; it != end_it; ++it)
        v.emplace_back(it->str());
    
    for (string tok : v)
        cout << "Tok: " << tok << endl;
}*/

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

    //tokenize("1 + 1");
    Tokenizer t("1 + 1");
    cout << "Tokenizer current token: " << t.getCurToken() << endl;
    cout << "Tokenizer current token: " << t.getNextToken() << endl;
    cout << "Tokenizer current token: " << t.getNextToken() << endl;
    cout << "Tokenizer current token: " << t.getNextToken() << endl;

    Tokenizer t2("(3 + 4) * 6");
    cout << "Tokenizer current token: " << t2.getCurToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getCurToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;
    cout << "Tokenizer current token: " << t2.getNextToken() << endl;

    return 0;
}