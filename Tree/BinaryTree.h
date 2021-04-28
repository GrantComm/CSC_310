#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    char value;
    Node* left, *right;
};

class BinaryTree 
{
    public:
        BinaryTree();
        int getWhichBaseOperation();
        int getWhichSecondaryOperation(int);
        void removeSpaces();
        bool isValid();
        string boolToString(bool);
        void setPreorderString(string);
        string getPreorderString();
        Node* createNode(char val);
        Node* buildHelper(int&); 
        Node* buildTree(string);
        bool isBSTHelper(Node*, int, int);
        bool isBST(Node*);
        int node_count();
        int height(Node*);
        bool isFullBT(Node*);
        bool isComplete(Node*);
        void printInorder(Node*);
        void printPreorder();
        void printPostorder(Node*);
        bool levelHasNodes(Node*, int);
        void printLevelorder(Node*); //TODO
        void printVertical(); //TODO
        void printVerticalWithArcs(); //TODO
        void run();

    private:
        string inputPreorderString;
        Node *tree;
}; 

#endif