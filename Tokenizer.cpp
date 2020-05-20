#include "Tokenizer.hpp"

using std::remove_if;
using std::all_of;

Tokenizer::Tokenizer(string expr) {
    // Erase expression's whitespace
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

    // Match numbers, operators, and parentheses
    r = ("\\s*(?:(\\d+)|(.))"); 
    it = sregex_iterator(expr.begin(), expr.end(), r);

    generateToken();
}

void Tokenizer::generateToken() {
    string cur = it->str();

    if (all_of(cur.begin(), cur.end(), ::isdigit))
        curToken = make_pair("NUMBER", cur);
    else if (cur == "+" || cur == "*")
        curToken = make_pair("OPERATOR", cur);
    else if (cur == "(")
        curToken = make_pair("LEFTPAREN", cur);
    else if (cur == ")")
        curToken = make_pair("RIGHTPAREN", cur);
    else
        cout << "Error: Malformed expression." << endl;
}

void Tokenizer::advanceToNext() {
    if (++it != end_it) {
        generateToken();
    }
    else {
        curToken = make_pair("","");
        cout << "End of tokens reached." << endl;
    }
}