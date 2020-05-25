#include "Evaluator.hpp"
#include <limits>
#include <assert.h>

using std::string;
using std::stol;
using std::make_shared;
using std::numeric_limits;

Evaluator::Evaluator() {
}

double Evaluator::evalError(string errMsg) {
    internalTokenizer.reset();
    
    if (errMsg != "default")
        cout << errMsg << endl << endl;
    else
        cout << "Invalid expression, returning error code inf." << endl << endl;

    return numeric_limits<double>::infinity();
}

double Evaluator::eval(string expr) {
    internalTokenizer = make_shared<Tokenizer>(expr);

    if (internalTokenizer->isValidExpression() == false) {
        return evalError("Invalid expression.");
    }

    double result = computeExpr(internalTokenizer, 1); 
    cout << "Result: " << result << endl << endl;

    return result;
}

/* computeAtom(): Computes the value of an atom, which is either numbers 
*  or parenthesized expressions.
*  Input: pointer to Tokenizer object
*  Returns: double 
*/
double Evaluator::computeAtom(shared_ptr<Tokenizer> tokenizer) {
    Token tok = tokenizer->getCurToken();
    
    if (tok.type == "LEFTPAREN") {
        tokenizer->advanceToNext();
        double val = computeExpr(tokenizer, 1);

        if (tokenizer->getCurToken().type != "RIGHTPAREN") {
             return evalError("Unmatched left parenthesis.");
        }
           
        tokenizer->advanceToNext();
        return val;
    }
    else if (tok.type == "")
        return evalError("Malformed token.");
    else if (tok.type == "OPERATOR")
        return evalError("Expected atom, got an operator.");
    else {
        // Number
        assert(tok.type == "NUMBER");
        tokenizer->advanceToNext();
        return stoll(tok.value);
    }
}

/* computeExpr(): Computes the value of an expression, which consists of
*  atoms connected by operators.
*  Input: pointer to Tokenizer object
*  Returns: double
*/
double Evaluator::computeExpr(shared_ptr<Tokenizer> tokenizer, int min_prec) {
    double atom_lhs = computeAtom(tokenizer);

    while (true) {
        Token cur = tokenizer->getCurToken();
        
        if (cur.value == "" || cur.type != "OPERATOR"
                            || opInfo.find(cur.value) == opInfo.end() // op not found
                            || opInfo[cur.value] < min_prec) // op precedence lower than min prec
            break;

        // Get operator's precedence and compute minimal precedence for recursive call
        string op = cur.value;
        int prec = opInfo[op];

        int next_min_prec = prec + 1; // implement assoc if wanted

        // Consume current token and prepare next for recursive call
        tokenizer->advanceToNext();
        double atom_rhs = computeExpr(tokenizer, next_min_prec);

        // Update lhs with new value
        atom_lhs = computeOp(op, atom_lhs, atom_rhs);
    }

    return atom_lhs;
}

/* computeOp(): Performs the actual arithmetic of the mathematical expression.
*  Input: string containing operator, left and right hand side of expression
*  Returns: double
*/
double Evaluator::computeOp(string op, double lhs, double rhs) {
    internalTokenizer.reset();

    if (op == "+")
        return lhs + rhs;
    else if (op == "-")
        return lhs - rhs;
    else if (op == "*")
        return lhs * rhs;
    else if (op == "/")
        return lhs / rhs;
    else
        return evalError("Unknown operator.");
}