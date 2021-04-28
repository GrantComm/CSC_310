#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <iomanip>

using namespace std;

class Term
{
    public:
        void setCoefficient(string);
        void setExponent(string);
        void setNext(Term*);
        int getCoefficient();
        int getExponent();
        Term* getNext();

    private:
        int coefficient;
        int exponent;
        Term *next;
};

#endif