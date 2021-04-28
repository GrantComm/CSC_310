#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include "Polynomial.h"

using namespace std;

const int POLYNOMIALS_COUNT = 11;

class Operator
{
    public:
        Operator(); 
        void validateAndSetNumberOfPolynomials();
        Polynomial addTwoPolynomials(Polynomial, Polynomial);
        Polynomial add();
        Polynomial multiplyTwoPolynomials(Polynomial, Polynomial);
        Polynomial multiply();
        void showOperation();
        void operate();
    private:
        int maxNumberOfPolynomials;
        Polynomial polynomials[POLYNOMIALS_COUNT + 1]; 
};

#endif