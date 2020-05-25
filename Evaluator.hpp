#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "Tokenizer.hpp"
#include <unordered_map>
#include <string>
#include <memory>

using std::unordered_map;
using std::string;
using std::shared_ptr;

class Evaluator
{
private:
    shared_ptr<Tokenizer> internalTokenizer; // Tokenizer to be initalized by eval
    unordered_map<string, int> opInfo = {
        // Supported operators and their precedence level
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2} };

    double evalError(string errMsg);
    double computeAtom(shared_ptr<Tokenizer> tokenizer);
    double computeExpr(shared_ptr<Tokenizer> tokenizer, int min_prec);
    double computeOp(string op, double lhs, double rhs);
public:
    Evaluator();
    double eval(string expr);
};

#endif
