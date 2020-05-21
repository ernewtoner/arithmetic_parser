#include "Tokenizer.hpp"

using std::remove_if;
using std::all_of;

Tokenizer::Tokenizer(string expr) {
    // Erase expression's whitespace
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());

    cout << "expr: " << expr << endl;
    expression = new string;
    *expression = expr;

    // Match numbers, operators, and parentheses
    r = new regex("\\s*(?:(\\d+)|(.))");
    it = new sregex_iterator(expression->begin(), expression->end(), *r);

    curToken = new Token;
    generateToken();
}

Tokenizer::~Tokenizer() {
    delete curToken;
    delete r;
    delete it;
    delete expression;
}

void Tokenizer::generateToken() {
    string cur = (*it)->str();

    cout << "Tokenizer generateToken() cur: [" << cur << "]\n";

    if (all_of(cur.begin(), cur.end(), ::isdigit))
        *curToken = {"NUMBER", cur};
    else if (cur == "+" || cur == "*")
        *curToken = {"OPERATOR", cur};
    else if (cur == "(")
        *curToken = {"LEFTPAREN", cur};
    else if (cur == ")")
        *curToken = {"RIGHTPAREN", cur};
    else
        cout << "Error: Malformed expression." << endl;
}

void Tokenizer::advanceToNext() {
    if (++(*it)!= sregex_iterator({})) {
        //cout << "Tokenizer advanceToNext() cur: [" << it->str() << "]\n";
        generateToken();
    }
    else {
        *curToken = {"",""};
        cout << "End of tokens reached." << endl;
    }
}