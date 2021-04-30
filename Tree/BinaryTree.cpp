#include "BinaryTree.h"

Tree:: Tree()
{

}

//-----------------------------------------------------------------------|
//                                                                       |
// Prompts the user for the type of operation that they would like to do.|
//                                                                       |
//-----------------------------------------------------------------------|

int Tree:: getWhichBaseOperation()
{
    string operationNumber;

    cout << endl << "Please select the type of operation you would like to perform." << endl;
    cout << "|------------------------------------------------|" << endl;
    cout << "| (0): Exit the program                          |" << endl;
    cout << "| (1): Input a preorder representation of a tree |" << endl;
    cout << "|------------------------------------------------|" << endl;

    cout << endl << "Operation # -> ";
    getline(cin, operationNumber);

    while (operationNumber.length() > 1 
           || !isdigit(operationNumber[0]) 
           || stoi(operationNumber) > 1 
           || stoi(operationNumber) < 0)
    {
        cout << "Invalid input! Please enter either 1 or 0 -> ";
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

int Tree:: getWhichSecondaryOperation(int input)
{
    string operationNumber;
    int selection;

    switch (input)
    {
    case 0:
        selection = stoi(operationNumber);
        break;

    case 1:
        cout << endl << "|--------------------------------------------------|" << endl;
        cout << "| (0): Return to main menu                         |" << endl;
        cout << "| (1): Check if the tree is a binary search tree   |" << endl;
        cout << "| (2): Return the number of nodes in the tree      |" << endl;
        cout << "| (3): Return the height of the tree               |" << endl;
        cout << "| (4): Check if the tree is a full binary tree     |" << endl;
        cout << "| (5): Check if the tree is a complete binary tree |" << endl;
        cout << "| (6): Show a full summary                         |" << endl;
        cout << "|--------------------------------------------------|" << endl;

        cout << endl << "Operation # -> ";
        getline(cin, operationNumber);

        while (operationNumber.length() > 1 
            || !isdigit(operationNumber[0]) 
            || stoi(operationNumber) > 6
            || stoi(operationNumber) < 0)
        {
            cout << "Invalid input! Please enter a number between 0 and 6 -> ";
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

void Tree:: removeSpaces() 
{
    string formattedString; 

    for (int i = 0; i < inputPreorderString.length(); i++)
    {
        char currentCharacter = inputPreorderString[i];

        if (!isspace(currentCharacter))
        {
            formattedString.append(1, currentCharacter);
        }
    }

    inputPreorderString = formattedString;
}


//-----------------------------------------------------------------------|
//                                                                       |
// Validates the inputted preorder string                                |
//                                                                       |
//-----------------------------------------------------------------------|

bool Tree:: isValid()
{
    if (inputPreorderString.length() == 0 || inputPreorderString[0] == '.') 
    {
        return false;
    }

    int nodeCount = 0;
    int nullCount = 0;

    for (int i = 0; i < inputPreorderString.length(); i++)
    {
        if (inputPreorderString[i] == '.') 
        {
            nullCount++; 
        } else 
        {
            nodeCount++;
        }
    }

    return nullCount - nodeCount == 1; 
}

//-----------------------------------------------------------------------|
//                                                                       |
// Converts a bool to a string representation                            |
//                                                                       |
//-----------------------------------------------------------------------|

string Tree:: boolToString(bool input)
{
    if (input)
    {
        return "TRUE";
    }

    return "FALSE";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Sets the preorder string                                              |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: setPreorderString(string input)
{
    inputPreorderString = input;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the preorder traversal of the tree                            |
//                                                                       |
//-----------------------------------------------------------------------|

string Tree:: getPreorderString()
{
    return inputPreorderString;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Creates a new node for the tree                                       |
//                                                                       |
//-----------------------------------------------------------------------|

BinaryTree* Tree:: createNode(char val)
{
    BinaryTree *newNode = new BinaryTree;
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

BinaryTree* Tree:: buildHelper(int &index)
{
    if (inputPreorderString[index] == '.')
    {
        index++;
        return NULL;
    }

    BinaryTree* root = createNode(inputPreorderString[index]);
    index++;

    root->left = buildHelper(index);
    root->right = buildHelper(index);

    return root;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Builds the expression tree for a postfix expression                   |
//                                                                       |
//-----------------------------------------------------------------------|

BinaryTree* Tree:: buildTree(string input)
{
    int index = 0;
    return buildHelper(index);
}

//-----------------------------------------------------------------------|
//                                                                       |
// Helps check if the tree is a binary search tree                       |
//                                                                       |
//-----------------------------------------------------------------------|

bool Tree:: isBSTHelper(BinaryTree* root, int min, int max)
{
    if (root != NULL)
    {
        if (root -> value < min || root -> value > max)
        {
            return false;
        }

        return isBSTHelper(root->left, min, root->value - 1) &&
               isBSTHelper(root->right, root->value + 1, max);
    }

    return true;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the tree is a binary search tree                            |
//                                                                       |
//-----------------------------------------------------------------------|

bool Tree:: isBST(BinaryTree* root)
{
    return isBSTHelper(root, INT_MIN, INT_MAX);
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the number of nodes in the tree                               |
//                                                                       |
//-----------------------------------------------------------------------|

int Tree:: node_count()
{
    int count = 0;

    for (int i = 0; i < inputPreorderString.length(); i++) 
    {
        if (inputPreorderString[i] != '.')
        {
            count++;
        }
    }

    return count;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the height of the tree                                        |
//                                                                       |
//-----------------------------------------------------------------------|

int Tree:: height(BinaryTree* root)
{
    if (root != NULL)
    {
        queue<BinaryTree*> levels;
  
        levels.push(root);
        int height = 0;
    
        while (1)
        {
            int nodeCount = levels.size();
            if (nodeCount == 0)
            {
                return height;
            }
    
            height++;

            while (nodeCount > 0)
            {
                BinaryTree *node = levels.front();
                levels.pop();
                if (node->left != NULL)
                    levels.push(node->left);
                if (node->right != NULL)
                    levels.push(node->right);
                nodeCount--;
            }
        }
    }

    return 0;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the tree is a full binary tree                              |
//                                                                       |
//-----------------------------------------------------------------------|

bool Tree:: isFullBT(BinaryTree *root)
{
    if (root == NULL)
    {
        return true;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        return true;
    }
    else if (root->left != NULL && root->right != NULL)
    {
        return (isFullBT(root->left) && isFullBT(root->right));
    }

    return false;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the tree is a complete binary tree                          |
//                                                                       |
//-----------------------------------------------------------------------|

bool Tree:: isComplete(BinaryTree *root)
{
    if (root != NULL)
    {
        queue<BinaryTree*> levels;
        levels.push(root);
        bool hasNone = false;
  
        while(!levels.empty())
        {
            BinaryTree *node = levels.front();
            
            levels.pop();
    
            if(node->left)
            {

                if (hasNone)
                {
                    return false;
                }
        
                levels.push(node->left);
            }
            else
            {
                hasNone = true;
            }
       
            if(node->right)
            {
                if(hasNone)
                {
                    return false;
                }
    
                levels.push(node->right);
            }
            else
            {
                hasNone = true;
            }
        }
    }

    return true;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs preorder traversal of a tree                                 |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: printPreorder()
{
    for (int i = 0; i < inputPreorderString.length(); i++) 
    {
        cout << inputPreorderString[i];
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs inorder traversal of a tree                                  |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: printInorder(BinaryTree *root)
{
    if (root != NULL)
    {
        printInorder(root->left);
        cout << root->value;
        printInorder(root->right);
    }
    else
    {
        cout << ".";
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs postorder traversal of a tree                                |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: printPostorder(BinaryTree *root)
{
    if (root != NULL)
    {
        printPostorder(root->left);
        printPostorder(root->right);
        cout << root->value;
    }
    else
    {
        cout << ".";
    }
    
}

//-----------------------------------------------------------------------|
//                                                                       |
// Performs levelorder traversal of a tree                               |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: printLevelorder(BinaryTree *root)
{

    if (root != NULL)
    {
        queue<BinaryTree*> levels;
        levels.push(root);

        while (!levels.empty())
        {
            BinaryTree *node = levels.front();

            if (node == NULL)
            {
                cout << '.';
            }
            else
            {
                cout << node->value;
            }

            levels.pop();
 
            levels.push(node->left);
            levels.push(node->right);
            }
    }
    else
    {
        cout << ".";
    }

}

//-----------------------------------------------------------------------|
//                                                                       |
// Runs the binary tree program                                          |
//                                                                       |
//-----------------------------------------------------------------------|

void Tree:: run()
{
    int primaryOperationNumber = getWhichBaseOperation();
    int secondaryOperationNumber;
    cin.clear();

    while (primaryOperationNumber != 0)
    {
        secondaryOperationNumber = getWhichSecondaryOperation(primaryOperationNumber);

        if (primaryOperationNumber == 1 && secondaryOperationNumber == 0)
        {
            cin.clear();
            inputPreorderString = "";
            primaryOperationNumber = getWhichBaseOperation();
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 1)
        {
            cout << endl << "Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Error! Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Is a Binary Search Tree: " << boolToString(isBST(tree)); 
            cout << endl << "------------------------------------------------" << endl;   
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 2)
        {
            cout << endl << "Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Error! Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Number of Nodes: " << node_count();
            cout << endl << "------------------------------------------------" << endl;
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 3)
        {
            cout << endl << "Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Error! Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Height of Tree: " << height(tree); 
            cout << endl << "------------------------------------------------" << endl;
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 4)
        {
            cout << endl << "Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Error! Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Is a Full Binary Tree: " << boolToString(isFullBT(tree)); 
            cout << endl << "------------------------------------------------" << endl;  
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 5)
        {
            cout << "Error! Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Is a Complete Binary Tree: " << boolToString(isComplete(tree)); 
            cout << endl << "------------------------------------------------" << endl;
        }
        else if (primaryOperationNumber == 1 && secondaryOperationNumber == 6)
        {
            cout << "Enter a preorder representation of a tree: ";
            getline(cin, inputPreorderString);

            while (!isValid())
            {
                cout << "Error! Enter a valid preorder representation of a tree: ";
                cin.clear();
                getline(cin, inputPreorderString);
            }

            tree = buildTree(inputPreorderString);

            cout << "Is a Binary Search Tree: " << boolToString(isBST(tree)) << endl; 
            cout << "Number of Nodes: " << node_count() << endl;
            cout << "Height of Tree: " << height(tree) << endl;
            cout << "Is a Full Binary Tree: " << boolToString(isFullBT(tree)) << endl;
            cout << "Is a Complete Binary Tree: " << boolToString(isComplete(tree)) << endl;
            cout << "Preorder: ";
            printPreorder();
            cout << endl << "Inorder: ";
            printInorder(tree);
            cout << endl << "Postorder: ";
            printPostorder(tree);
            //cout << endl << "Levelorder: ";
            //printLevelorder(tree);
            cout << endl << "------------------------------------------------" << endl;
        }
    }
}