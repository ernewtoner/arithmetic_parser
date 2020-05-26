#include "Evaluator.hpp"
#include <limits>
#include <assert.h>
#include <cmath>

using std::string;
using std::stol;
using std::make_shared;
using std::numeric_limits;
using std::get;
using std::tie;
using std::pow;

/* evalError(string): Helper function indicating the class encountered an error.
*  Input: string error message to print
*  Returns: double indicating error (infinity)
*/
double Evaluator::evalError(string errMsg) {
    // Reset Tokenizer shared pointer as it is no longer needed
    internalTokenizer.reset();
    
    if (errMsg != "default") 
        cout << errMsg << endl << endl;
    else 
        cout << "Invalid expression, returning error code inf." << endl << endl;

    return numeric_limits<double>::infinity();
}

/* eval(string): Begins evaluation by first instantiating a Tokenizer to parse the 
*  expression then passing that to computeExpr().)
*  Input: string containing mathematical expression
*  Returns: a double, the result of calculation 
*/
double Evaluator::eval(string expr) {
    internalTokenizer = make_shared<Tokenizer>(expr);

    if (internalTokenizer->isValidExpression() == false) {
        return evalError("Invalid expression.");
    }

    double result = computeExpr(internalTokenizer, 1); 
    cout << "Result: " << result << endl << endl;

    return result;
}

/******************************************************************************************
*  The algorithm used here is called precedence climbing, a recursive descent algorithm.
*  See https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm and 
*  https://en.wikipedia.org/wiki/Operator-precedence_parser#Precedence_climbing_method 
*  for a lot more information.
*  
*  In short, the expression is evaluated as collections of nested sub-expressions each with
*  their according precedence level.
*******************************************************************************************/

/* computeAtom(shared_ptr<Tokenizer>): Computes the value of an atom, which is either numbers 
*  or parenthesized expressions.
*  Input: shared_ptr to Tokenizer object
*  Returns: a double, the result of the calculation
*/
double Evaluator::computeAtom(shared_ptr<Tokenizer> tokenizer) {
    Token tok = tokenizer->getCurToken();
    
    if (tok.type == "LEFTPAREN") {
        tokenizer->advanceToNext();
        double val = computeExpr(tokenizer, 1); // 1 is the lowest precedence (+, -)

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
        // Must be a number
        assert(tok.type == "NUMBER");
        tokenizer->advanceToNext();
        return stoll(tok.value);
    }
}

/* computeExpr(shared_ptr<Tokenizer>, int): Computes the value of an expression, which consists of
*  atoms connected by operators.
*  Input: shared_ptr to Tokenizer object, integer indicating minimal precedence level
*  Returns: double
*/
double Evaluator::computeExpr(shared_ptr<Tokenizer> tokenizer, int min_prec) {
    double atom_lhs = computeAtom(tokenizer);

    while (true) {
        Token cur = tokenizer->getCurToken();
        
        if (cur.value == "" || cur.type != "OPERATOR"
                            || opInfo.find(cur.value) == opInfo.end() // op not found
                            || get<0>(opInfo[cur.value]) < min_prec) // op precedence lower than min prec
            break;

        // Get operator's precedence and associativity, compute minimal precedence for recursive call
        string op = cur.value;
        int prec, next_min_prec; string assoc;
        tie(prec, assoc) = opInfo[op];

        if (assoc == "LEFT") 
            next_min_prec = prec + 1;
        else 
            next_min_prec = prec;

        // Consume current token and prepare next for recursive call
        tokenizer->advanceToNext();
        double atom_rhs = computeExpr(tokenizer, next_min_prec);

        // Update lhs with new value
        atom_lhs = computeOp(op, atom_lhs, atom_rhs);
    }

    return atom_lhs;
}

/* computeOp(): Performs the actual arithmetic of the mathematical expression.
*  Input: string containing operator, two doubles for left and right hand side of expression
*  Returns: double, result of the arithmetic.
*/
double Evaluator::computeOp(string op, double lhs, double rhs) {
    internalTokenizer.reset(); // Tokenizer no longer needed

    if (op == "+")
        return lhs + rhs;
    else if (op == "-")
        return lhs - rhs;
    else if (op == "*")
        return lhs * rhs;
    else if (op == "/")
        return lhs / rhs;
    else if (op == "^")
        return pow(lhs, rhs);
    else
        return evalError("Unknown operator.");
}