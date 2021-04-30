#include "queue.h"

Queue:: Queue() 
{
    size = 0;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Adds an element to the queue                                          |
//                                                                       |
//-----------------------------------------------------------------------|

void Queue:: enQueue(int input)
{
    QueueNode* temp =  new QueueNode;
    temp->data = input;

    if (!tail)
    {
        head = tail = temp;
        size++;
        return;
    }
    else
    {
        tail->next = temp;
        tail = temp;
        size++;
        return;
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Removes the element at the front of the queue                         |
//                                                                       |
//-----------------------------------------------------------------------|

void Queue:: deQueue()
{
    if (head) 
    { 
        QueueNode *temp = head;
        head = head -> next;

        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete(temp);
        size--;
        return;
    }

    return;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the element at the front of the queue                         |
//                                                                       |
//-----------------------------------------------------------------------|

int Queue:: front()
{
    if (head)
    {
        return head->data;
    }

    cout << "ERROR! QUEUE IS EMPTY" << endl;
    return -1;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the element at the front of the queue                         |
//                                                                       |
//-----------------------------------------------------------------------|

int Queue:: rear()
{
    if (tail)
    {
        return tail->data;
    }

    cout << "ERROR! QUEUE IS EMPTY" << endl;
    return -1;
}

bool Queue:: is_Empty()
{
    return size == 0;
}