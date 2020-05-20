#include "Evaluator.hpp"
#include <utility>

using std::string;
using std::stoi;
using std::pair;

Evaluator::Evaluator() {
}

int Evaluator::compute_atom(Tokenizer t) 
{
    pair<string, string> tok = t.getCurToken();
    if (tok.first == "LEFTPAREN") {
        t.advanceToNext();
        int val = compute_expr(t, 1);
        if (t.getCurToken().first != "RIGHTPAREN")
            perror("unmatched right paren");
        t.advanceToNext();
        return val;
    }
    else if (tok.first == "")
        perror("fail");
    else if (tok.first == "OPERATOR")
        perror("expected atom, got an operator");
    else {
        t.advanceToNext();
        return stoi(tok.second);
    }
}

int Evaluator::compute_expr(Tokenizer t, int min_prec)
{

}

int Evaluator::compute_op(string op, int lhs, int rhs)
{

}