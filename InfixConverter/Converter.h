#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

const int VALIDCHARS_COUNT = 6;

struct Expression
{
    char value;
    Expression* left, *right;
};

class Converter
{
    public:
        Converter(); 
        int getWhichBaseOperation();
        int getWhichSecondaryOperation(int);
        void removeSpaces();
        bool balancedParenthesis();
        bool isOperator(char);
        bool isValidChar(char);
        bool validInfix();
        int getPrecedence(char);
        bool isHigherPrecedence(char, char);
        string infixToPostfix();
        bool isBase36(char);
        bool validPostfix();
        int operate(int, int, char);
        string convertToBase36(int);
        string evaluatePostfix();
        Expression* createNode(char);
        void buildExpressionTree(string);
        void inorderTraversal(Expression*);
        void postorderTraversal(Expression*);
        void preorderTraversal(Expression*);
        void convert();

    private:
        string input;
        char validChars[VALIDCHARS_COUNT];
        char *infixExpression;
        char *postfixExpression;
        Expression *expression;
};

#endif