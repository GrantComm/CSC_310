#ifndef STACK_H
#define STACK_H


#include <iostream>

using namespace std;

struct StackNode 
{
    int data;
    StackNode *next;
};

class Stack 
{

    public:
        Stack();
        void pop();
        int top();
        void push(int);
        bool is_Empty();
    private:
        StackNode* head;
        int size;
};

#endif