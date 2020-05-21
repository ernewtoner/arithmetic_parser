#include "Tokenizer.hpp"

using std::remove_if;
using std::all_of;

Tokenizer::Tokenizer(string str) {
    // Erase expression's whitespace
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

    cout << "expr: " << str << endl;
    expr = str;

    // Match numbers, operators, and parentheses
    r = ("\\s*(?:(\\d+)|(.))");
    it = sregex_iterator(expr.begin(), expr.end(), r);

    generateToken();
}

Tokenizer::~Tokenizer() {
}

void Tokenizer::generateToken() {
    string cur = it->str();

    //cout << "Tokenizer generateToken() cur: [" << cur << "]\n";

    if (all_of(cur.begin(), cur.end(), ::isdigit))
        curToken = {"NUMBER", cur};
    else if (cur == "+" || cur == "*" || cur == "-" || cur == "/")
        curToken = {"OPERATOR", cur};
    else if (cur == "(")
        curToken = {"LEFTPAREN", cur};
    else if (cur == ")")
        curToken = {"RIGHTPAREN", cur};
    else
        cout << "Error: Malformed expression." << endl;
}

void Tokenizer::advanceToNext() {
    if (++it != sregex_iterator()) {
        //cout << "Tokenizer advanceToNext() cur: [" << it->str() << "]\n";
        generateToken();
    }
    else {
        curToken = {"",""};
        cout << "End of tokens reached." << endl;
    }
}