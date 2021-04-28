#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <iomanip>
#include "Term.h"

using namespace std;

const int VALIDCHARS_COUNT = 4;

class Polynomial
{
    public:
        Polynomial(); 
        string getStr();
        void setPolynomial(string);
        bool isValidChar(char);
        string removeSpaces(string);
        void addSpacing();
        bool isValidPolynomial();
        void setTerms();
        void setTerm (string, Term*);
        Term* getTerm();
        void insertTerm(Term*);
        void sortTerms();
        void insertSort(Term**, Term*);
        void combineLikeTerms();
        void printPolynomial(bool); 

    private:
        string polynomial; 
        Term *terms;
        char validChars[VALIDCHARS_COUNT];
};

#endif