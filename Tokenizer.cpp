#include "Tokenizer.hpp"

using std::remove_if;
using std::all_of;
using std::none_of;

/* tokenize(string): Parses input string into the string regex iterator of the class, 
*  provided the string is a valid mathematical expression.
*  Input: input string to be parsed as mathematical expression.
*/
void Tokenizer::tokenize(string inputStr) {
     // Erase expression's whitespace
    inputStr.erase(remove_if(inputStr.begin(), inputStr.end(), isspace), inputStr.end());

    cout << "Parsing expression: " << inputStr << endl;
    if (validateExpression(inputStr)) {
        validExpression = true;
        expr = inputStr;
    }
    else {
        validExpression = false;
        return;
    }

    // Match numbers, operators, and parentheses
    r = ("\\s*(?:(\\d+)|(.))");
    it = sregex_iterator(expr.begin(), expr.end(), r);

    generateToken();
}

/* isSupportedOperator(char op): Small helper function for validation */
bool isSupportedOperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

/* isSupportedOperator(char op): Small helper function for validation */
bool tokenizerError(string errMsg) {
    cout << errMsg << endl;
    return false;
}

/* validateExpression(string): Verifies that the input string is a valid mathematical 
*  expression.
*  Input: input string to validate
*  Returns: double
*/
bool Tokenizer::validateExpression(string expr) {
    // Check if empty
    if (expr.length() == 0)
        return tokenizerError("Error: empty expression.");

    // Check paren count
    int leftParenCount = count(expr.begin(), expr.end(), '(');
    int rightParenCount = count(expr.begin(), expr.end(), ')');

    if (leftParenCount != rightParenCount)
        return tokenizerError("Error: expression has an uneven number of parentheses.");

    // Check if any numbers
    if (none_of(expr.begin(), expr.end(), ::isdigit))
        return tokenizerError("Error: expression contains no numbers.");

    // Check number of operators and numbers, since parser doesn't support negative numbers there should not be
    // two operators in a row.
    int op_count = 0;
    int num_count = 0;

    for (int i=0; i < expr.length(); i++) {
        if (i > 0 && expr[i-1] == '(' && expr[i] == ')')
            return tokenizerError("Error: expression contains an empty parenthesized expression.");

        if (isSupportedOperator(expr[i])) {
            op_count++;

            // Check for two operators in a row
            if (i > 0 && isSupportedOperator(expr[i-1]))
                return tokenizerError("Error: expression has two operators in a row and parsing negative numbers is not supported.");
        }
    }

    return true;
}

/* compute_expr(): Computes the value of an expression, which consists of
*  atoms connected by operators.
*  Input: pointer to Tokenizer object
*  Returns: double
*/
void Tokenizer::generateToken() {
    string cur = it->str();
    //cout << "Tokenizer generateToken() cur: [" << cur << "]\n";

    if (all_of(cur.begin(), cur.end(), ::isdigit))
        curToken = {"NUMBER", cur};
    else if (cur == "+" || cur == "*" || cur == "-" || cur == "/")
        curToken = {"OPERATOR", cur};
    else if (cur == "(")
        curToken = {"LEFTPAREN", cur};
    else if (cur == ")")
        curToken = {"RIGHTPAREN", cur};
    else {
        cout << "Error: Token generation failed, malformed expression." << endl;
        validExpression = false;
    }
}

/* compute_expr(): Computes the value of an expression, which consists of
*  atoms connected by operators.
*  Input: pointer to Tokenizer object
*  Returns: double
*/
void Tokenizer::advanceToNext() {
    if (++it != sregex_iterator()) {
        generateToken();
    }
    else {
        curToken = {"",""};
    }
}