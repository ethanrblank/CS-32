#include <iostream>
#include <string>
#include <cassert>
#include <stack>

using namespace std;

bool is_operator(const char i);
bool is_operand(const char i);
int operator_value(const char i);
int evaluate(string infix, const bool values[], string& postfix, bool& result);
bool is_valid_syntax(const string& infix);
int cast(const char c);

int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/


bool is_valid_syntax(const string& infix) {
    // Initial test condition for an empty string
    if (infix.size() == 0)
        return false;
   
    // Create a new string without spaces so that syntax is easier to evaluate
    string adjust = "";
    for (int i = 0; i < infix.size(); ++i) {
        if (infix[i] != ' ')
            adjust += infix[i];
    }
    
    // count how many ( are in the infix statement
    int open_paren_counter = 0;
    for (int i = 0; i < adjust.size(); ++i) {
        if (adjust[i] == '(')
            ++open_paren_counter;
    }
    
    // count how many ) are in the infix statement
    int close_paren_counter = 0;
    for (int i = 0; i < adjust.size(); ++i) {
        if (adjust[i] == ')')
            ++close_paren_counter;
    }
    
    // if the parentheses counters don't match, then the infix statement is not syntactically correct
    if (open_paren_counter != close_paren_counter)
        return false;
    
    // If an operator is at the beginning or end of the statment, it is invalid
    if (adjust[0] == '&' || adjust[0] == '|' || adjust[adjust.size()-1] == '&' || adjust[adjust.size()-1] == '|')
        return false;
    
    for (int i = 0; i < adjust.size(); ++i) {
        char loc = adjust[i];
        
        if (is_operand(loc) && is_operand(adjust[i+1])) // if two numbers are right next to each other, not syntactically valid
            return false;
        if ((loc == '|' || loc == '&') && (operator_value(adjust[i+1]) == 2 || operator_value(adjust[i+1]) == 1)) // if two operators are right next to each other
            return false;
        if (loc == '(' && adjust[i+1] == ')') // if the infix reads "()"
            return false;
        if ((is_operand(loc) && adjust[i+1] == '(') || (loc == ')' && is_operand(adjust[i+1])))
            return false;
    }
    return true;
}

/** Function casts a char variable as an int so that the eval function can index correctly **/
int cast(const char c) {
    switch (c) {
        case '0': {
            return 0;
            break;
        }
        case '1': {
            return 1;
            break;
        }
        case '2': {
            return 2;
            break;
        }
        case '3': {
            return 3;
            break;
        }
        case '4': {
            return 4;
            break;
        }
        case '5': {
            return 5;
            break;
        }
        case '6': {
            return 6;
            break;
        }
        case '7': {
            return 7;
            break;
        }
        case '8': {
            return 8;
            break;
        }
        case '9': {
            return 9;
            break;
        }
        default: {
            return -1;
            break;
        }
    }
}

/** determines whether or not a char is an operator, if yes, then the function returns true. used later in the eval function **/
bool is_operator(const char i) {
    if (i == '!' || i == '&' || i == '|') {
        return true;
    }
    return false;
}

/** Checks to see if a char is a number, if yes then it returns true. **/
bool is_operand(const char i) {
    if (i == '0' || i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8' || i == '9')
        return true;
    return false;
}

//** useful for setting the precedence of operators. if character is not an operator, it returns 0 **/
int operator_value(const char i) {
    int num = 0;
    switch (i) {
        case '!': {
            num = 3;
            break;
        }
        case '&' : {
            num = 2;
            break;
        }
        case '|': {
            num = 1;
            break;
        }
            
        default:
            break;
    }
    return num;
}


// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)

int evaluate(string infix, const bool values[], string& postfix, bool& result) {
    if (!is_valid_syntax(infix)) // first check to see if it is valid, if not exit function and return 1
        return 1;
    
    else {
        stack<char> operator_stack; // initialize stack
        postfix = ""; // intialize postfix string
        
        for (size_t i = 0; i < infix.size(); ++i) { // cycle through the infix to convert it to postfix
            switch (infix[i]) {
                case '(': {
                    operator_stack.push(infix[i]);
                    break;
                }
                case ')': {
                    while (operator_stack.top() != '(') {
                        postfix.push_back(operator_stack.top()); // append contents to the postfix string
                        operator_stack.pop();
                    }
                    operator_stack.pop();
                }
                default: {
                    if (is_operator(infix[i])) {
                        while (!(operator_stack.empty()) && operator_stack.top() != '(' && (operator_value(infix[i]) <= operator_value(operator_stack.top()))) {
                            postfix.push_back(operator_stack.top()); // append contents to postfix string
                            operator_stack.pop();
                        }
                        operator_stack.push(infix[i]);
                        break;
                    }
                    else if (is_operand(infix[i])) {
                        postfix.push_back(infix[i]);
                        break;
                    }
                    else
                        break;
                }
            }
        }
        while (!(operator_stack.empty())) {
            postfix.push_back(operator_stack.top()); // complete the postfix string
            operator_stack.pop();
        }
        
        // FULLY CONVERTED TO POSTFIX NOTATION, NOW EVALUATE
        stack<char> operand_stack;
        for (size_t i = 0; i < postfix.size(); ++i) {
            if (is_operand(postfix[i]) || postfix[i] == '!') {
                if (postfix[i] != '!') {
                    operand_stack.push(postfix[i]);
                }
                else {
                    char operand_index = operand_stack.top();
                    bool operand = false;
                    if (operand_index != 't' && operand_index != 'f') {
                        operand = values[cast(operand_index)];
                    }
                    else if (operand_index == 't') {
                        operand = true;
                    }
                    operand_stack.pop();
                    if (!operand)
                        operand_stack.push('t');
                    else
                        operand_stack.push('f');
                    
                }
            }
            
            // I used 't' or 'f' instead of 1 or 0 so they would not be misconstrued as indices
            else {
                char operand2_index = operand_stack.top();
                bool operand2 = false;
                if (operand2_index != 't' && operand2_index != 'f') {
                    operand2 = values[cast(operand2_index)];
                }
                else if (operand2_index == 't') {
                    operand2 = true;
                }
                operand_stack.pop();
                char operand1_index = operand_stack.top();
                bool operand1 = false;
                if (operand1_index != 't' && operand1_index != 'f') {
                    operand1 = values[cast(operand1_index)];
                }
                else if (operand1_index == 't') {
                    operand1 = true;
                }
                operand_stack.pop();
                int rank = operator_value(postfix[i]);
                switch (rank) {
                    case 2: {
                        if (operand1&operand2)
                           operand_stack.push('t');
                        else
                            operand_stack.push('f');
                        break;
                    }
                    case 1: {
                        if (operand1|operand2)
                            operand_stack.push('t');
                        else
                            operand_stack.push('f');
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        if (operand_stack.top() != 'f' && operand_stack.top() != 't') {
            result = values[cast(operand_stack.top())];
        }
        else if (operand_stack.top() == 't')
            result = true;
        else
            result = false;
        return 0;
    }
}

