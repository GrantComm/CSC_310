#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

struct QueueNode {
    int data;
    QueueNode* next;
};

class  Queue {
    public:
        Queue();
        void enQueue(int);
        void deQueue();
        int front();
        int rear();
        bool is_Empty();
    private:
        QueueNode *head;
        QueueNode *tail;
        int size;
};

#endif