#include "queue.h"

int main ()
{
    Queue queue = Queue();

    cout << "IS EMPTY: " << queue.is_Empty() << endl;

    queue.enQueue(1);
    queue.enQueue(2);
    queue.enQueue(3);
    queue.enQueue(4);
    queue.enQueue(5);

    cout << "IS EMPTY: " << queue.is_Empty() << endl;

    queue.deQueue();
    queue.deQueue();

    while (!queue.is_Empty())
    {
        int num = queue.front();
        queue.deQueue();

        if (queue.is_Empty()) 
        {
            cout << num << endl;
        }
        else
        {
            cout << num << ", ";
        }
        
    }
}