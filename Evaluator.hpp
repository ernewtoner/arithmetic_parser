#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "Tokenizer.hpp"
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class Evaluator
{
private:
    // Supported operators and their precedence level
    unordered_map<string, int> opInfo = {
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2} };
public:
    Evaluator();
    double compute_atom(Tokenizer*);
    double compute_expr(Tokenizer*, int min_prec);
    double compute_op(string op, double lhs, double rhs);
};

#endif
