#include "Evaluator.hpp"
#include <assert.h>

using std::string;
using std::stoi;

Evaluator::Evaluator() {
}

// Atoms are either numbers or parenthesized expressions
int Evaluator::compute_atom(Tokenizer* tokenizer) 
{
    Token tok = tokenizer->getCurToken();
    cout << "compute_atom called with [" << tok.type << "] [" << tok.value << "]\n";

    if (tok.type == "LEFTPAREN") {
        tokenizer->advanceToNext();
        cout << "compute_atom advanced to [" << tokenizer->getCurToken().type << "] [" << tokenizer->getCurToken().value << "]\n";
        int val = compute_expr(tokenizer, 1);

        if (tokenizer->getCurToken().type != "RIGHTPAREN")
            perror("unmatched right parenthesis");
        
        tokenizer->advanceToNext();
        return val;
    }
    else if (tok.type == "")
        perror("fail");
    else if (tok.type == "OPERATOR")
        perror("expected atom, got an operator");
    else {
        // Number
        assert(tok.type == "NUMBER");
        tokenizer->advanceToNext();
        return stoi(tok.value);
    }
}

// Expressions consist of atoms connected by operators
int Evaluator::compute_expr(Tokenizer* tokenizer, int min_prec)
{
    Token temp = tokenizer->getCurToken();
    cout << "compute_expr called with [" << temp.type << "] [" << temp.value << "]" << endl;
    int atom_lhs = compute_atom(tokenizer);

    while (true) {
        Token cur = tokenizer->getCurToken();
        cout << "cur.type [" << cur.type << "] cur.value [" << cur.value << "]" << endl;
        
        if (cur.value == "" || cur.type != "OPERATOR"
                            || opInfo.find(cur.value) == opInfo.end() // op not found
                            || opInfo[cur.value] < min_prec) // op precedence lower than min prec
            break;

        // Get operator's precedence and compute minimal precedence for recursive call
        string op = cur.value;
        int prec = opInfo[op];
        cout << "prec: " << prec << endl;
        int next_min_prec = prec + 1; // implement assoc if wanted

        // Consume current token and prepare next for recursive call
        tokenizer->advanceToNext();
        int atom_rhs = compute_expr(tokenizer, next_min_prec);

        // Update lhs with new value
        //cout << "atom_lhs " << atom_lhs << " atom_rhs " << atom_rhs << endl; 
        atom_lhs = compute_op(op, atom_lhs, atom_rhs);
        //cout << "atom_lhs result: " << atom_lhs << endl;
    }

    return atom_lhs;
}

int Evaluator::compute_op(string op, int lhs, int rhs)
{
    cout << "compute_op lhs : " << lhs << " rhs: " << rhs << endl;
    if (op == "+")
        return lhs + rhs;
    else if (op == "*")
        return lhs * rhs;
    else
        perror("unknown operator");
}