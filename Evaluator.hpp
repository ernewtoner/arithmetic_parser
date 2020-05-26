#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "Tokenizer.hpp"
#include <unordered_map>
#include <string>
#include <memory>

using std::unordered_map;
using std::string;
using std::shared_ptr;
using std::tuple;

class Evaluator
{
private:
    shared_ptr<Tokenizer> internalTokenizer; // Tokenizer to be initalized by eval
    unordered_map<string, tuple<int,string>> opInfo = {
        // Supported operators, their precedence level and associativity 
        {"+", tuple<int,string>{1, "LEFT"}},
        {"-", tuple<int,string>{1, "LEFT"}},
        {"*", tuple<int,string>{2, "LEFT"}},
        {"/", tuple<int,string>{2, "LEFT"}},
        {"^", tuple<int,string>{3, "RIGHT"}} };
    
    double evalError(string errMsg);
    double computeAtom(shared_ptr<Tokenizer> tokenizer);
    double computeExpr(shared_ptr<Tokenizer> tokenizer, int min_prec);
    double computeOp(string op, double lhs, double rhs);
public:
    double eval(string expr);
};

#endif
