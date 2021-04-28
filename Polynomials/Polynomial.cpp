#include "Polynomial.h"

Polynomial:: Polynomial() 
{
    validChars[0] = 'x';
    validChars[1] = '^';
    validChars[2] = '+';
    validChars[3] = '-';
    terms = nullptr;
}

//----------------------------------------------------------------------|
//                                                                      |
// Returns the string representation of the polynomial                  |
//                                                                      |
//----------------------------------------------------------------------|

string Polynomial:: getStr() 
{
    return polynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Sets the polynomial string to the inputted polynomial string         |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: setPolynomial(string input)
{
    polynomial = input;
}

//----------------------------------------------------------------------|
//                                                                      |
// Validates the inputted character                                     |
//                                                                      |
//----------------------------------------------------------------------|

bool Polynomial:: isValidChar(char input)
{
    for (int i = 0; i < VALIDCHARS_COUNT; i++)
    {
        if (input == validChars[i])
        {
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------|
//                                                                      |
// Remove the spaces in the inputted polynomial                         |
//                                                                      |
//----------------------------------------------------------------------|

string Polynomial:: removeSpaces(string input) 
{
    string formattedString; 

    for (int i = 0; i < input.length(); i++)
    {
        char currentCharacter = input[i];

        if (currentCharacter == 'X')
        {
            formattedString.append(1, tolower(currentCharacter));
        }
        else if (!isspace(currentCharacter))
        {
            formattedString.append(1, currentCharacter);
        }
    }

    return formattedString;
}

//----------------------------------------------------------------------|
//                                                                      |
// Checks the polynomial for invalid characters                         |
//                                                                      |
//----------------------------------------------------------------------|

bool Polynomial:: isValidPolynomial()
{
    if (isValidChar(polynomial[polynomial.length() -1]) && (polynomial[polynomial.length() -1] != 'x'))
    {
        cout <<polynomial[polynomial.length()-1];
        return false;
    }
    
    for (int i = 0; i < polynomial.length(); i++)
    {
        char currentCharacter = polynomial[i];
        if (!isValidChar(currentCharacter) && !isdigit(currentCharacter))
        {
            return false;
        } 
        else if (isValidChar(currentCharacter))
        {
            if (polynomial[i-1] == currentCharacter || polynomial[i+1] == currentCharacter)
            {
                return false;
            }
        } 
    }

    return true;
}

//----------------------------------------------------------------------|
//                                                                      |
// Adds the necessary spacing in the inputted polynomial                |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: addSpacing() 
{
    string formattedPolynomial;

    for (int i = 0; i < polynomial.length(); i++)
    {
        if (i == 0 && polynomial[i] == '-') 
        {
            formattedPolynomial.append(1, polynomial[i]);
        } 
        else if (polynomial[i] == '+' || polynomial[i] == '-' && polynomial[i-1] != '^')
        {
            formattedPolynomial.append(1, ' ');
            formattedPolynomial.append(1, polynomial[i]);
            formattedPolynomial.append(1, ' ');
        }
        else if (polynomial[i] == 'X')
        {
            formattedPolynomial.append(1, tolower(polynomial[i]));
        }
        else
        {
            formattedPolynomial.append(1, polynomial[i]);
        }
    }

    polynomial = formattedPolynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Creates terms and stores them in the polynomial                      |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: setTerms()
{
    terms = nullptr;
    int i = 0;
    int j = polynomial.find(" ");

    while (i < polynomial.length())
    {
        Term *newTerm = new Term();
        int index     = i;

        if (j != -1)
        {
            setTerm(removeSpaces(polynomial.substr(index, j)), newTerm);

            i = j; 
            j = (polynomial.find(" ", i+3) == -1) ? polynomial.length(): polynomial.find(" ", i+3); 
        }
        else
        {
            setTerm(polynomial.substr(index, polynomial.length()), newTerm);

            i = polynomial.length();
        }

        if (terms == nullptr)
        {
            terms = newTerm;
        }
        else
        {
            Term *tempTerm = terms;

            while(tempTerm -> getNext() != nullptr)
            {
                tempTerm = tempTerm ->getNext();
            }

            tempTerm->setNext(newTerm);
        }
    }
}

//----------------------------------------------------------------------|
//                                                                      |
// Creates a term                                                       |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: setTerm (string termString, Term *term)
{
    int variablePosition = termString.find("x");
    int exponentPosition = termString.find("^");
    string coefficient;
    string exponent;

    if (variablePosition != -1)
    {
        string coefficientString = termString.substr(0, variablePosition);

        if (exponentPosition != -1)
        {
            if (coefficientString == "+" || coefficientString == "")
            {
                coefficient = "1";
            }
            else if (coefficientString == "-")
            {
                coefficient = "-1";
            }
            else
            {
                coefficient = coefficientString;
            }
            exponent    = termString.substr(exponentPosition + 1, termString.length());
        }
        else
        {
            if (coefficientString == "+" || coefficientString == "")
            {
                coefficient = "1";
            }
            else if (coefficientString == "-")
            {
                coefficient = "-1";
            }
            else
            {
                coefficient = coefficientString;
            }

            exponent = "1";
        }
        
    }
    else if (coefficient == "0")
    {
        return;
    }
    else
    {
        coefficient = termString;
        exponent    = "0"; 
    }

    term -> setCoefficient(coefficient);
    term -> setExponent(exponent);
}

//----------------------------------------------------------------------|
//                                                                      |
// Returns the terms for the polynomial                                 |
//                                                                      |
//----------------------------------------------------------------------|

Term* Polynomial:: getTerm()
{
    return terms;
}

//----------------------------------------------------------------------|
//                                                                      |
// Inserts a term in the polynomial                                     |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: insertTerm(Term *insertedTerm)
{
    if (terms == nullptr)
    {
        terms = insertedTerm;
    }
    else
    {
        Term *lastTerm = terms;

        while (lastTerm -> getNext() != nullptr)
        {
            lastTerm = lastTerm -> getNext();
        }

        lastTerm -> setNext(insertedTerm);
    }
}

//----------------------------------------------------------------------|
//                                                                      |
// Sorts the terms in the polynomial                                    |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: sortTerms()
{
    Term *sortedTerms = nullptr;
    Term *currentTerm = terms;

    while (currentTerm != nullptr)
    {
        Term *next = currentTerm -> getNext();
        insertSort(&sortedTerms, currentTerm); 
        currentTerm = next;
    }

    terms = sortedTerms;
}

//----------------------------------------------------------------------|
//                                                                      |
// Inserts a new term into the sorted terms                             |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: insertSort(Term **sortedTerms, Term *term)
{
    Term* current;

    if (*sortedTerms == nullptr || (*sortedTerms) -> getExponent() < term -> getExponent()) 
    { 
        term -> setNext(*sortedTerms);
        *sortedTerms = term; 
    } 
    else
    { 
        current = *sortedTerms;

        while (current -> getNext() != nullptr && current -> getNext() -> getExponent() > term -> getExponent()) 
        {   
            current = current -> getNext(); 
        } 

        term -> setNext(current -> getNext());
        current -> setNext(term); 
    }
}

//----------------------------------------------------------------------|
//                                                                      |
// Combines like terms in the polynomial                                |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: combineLikeTerms()
{
    Term *currentTerm, *nextTerm, *likeTerm;
    currentTerm = terms;
    
    while (currentTerm != nullptr && currentTerm -> getNext() != nullptr)
    {
        nextTerm = currentTerm;

        while (nextTerm-> getNext() != nullptr)
        {
 
            if (currentTerm -> getExponent() == nextTerm -> getNext() -> getExponent())
            {
                currentTerm -> setCoefficient(to_string(currentTerm -> getCoefficient() + nextTerm -> getNext() -> getCoefficient()));
                likeTerm = nextTerm -> getNext();
                nextTerm -> setNext(nextTerm -> getNext() -> getNext());
 
                delete (likeTerm);
            }
            else
            {
                nextTerm = nextTerm -> getNext();
            }
        }

        currentTerm = currentTerm -> getNext();
    }
}

//----------------------------------------------------------------------|
//                                                                      |
// Print out the current polynomial                                     |
//                                                                      |
//----------------------------------------------------------------------|

void Polynomial:: printPolynomial(bool isResult) 
{
    if (!isResult)
    {
       cout << "[";
    }

    if (terms == nullptr)
    {
        cout << "0" << endl;
        return;
    }
    else
    {
        Term *tempTerm = terms;
        Term *prevTerm = nullptr;

        while (tempTerm != nullptr)
        {
            int currentCoefficient = tempTerm ->getCoefficient(); 
            int currentExponent    = tempTerm -> getExponent();

            if(prevTerm != nullptr && currentCoefficient < 0)
            {
                currentCoefficient *= -1;
            }

            if (currentExponent > 1 || currentExponent < 0)
            {
                if (currentCoefficient == 1)
                {
                    cout << "x^" << currentExponent;
                }
                else if (currentCoefficient == -1)
                {
                    cout << "-x^" << currentExponent;
                }
                else
                {
                    cout << currentCoefficient << "x^" << currentExponent;
                }
            }
            else if (currentExponent == 1)
            {
                if (currentCoefficient == 1)
                {
                    cout << "x";
                }
                else
                {
                    cout << currentCoefficient << "x";
                }
            }
            else
            {
                cout << currentCoefficient;
            }

            prevTerm = tempTerm;
            tempTerm = tempTerm -> getNext();

            if (tempTerm != nullptr)
            {
                if (tempTerm -> getCoefficient() > 0)
                {
                    cout << " + "; 
                }
                else
                {
                    cout << " - ";
                }
                    
            }
        }
    }

    if (!isResult)
    {
       cout << "]";
    }
   
}
