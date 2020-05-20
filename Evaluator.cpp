#include "Evaluator.hpp"

using std::string;
using std::stoi;

Evaluator::Evaluator() {
}

int Evaluator::compute_atom(Tokenizer t) 
{
    Token tok = t.getCurToken();
    if (tok.type == "LEFTPAREN") {
        t.advanceToNext();
        int val = compute_expr(t, 1);
        if (t.getCurToken().type != "RIGHTPAREN")
            perror("unmatched right paren");
        t.advanceToNext();
        return val;
    }
    else if (tok.type == "")
        perror("fail");
    else if (tok.type == "OPERATOR")
        perror("expected atom, got an operator");
    else {
        t.advanceToNext();
        return stoi(tok.value);
    }
}

int Evaluator::compute_expr(Tokenizer t, int min_prec)
{

}

int Evaluator::compute_op(string op, int lhs, int rhs)
{

}