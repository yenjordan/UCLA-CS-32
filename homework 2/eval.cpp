#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int operatorPrecedence(char character);
bool convertToPostfix(string infix, string& postfix);
bool evaluatePostfix(string postfix);

int operatorPrecedence(char character)
{
    switch (character)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            exit(1);
    }
}

bool convertToPostfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> operatorStack;
    
    string removeSpaces = "";
    for(int i = 0; i < infix.size(); i++)
    {
        if(infix[i] == ' ')
        {
            continue;
        }
        removeSpaces += infix[i];
    }
    infix = removeSpaces;
    
    if(infix.empty())
        return false;
    
    switch (infix[0])
    {
        case '|':
        case '&':
            return false;
        default:
            break;
    }
    
    // Check end
    switch (infix[infix.size() - 1])
    {
        case '|':
        case '&':
        case '!':
        case '(':
            return false;
        default:
            break;
    }
    
    size_t infixSize = infix.size();
    for(int i = 0; i < infixSize; i++)
    {
        char character = infix[i];
        switch (character)
        {
            case 'T':
            case 'F':
                if(i + 1 < infixSize)
                {
                    switch (infix[i+1])
                        {
                            case 'T':
                            case 'F':
                            case '(':
                            case '!':
                                return false;
                            default:
                                break;
                        }
                }
                postfix += character;
                break;
                
            case '(':
            case '!':
                if(i+1 < infixSize)
                {
                    switch (infix[i+1])
                    {
                        case ')':
                        case '&':
                        case '|':
                            return false;
                        default:
                            break;
                    }
                }
                
                operatorStack.push(character);
                break;
                
            case ')':
                if(i+1 < infixSize)
                {
                    switch (infix[i+1])
                    {
                        case 'T':
                        case 'F':
                        case '(':
                            return false;
                        default:
                            break;
                    }
                }
                while(!operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if(operatorStack.empty())
                    return false;
                operatorStack.pop();
                break;
            case '&':
            case '|':
                if(i+1 < infixSize)
                {
                    switch (infix[i+1])
                    {
                        case '&':
                        case '|':
                        case ')':
                            return false;
                        default:
                            break;
                    }
                }
                
                while(!operatorStack.empty() &&
                      operatorStack.top() != '(' &&
                      operatorPrecedence(character) <= operatorPrecedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(character);
                break;
            default:
                return false;
        }
    }
    while(!operatorStack.empty())
    {
        if(operatorStack.top() == '(' || operatorStack.top() == ')')
            return false;
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return true;
}

bool evaluatePostfix(string postfix)
{
    stack<bool> operandStack;

    size_t postfixSize = postfix.size();
    for(int i = 0; i < postfixSize; i++)
    {
        char character = postfix[i];
        if (character == 'T' || character == 'F')
        {
            switch (character)
            {
                case 'T':
                    operandStack.push(true);
                    break;
                case 'F':
                    operandStack.push(false);
                    break;
            }
        }
        else if (character == '&' || character == '|')
        {
            bool secondOperand = operandStack.top();
            operandStack.pop();
            bool firstOperand = operandStack.top();
            operandStack.pop();
            switch (character) {
                case '&':
                    operandStack.push(firstOperand & secondOperand);
                    break;
                case '|':
                    operandStack.push(firstOperand | secondOperand);
                    break;
            }
        }
        else if (character == '!')
        {
            bool operandTop = operandStack.top();
            operandStack.pop();
            operandStack.push(!operandTop);
        }
        else
        {
            exit(1);
        }
    }
    return operandStack.top();
}

int evaluate(string infix, string& postfix, bool& result)
{
    if(!convertToPostfix(infix, postfix ))
    {
        return(1);
    }
    result = evaluatePostfix(postfix);
    return 0;
}

// int main()
// {
//     string pf;
//     bool answer;
//     assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
//     assert(evaluate("", pf, answer) == 1);
//     assert(evaluate("T|", pf, answer) == 1);
//     assert(evaluate("F F", pf, answer) == 1);
//     assert(evaluate("TF", pf, answer) == 1);
//     assert(evaluate("()", pf, answer) == 1);
//     assert(evaluate("()T", pf, answer) == 1);
//     assert(evaluate("T(F|T)", pf, answer) == 1);
//     assert(evaluate("T(&T)", pf, answer) == 1);
//     assert(evaluate("(T&(F|F)", pf, answer) == 1);
//     assert(evaluate("T+F", pf, answer) == 1);
//     assert(evaluate(" F  |  !F & (T&F) ", pf, answer) == 0
//                            &&  pf == "FF!TF&&|"  &&  !answer);
//     assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
//     assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
//     cout << "Passed all tests" << endl;
// }
