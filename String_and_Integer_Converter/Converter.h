#ifndef CONVERTER_H

#define CONVERTER_H

#include <iostream>

using namespace std;

class Converter 
{
    public:
        Converter();
        int to_Stoi(string);
        string to_String(int);
        void convert();
    private:
};

#endif