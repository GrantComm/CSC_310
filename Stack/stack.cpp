#include "stack.h"

Stack:: Stack() 
{
    size = 0;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Removes the element at the top of the stack                           |
//                                                                       |
//-----------------------------------------------------------------------|

void Stack:: pop() 
{
    if (head != nullptr)
    {
        StackNode* temp = head;
        head = head -> next;

        temp -> next = nullptr;
        delete(temp);

        size--;
        return;
    }

    cout << "ERROR! STACK IS EMPTY!" << endl;
    return;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the element at the top of the stack                           |
//                                                                       |
//-----------------------------------------------------------------------|

int Stack:: top()
{
    return head -> data;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Adds an element to the stack                                          |
//                                                                       |
//-----------------------------------------------------------------------|

void Stack:: push(int input) 
{
    StackNode* temp = new StackNode;
    temp -> data = input;
    temp -> next = head;

    head = temp;

    size++;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the stack is empty                                          |
//                                                                       |
//-----------------------------------------------------------------------|

bool Stack:: is_Empty() 
{
    return size == 0;
}