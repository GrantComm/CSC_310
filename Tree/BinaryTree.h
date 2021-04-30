#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <queue>
using namespace std;

struct BinaryTree
{
    char value;
    BinaryTree* left, *right;
};

class Tree 
{
    public:
        Tree();
        int getWhichBaseOperation();
        int getWhichSecondaryOperation(int);
        void removeSpaces();
        bool isValid();
        string boolToString(bool);
        void setPreorderString(string);
        string getPreorderString();
        BinaryTree* createNode(char val);
        BinaryTree* buildHelper(int&); 
        BinaryTree* buildTree(string);
        bool isBSTHelper(BinaryTree*, int, int);
        bool isBST(BinaryTree*);
        int node_count();
        int height(BinaryTree*);
        bool isFullBT(BinaryTree*);
        bool isComplete(BinaryTree*);
        void printInorder(BinaryTree*);
        void printPreorder();
        void printPostorder(BinaryTree*);
        bool levelHasNodes(BinaryTree*, int);
        void printLevelorder(BinaryTree*); //TODO
        void printVertical(); //TODO
        void printVerticalWithArcs(); //TODO
        void run();

    private:
        string inputPreorderString;
        BinaryTree *tree;
}; 

#endif