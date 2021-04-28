#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Reader
{
    public:
        Reader();
        int getMenuSelection();
        bool isValidFile(string, bool);
        void setFileToRead(string);
        void setFileToWrite(string);
        string getFileToRead();
        string getFileToWrite();
        string getOppositeDirection(string);
        bool isCardinalDirection(string);
        void updateCardinalDirection(string);
        string getBackwardsCardinalDirection();
        string getStreet(string);
        void headHome(stack<string>&, bool);
        void read();
        void output();
        void write();
        void run();
    private:
        string fileToRead;
        string fileToWrite;
        string currentCardinalDirection;
        queue<string> directionSets;
    
};

#endif