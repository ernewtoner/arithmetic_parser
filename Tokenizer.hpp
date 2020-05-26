#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <iostream>
#include <regex>

using std::string;
using std::regex;
using std::sregex_iterator;
using std::cout;
using std::endl;

struct Token 
{
    string type; // Number, operator, leftparen or rightparen
    string value;
};

class Tokenizer {
private:
    string expr; // Mathematical expression to tokenize
    bool validExpression;
    regex r;
    sregex_iterator it;
    Token curToken; // Current processed match from regex iterator
    bool validateExpression(string expr);
    void generateToken();
public:
    Tokenizer(string expr) { tokenize(expr); }
    void tokenize(string expr);
    bool isValidExpression() { return validExpression; }
    Token getCurToken() { return curToken; }
    void advanceToNext();
};

#endif
