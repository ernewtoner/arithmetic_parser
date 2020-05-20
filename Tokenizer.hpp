#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <iostream>
#include <utility>
#include <regex>

using std::string;
using std::pair;
using std::make_pair;
using std::regex;
using std::sregex_iterator;
using std::cout;
using std::endl;

class Tokenizer {
private:
    sregex_iterator it, end_it;
    regex r;
    pair<string, string> curToken;
public:
    Tokenizer(string expr);
    void generateToken();
    pair<string, string> getCurToken() { return curToken; }
    void advanceToNext();
};

#endif
