#include "Tokenizer.hpp"

using std::remove_if;
using std::all_of;
using std::none_of;

/* tokenize(string): Loads input string into the string regex iterator of the class, 
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

/* tokenizerError(string): Helper function to indicate an error parsing the mathematical
 * expression, it has been found invalid. */
bool tokenizerError(string errMsg) {
    cout << errMsg << endl;
    return false;
}
/* isSupportedOperator(char): Helper function for validation. */
bool isSupportedOperator(char op) { return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^'); }

/* validateExpression(string): Checks a range of conditions that would indicate the mathematical expression is 
*  invalid before we parse it.
*  Input: input string to validate
*  Returns: double
*/
bool Tokenizer::validateExpression(string expr) {
    if (expr.length() == 0)
        return tokenizerError("Error: empty expression.");

    int leftParenCount = count(expr.begin(), expr.end(), '(');
    int rightParenCount = count(expr.begin(), expr.end(), ')');

    if (leftParenCount != rightParenCount)
        return tokenizerError("Error: expression has an uneven number of parentheses.");

    if (none_of(expr.begin(), expr.end(), ::isdigit))
        return tokenizerError("Error: expression contains no numbers.");

    // Check number of operators and numbers, since parser doesn't support negative number input there should 
    // not be two operators in a row.
    int op_count, num_count = 0;

    for (int i=0; i < expr.length(); i++) {
        if (i > 0 && expr[i-1] == '(' && expr[i] == ')')
            return tokenizerError("Error: expression contains an empty parenthesized expression.");

        if (isSupportedOperator(expr[i])) {
            op_count++;

            if (i > 0 && isSupportedOperator(expr[i-1]))
                return tokenizerError("Error: expression has two operators in a row and parsing negative numbers is not supported.");
        }
    }

    return true;
}

/* generateToken(): Extracts current matched string from class regex iterator and codifies it in a class Token object 
   according to its type. */
void Tokenizer::generateToken() {
    string cur = it->str();

    if (all_of(cur.begin(), cur.end(), ::isdigit))
        curToken = {"NUMBER", cur};
    else if (cur == "+" || cur == "*" || cur == "-" || cur == "/" || cur == "^")
        curToken = {"OPERATOR", cur};
    else if (cur == "(")
        curToken = {"LEFTPAREN", cur};
    else if (cur == ")")
        curToken = {"RIGHTPAREN", cur};
    else
        validExpression = tokenizerError("Error: Token generation failed, malformed expression.");
}

/* advanceToNext(): Increments the regex iterator to move on to the next matched string. */
void Tokenizer::advanceToNext() {
    if (++it != sregex_iterator())
        generateToken();
    else 
        curToken = {"",""};
}