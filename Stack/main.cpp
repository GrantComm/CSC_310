#include "stack.h"

int main() 
{
    Stack stack = Stack();

    cout << "IS EMPTY: " << stack.is_Empty() << endl;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    cout << "IS EMPTY: " << stack.is_Empty() << endl;
    stack.pop();

    cout << "FINAL: ";

    while (!stack.is_Empty()) 
    {
        int num = stack.top();
        stack.pop();

        if (stack.is_Empty()) 
        {
            cout << num << endl;
        } 
        else 
        {
            cout << num << ", ";
        }
    }

}