#include "Converter.h"

Converter:: Converter()
{
    validChars[0] = '+';
    validChars[1] = '-';
    validChars[2] = '/';
    validChars[3] = '*';
    validChars[4] = '(';
    validChars[5] = ')';
}

//-----------------------------------------------------------------------|
//                                                                       |
// Prompts the user for the type of operation that they would like to do.|
//                                                                       |
//-----------------------------------------------------------------------|

int Converter:: getWhichBaseOperation()
{
    string operationNumber;

    cout << endl << "Please select the type of operation you would like to perform." << endl;
    cout << "|----------------------------------------------|" << endl;
    cout << "| (0): Exit the program                        |" << endl;
    cout << "| (1): Input an infix expression               |" << endl;
    cout << "| (2): Input a postfix expression              |" << endl;
    cout << "|----------------------------------------------|" << endl;

    cout << "Operation # -> ";
    getline(cin, operationNumber);

    while (operationNumber.length() > 1 
           || !isdigit(operationNumber[0]) 
           || stoi(operationNumber) > 3 
           || stoi(operationNumber) < 0)
    {
        cout << "Invalid input! Please enter a number between 0 and 2 -> ";
        cin.clear();
        getline(cin, operationNumber);
    }

    return stoi(operationNumber);
}

//-----------------------------------------------------------------------|
//                                                                       |
// Prompts the user for the type of secondary operation.                 |
//                                                                       |
//-----------------------------------------------------------------------|

int Converter:: getWhichSecondaryOperation(int input)
{
    string operationNumber;
    int selection;

    switch (input)
    {
    case 0:
        selection = stoi(operationNumber);
        break;

    case 1:
        cout << endl << "Please select the type of (infix) operation you would like to perform." << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "| (0): Return to previous menu                 |" << endl;
        cout << "| (1): Print Postfix expression                |" << endl;
        cout << "| (2): Print postix expression, preorder,      |" << endl;
        cout << "|      inorder, postorder, and evaluate the    |" << endl;
        cout << "|      expression                              |" << endl;
        cout << "|----------------------------------------------|" << endl;

        cout << "Operation # -> ";
        getline(cin, operationNumber);

        while (operationNumber.length() > 1 
            || !isdigit(operationNumber[0]) 
            || stoi(operationNumber) > 2 
            || stoi(operationNumber) < 0)
        {
            cout << "Invalid input! Please enter a number between 0 and 2 -> ";
            cin.clear();
            getline(cin, operationNumber);
        }

        selection = stoi(operationNumber);
        break;

    case 2:
        cout << endl << "Please select the type of (postfix) operation you would like to perform." << endl;
        cout << "|----------------------------------------------|" << endl;
        cout << "| (0): Return to previous menu                 |" << endl;
        cout << "| (1): Evaluate the expression                 |" << endl;
        cout << "| (2): Print preorder, inorder, and postorder  |" << endl;
        cout << "|----------------------------------------------|" << endl;

        cout << "Operation # -> ";
        getline(cin, operationNumber);

        while (operationNumber.length() > 1 
            || !isdigit(operationNumber[0]) 
            || stoi(operationNumber) > 2 
            || stoi(operationNumber) < 0)
        {
            cout << "Invalid input! Please enter a number between 0 and 2 -> ";
            cin.clear();
            getline(cin, operationNumber);
        }

        selection = stoi(operationNumber);
        break;
    }

    return selection;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Removes the spaces from the inputted expression                       |
//                                                                       |
//-----------------------------------------------------------------------|

void Converter:: removeSpaces() 
{
    string formattedString; 

    for (int i = 0; i < input.length(); i++)
    {
        char currentCharacter = input[i];

        if (!isspace(currentCharacter))
        {
            formattedString.append(1, currentCharacter);
        }
    }

    input = formattedString;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks for balanced parenthesis                                       |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: balancedParenthesis() 
{
    int counter = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '(')
        {
            counter++;
        }
        else if (input[i] == ')')
        {
            counter--;
        }
    }

    return counter == 0; 
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the input is a valid operator                               |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: isOperator(char input) 
{
    for (int i = 0; i < VALIDCHARS_COUNT; i++)
    {
        if (validChars[i] == input)
        {
           return true;
        }
    }

    return false; 
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks for valid characters                                           |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: isValidChar(char input) 
{
    for (int i = 0; i < VALIDCHARS_COUNT; i++)
    {
        if (isOperator(input) || isdigit(input))
        {
            return true;
        } 
        else if (isupper(input))
        {
            if (input >= 'A' && input <= 'Z')
            {
                return true;
            }

            return false;
        }
    }

    return false; 
}

//-----------------------------------------------------------------------|
//                                                                       |
// Validates and sets the user's input for an infix expression.          |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: validInfix()
{
    removeSpaces();

    if (!balancedParenthesis())
    {
        cout << "Bad formatting error! Unbalanced parenthesis." << endl;
        return false;
    } 
    else if (input == "")
    {
        cout << "Bad formatting error! Empty input." << endl;
        return false;
    }

    for (int i = 0; i < input.length(); i++)
    {
        if ((i == 0 && isOperator(input[i])) && (input[i] != '('))
        {
            cout << "Bad formatting error! Expression cannot start with an operator." << endl;
            return false;
        }
        else if (!isValidChar(input[i]))
        {
            cout << "Bad formatting error! Invalid Characters." << endl;
            return false;
        } 
        else if ((input[i] == input[i-1] || input[i] == input[i+1]) && (input[i] != '(' && input[i] != ')'))
        {
            cout << "Bad formatting error! Duplicate Characters." << endl;
            return false;
        }
        else if ((isOperator(input[i]) && (input[i] != '(' && input[i] != ')'))) 
        {
            if ((isOperator(input[i-1]) || isOperator(input[i+1])) && (input[i-1] != ')' && input[i+1] != '('))
            {
                cout << i << endl;
                cout << "Bad formatting error! Operators cannot be next to each other." << endl;
                return false;
            }
            else if (i == input.length() - 1)
            {
                cout << "Bad formatting error! An operand must follow an operator." << endl;
                return false;
            }
        }
        else if (isValidChar(input[i]) && !isOperator(input[i + 1]) && input[i] != '(' && i != input.length() - 1)
        {
            cout << "Bad formatting error! An operator must follow an operand." << endl;
            return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the precedence for an inputted operator                       |
//                                                                       |
//-----------------------------------------------------------------------|

int Converter:: getPrecedence(char input)
{
    if (input == '+' || input == '-')
    {
        return 1;
    }

    return 2;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Determines if one operator has higher precedence than another         |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: isHigherPrecedence(char current, char previous)
{
    return getPrecedence(current) <= getPrecedence(previous);
}

//-----------------------------------------------------------------------|
//                                                                       |
// Converts an infix expression into a postfix expression                |
//                                                                       |
//-----------------------------------------------------------------------|

string Converter:: infixToPostfix()
{
    stack <char> operators;
    string postFixString;

    for (int i = 0; i < input.length(); i++)
    {
        char currentChar = input[i];

        if (currentChar == '(') 
        {
            operators.push(currentChar); 
        }
        else if (currentChar == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postFixString += operators.top();
                operators.pop();
            }
            
            operators.pop(); 
        }
        else if (isOperator(currentChar))
        {
            while(!operators.empty() && operators.top() != '(' && isHigherPrecedence(currentChar, operators.top()))
            {
                postFixString += operators.top();
                operators.pop();
            }
            operators.push(currentChar);
        }
        else
        {
            postFixString += currentChar;
        }
    }

    while (!operators.empty()) {
        postFixString += operators.top();
        operators.pop();
    }

    return postFixString;  
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the inputted character is base 36                           |
//                                                                       |
//-----------------------------------------------------------------------|
bool Converter:: isBase36(char input)
{
    return input >= 'A' && input <= 'Z';
}


//-----------------------------------------------------------------------|
//                                                                       |
// Validates and sets the user's input for a postfix expression.         |
//                                                                       |
//-----------------------------------------------------------------------|

bool Converter:: validPostfix()
{
    removeSpaces();

    int operandCount = 0;
    int operatorCount = 0;

    if (input == " ")
    {
        cout << "Bad formatting error! Empty input." << endl;

        return false;
    }

    for (int i = 0; i < input.length(); i++)
    {
        if ((i == 0 && isOperator(input[i])))
        {
            cout << "Bad formatting error! Expression cannot start with an operator." << endl;

            return false;
        }
        else if (!isValidChar(input[i]))
        {
            cout << "Bad formatting error! Invalid Characters." << endl;

            return false;
        }
        else if (input[i] == '(' || input[i] == ')')
        {
            cout << "Bad formatting error! Parenthesis are not allowed." << endl;

            return false;
        }
        else if ((isValidChar(input[i]) && !isOperator(input[i])) && isOperator(input[i+1]) && !isValidChar(input[i-1]))
        {
            cout << "Bad formatting error! Invalid Format." << endl;

            return false;
        }
        
        else if (!isOperator(input[i]) && !isdigit(input[i]))
        {
            if (!isBase36(input[i]))
            {
                cout << "Bad formatting error! Input is not Base 36." << endl;

                return false;
            }

            operandCount++;
        }
        else if (isdigit(input[i]))
        {
            operandCount++;
        }
        else if (isOperator(input[i]))
        {
            operatorCount++;
        }
    }

    if ((operandCount + operatorCount) % 2 == 0 || operatorCount != operandCount - 1)
    {
        cout << "Bad formatting error! Invalid expression." << endl;
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs an operation on two numbers                                  |
//                                                                       |
//-----------------------------------------------------------------------|

int Converter:: operate(int num1, int num2, char op)
{
    switch (op)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
    }

    return -1;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Converts an integer to base 36                                        |
//                                                                       |
//-----------------------------------------------------------------------|

string Converter:: convertToBase36(int input)
{
    string result = "";

    if (input > 9 && input < 36)
    {
        char digit = input + 55;

        return  result += digit;
    }
    else if (input <= 9)
    {
        return to_string(input);
    } 
    else if (input == 36)
    {
        return "1";
    }
    else
    {
        while(input != 0)
        {
            int currentDigit = (input % 36);
            char digit;

            if (currentDigit > 9 && currentDigit < 36) {
                digit = currentDigit + 55;
            } 
            else
            {
                digit = currentDigit + '0';
            }
            
            input     /= 36;
            result    += digit;
        }

        string reversedResult;

        for (int j = result.length(); j >= 0; j--)
        {
            reversedResult += result[j];
        }

        return reversedResult;
    }

    return "AN ERROR OCCURRED!";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Evaluates a postfix expression                                        |
//                                                                       |
//-----------------------------------------------------------------------|

string Converter:: evaluatePostfix()
{
    stack<int> operands;
    int result = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (isdigit(input[i]))
        {
            operands.push(input[i] - '0');
        }
        else if (!isOperator(input[i]))
        {
            operands.push(input[i] - 55);
        }
        else
        {
            int num1 = operands.top();
            operands.pop();
            int num2 = operands.top();
            operands.pop();
            operands.push(operate(num2, num1, input[i]));
        }
        
    }
    
    return to_string(operands.top()) + " or " + convertToBase36(operands.top()) + " (in base 36)";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Creates a new node for the expression tree                            |
//                                                                       |
//-----------------------------------------------------------------------|

Expression* Converter:: createNode(char val)
{
    Expression *newNode = new Expression;
    newNode->left       = NULL;
    newNode->right      = NULL;
    newNode->value      = val;

    return newNode;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Builds the expression tree for a postfix expression                   |
//                                                                       |
//-----------------------------------------------------------------------|
void Converter:: buildExpressionTree(string postfixString)
{
    stack <Expression*> expressionMembers;
    Expression *head, *operand1, *operand2; 
    for (int i = 0; i < postfixString.length(); i++)
    {
        if (!isOperator(postfixString[i]))
        {
            operand1 = createNode(postfixString[i]);
            expressionMembers.push(operand1);
        }
        else
        {
            head = createNode(postfixString[i]);
            operand1 = expressionMembers.top();
            expressionMembers.pop();
            operand2 = expressionMembers.top();
            expressionMembers.pop();

            head->left  = operand2;
            head->right = operand1;

            expressionMembers.push(head);
        }
        
    }

    expression = expressionMembers.top();
    expressionMembers.pop();
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs inorder traversal of an expression tree                      |
//                                                                       |
//-----------------------------------------------------------------------|
void Converter:: inorderTraversal(Expression *ex)
{
    if (ex != NULL)
    {
        inorderTraversal(ex->left);
        cout << ex->value << " ";
        inorderTraversal(ex->right);
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs postorder traversal of an expression tree                    |
//                                                                       |
//-----------------------------------------------------------------------|
void Converter:: postorderTraversal(Expression *ex)
{
    if (ex != NULL)
    {
        postorderTraversal(ex->left);
        postorderTraversal(ex->right);
        cout << ex->value << " ";
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs preorder traversal of an expression tree                     |
//                                                                       |
//-----------------------------------------------------------------------|
void Converter:: preorderTraversal(Expression *ex)
{
    if (ex != NULL)
    {
        cout << ex->value << " ";
        preorderTraversal(ex->left);
        preorderTraversal(ex->right);
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs the conversion for a user's input                            |
//                                                                       |
//-----------------------------------------------------------------------|

void Converter:: convert() 
{
    int primaryOperationNumber = getWhichBaseOperation();
    int secondaryOperationNumber;
    cin.clear();

    while (primaryOperationNumber != 0)
    {
        secondaryOperationNumber = getWhichSecondaryOperation(primaryOperationNumber);

        if (primaryOperationNumber == 1 && secondaryOperationNumber == 1)
        {
            cout << "Enter an infix expression: ";
            getline(cin, input);

            while (!validInfix())
            {
                cout << endl << "Enter an infix expression -> ";
                cin.clear();
                getline(cin, input);
            }

            cout << endl << "Postfix = " << infixToPostfix();
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 2)
        {
           cout << "Enter an infix expression: ";
            getline(cin, input);

            while (!validInfix())
            {
                cout << endl << "Enter an infix expression -> ";
                cin.clear();
                getline(cin, input);
            }

            string postfixStringExpression = infixToPostfix();
            buildExpressionTree(postfixStringExpression);
            input = postfixStringExpression;
            
            cout << endl << "Postfix = " << postfixStringExpression;
            cout << endl << "Preorder Traversal: ";
            preorderTraversal(expression);
            cout << endl << "Inorder Traversal: ";
            inorderTraversal(expression);
            cout << endl << "Postorder Traversal: ";
            postorderTraversal(expression);
            cout << endl << "Value = " << evaluatePostfix();
        }
        else if (primaryOperationNumber == 2 && secondaryOperationNumber == 1)
        {
            cout << "Enter a postfix expression: ";
            getline(cin, input);

            while (!validPostfix())
            {
                cout << endl << "Enter an postfix expression -> ";
                cin.clear();
                getline(cin, input);
            }

            cout << endl << "Value = " << evaluatePostfix();

        }
        else if (primaryOperationNumber == 2 && secondaryOperationNumber == 2)
        {
            cout << "Enter a postfix expression: ";
            getline(cin, input);

            while (!validPostfix())
            {
                cout << endl << "Enter an postfix expression -> ";
                cin.clear();
                getline(cin, input);
            }

            buildExpressionTree(input);
            cout << endl << "Preorder Traversal: ";
            preorderTraversal(expression);
            cout << endl << "Inorder Traversal: ";
            inorderTraversal(expression);
            cout << endl << "Postorder Traversal: ";
            postorderTraversal(expression);
        }

        cout << endl << "------------------------------------------------" << endl;
        cin.clear();
        input = "";
        primaryOperationNumber = getWhichBaseOperation();
    }
}