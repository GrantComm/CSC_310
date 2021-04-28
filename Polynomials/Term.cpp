#include "Term.h"

//----------------------------------------------------------------------|
//                                                                      |
// Sets the coefficient for the term                                    |
//                                                                      |
//----------------------------------------------------------------------|

void Term:: setCoefficient(string inputCoefficient)
{
    int currentCoefficient; 

    try 
    {
        currentCoefficient = stoi(inputCoefficient);

    } 
    catch (exception e) 
    {
        cout << "Something was wrong in your coefficient input!" << endl;
    }

    coefficient = currentCoefficient; 
}

//----------------------------------------------------------------------|
//                                                                      |
// Sets the exponent for the term                                       |
//                                                                      |
//----------------------------------------------------------------------|

void Term:: setExponent(string inputExponent) 
{
    int currentExponent; 

    try 
    {
        currentExponent = stoi(inputExponent);
        
    } 
    catch (exception e) 
    {
        cout << "Something was wrong in your exponent input!" << endl;
    }
    
    exponent = currentExponent;
}

//----------------------------------------------------------------------|
//                                                                      |
// Sets the next term                                                   |
//                                                                      |
//----------------------------------------------------------------------|

void Term:: setNext(Term *newTerm) 
{
    next = newTerm;
}

//----------------------------------------------------------------------|
//                                                                      |
// Returns the coefficient of the term                                  |
//                                                                      |
//----------------------------------------------------------------------|

int Term:: getCoefficient() 
{
    return coefficient;
}

//----------------------------------------------------------------------|
//                                                                      |
// Returns the exponent of the term                                     |
//                                                                      |
//----------------------------------------------------------------------|

int Term:: getExponent() 
{
    return exponent; 
}

Term* Term:: getNext()
{
    return next;
}