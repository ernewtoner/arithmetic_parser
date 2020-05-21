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
    int compute_atom(Tokenizer*);
    int compute_expr(Tokenizer*, int min_prec);
    int compute_op(string op, int lhs, int rhs);
};

#endif
