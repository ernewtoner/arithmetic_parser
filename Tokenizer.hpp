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
    string type;
    string value;
};

class Tokenizer {
private:
    sregex_iterator it, end_it;
    regex r;
    Token curToken;
public:
    Tokenizer(string expr);
    void generateToken();
    Token getCurToken() { return curToken; }
    void advanceToNext();
};

#endif
