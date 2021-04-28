#include "Operator.h" 

Operator:: Operator() 
{
}

//----------------------------------------------------------------------|
//                                                                      |
// Prompts the user for the number of polynomials and validates input   |
//                                                                      |
//----------------------------------------------------------------------|

void Operator:: validateAndSetNumberOfPolynomials()
{
    int inputNumberOfPolynomials;
    string input;

    cout << "Please enter the number of polynomials (2-" << to_string(POLYNOMIALS_COUNT) << ") -> ";
    getline(cin, input);

    while (input.length() > 2
            || !isdigit(input[0])
            || (stoi(input) != 0 
            && (stoi(input) < 2 
            || stoi(input) > POLYNOMIALS_COUNT))) 
    {
        cout << "Invalid input! Please enter a number between 2 and " << to_string(POLYNOMIALS_COUNT) << ": ";
        cin.clear();
        getline(cin, input);
    }
    
    inputNumberOfPolynomials = stoi(input);
    maxNumberOfPolynomials   = inputNumberOfPolynomials;
}

//----------------------------------------------------------------------|
//                                                                      |
// Adds two polynomials together                                        |
//                                                                      |
//----------------------------------------------------------------------|

Polynomial Operator:: addTwoPolynomials(Polynomial polynomial1, Polynomial polynomial2)
{
    Polynomial sumPolynomial = Polynomial();
    Term *polynomialTerms1 = polynomial1.getTerm();
    Term *polynomialTerms2 = polynomial2.getTerm();
    int sumCoefficient;
    int currentCoefficient;

    while (polynomialTerms1 != nullptr || polynomialTerms2 != nullptr)
    {
        Term *resultTerm = new Term();

        if ((polynomialTerms1 != nullptr && polynomialTerms2 != nullptr) && polynomialTerms1 -> getExponent() > polynomialTerms2 -> getExponent())
        {
            currentCoefficient = polynomialTerms1 -> getCoefficient(); 

            if (currentCoefficient != 0)
            {
                resultTerm -> setExponent(to_string(polynomialTerms1 -> getExponent()));
                resultTerm -> setCoefficient(to_string(polynomialTerms1 -> getCoefficient()));
                sumPolynomial.insertTerm(resultTerm);
            }

            polynomialTerms1 = polynomialTerms1 -> getNext();
        }
        else if ((polynomialTerms2 != nullptr && polynomialTerms1 != nullptr) && polynomialTerms2 -> getExponent() > polynomialTerms1 -> getExponent())
        {
            currentCoefficient = polynomialTerms2 -> getCoefficient(); 

            if (currentCoefficient != 0)
            {
                resultTerm -> setExponent(to_string(polynomialTerms2 -> getExponent()));
                resultTerm -> setCoefficient(to_string(polynomialTerms2 -> getCoefficient()));
                sumPolynomial.insertTerm(resultTerm);
            }

            polynomialTerms2 = polynomialTerms2 -> getNext();
        }
        else if ((polynomialTerms1 != nullptr && polynomialTerms2 != nullptr) && (polynomialTerms1 -> getExponent() == polynomialTerms2 -> getExponent()))
        {
            sumCoefficient = polynomialTerms1 -> getCoefficient() + polynomialTerms2 -> getCoefficient();

            if (sumCoefficient != 0)
            {
                resultTerm -> setExponent(to_string(polynomialTerms1 -> getExponent()));
                resultTerm -> setCoefficient(to_string(sumCoefficient));
                sumPolynomial.insertTerm(resultTerm);
            }

            polynomialTerms1 = polynomialTerms1 -> getNext();
            polynomialTerms2 = polynomialTerms2 -> getNext();
        }
        else
        {
            if (polynomialTerms1 != nullptr)
            {
                currentCoefficient = polynomialTerms1 -> getCoefficient(); 

                if (currentCoefficient != 0)
                {
                    resultTerm -> setExponent(to_string(polynomialTerms1 -> getExponent()));
                    resultTerm -> setCoefficient(to_string(polynomialTerms1 -> getCoefficient()));
                    sumPolynomial.insertTerm(resultTerm);
                }

                polynomialTerms1 = polynomialTerms1 -> getNext();
            }
            if (polynomialTerms2 != nullptr)
            {
                currentCoefficient = polynomialTerms2 -> getCoefficient(); 

                if (currentCoefficient != 0)
                {
                    resultTerm -> setExponent(to_string(polynomialTerms2 -> getExponent()));
                    resultTerm -> setCoefficient(to_string(polynomialTerms2 -> getCoefficient()));
                    sumPolynomial.insertTerm(resultTerm);
                }

                polynomialTerms2 = polynomialTerms2 -> getNext();
            }
        }
    }

    delete polynomialTerms1;
    delete polynomialTerms2;

    return sumPolynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Adds the inputted polynomials together                               |
//                                                                      |
//----------------------------------------------------------------------|

Polynomial Operator:: add() 
{
    Polynomial sumPolynomial = addTwoPolynomials(polynomials[1], polynomials[2]);

    for (int i = 3; i <= maxNumberOfPolynomials; i++)
    {
        sumPolynomial = addTwoPolynomials(polynomials[i], sumPolynomial);
    }

    sumPolynomial.combineLikeTerms();
    sumPolynomial.sortTerms();

    return sumPolynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Multiply two polynomials together                                    |
//                                                                      |
//----------------------------------------------------------------------|

Polynomial Operator:: multiplyTwoPolynomials(Polynomial polynomial1, Polynomial polynomial2)
{
    Term *polynomialTerms1       = polynomial1.getTerm();
    Term *polynomialTerms2       = polynomial2.getTerm();
    Term *resultTerm             = nullptr;
    Polynomial productPolynomial = Polynomial();

    while (polynomialTerms1 != nullptr) 
    {
        while (polynomialTerms2 != nullptr) 
        {
            Term *resultTerm       = new Term();
            int productCoefficient = polynomialTerms1 -> getCoefficient() * polynomialTerms2 -> getCoefficient();

            if (productCoefficient != 0)
            {
                resultTerm -> setCoefficient(to_string(productCoefficient));
                resultTerm -> setExponent(to_string(polynomialTerms1 -> getExponent() + polynomialTerms2 -> getExponent()));
                productPolynomial.insertTerm(resultTerm);
            }

            polynomialTerms2 = polynomialTerms2 -> getNext();
        }

        polynomialTerms2 = polynomial2.getTerm();
        polynomialTerms1 = polynomialTerms1 -> getNext();
    }

    return productPolynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Multiplies the inputted polynomials together                         |
//                                                                      |
//----------------------------------------------------------------------|

Polynomial Operator:: multiply() 
{
    Polynomial productPolynomial = multiplyTwoPolynomials(polynomials[1], polynomials[2]);

    for (int i = 3; i <= maxNumberOfPolynomials; i++)
    {
        productPolynomial = multiplyTwoPolynomials(productPolynomial, polynomials[i]);
    }
    
    productPolynomial.combineLikeTerms();
    productPolynomial.sortTerms();

    return productPolynomial;
}

//----------------------------------------------------------------------|
//                                                                      |
// Shows the operations that the user is carrying out                   |
//                                                                      |
//----------------------------------------------------------------------|

void Operator:: showOperation()
{
    cout << endl << "Sum = ";

    for (int i = 1; i <= maxNumberOfPolynomials; i++) 
    {
        if (!(i == maxNumberOfPolynomials))
        {
            polynomials[i].printPolynomial(false); 
            cout << " + "; 
        }
        else
        {
            polynomials[i].printPolynomial(false);
        }
    }

    cout << endl << setw(6) << "= ";
    add().printPolynomial(true);
    cout << endl << endl << "Product = ";

    for (int j = 1; j <= maxNumberOfPolynomials; j++) 
    {
        if (!(j == maxNumberOfPolynomials))
        {
            polynomials[j].printPolynomial(false); 
            cout << " * "; 
        }
        else
        {
            polynomials[j].printPolynomial(false);
        }
    }

    Polynomial productPolynomial = multiply();  
    cout << endl << setw(10) << "= ";

    productPolynomial.printPolynomial(true);
}

//----------------------------------------------------------------------|
//                                                                      |
// Performs the operations on the inputed polynomials                   |
//                                                                      |
//----------------------------------------------------------------------|

void Operator:: operate()
{
    string inputPolynomial;

    validateAndSetNumberOfPolynomials();
    cin.clear();

    while (maxNumberOfPolynomials != 0) 
    {
        for (int i = 1; i <= maxNumberOfPolynomials; i++) 
        {
            if (i == 1)
            {
                cout << endl << endl << "Input polynomial " << i << " -> "; 
            }
            else
            {
                cout << endl << "Input polynomial " << i << " -> ";
            }

            getline(cin, inputPolynomial);
            inputPolynomial = polynomials[i].removeSpaces(inputPolynomial);
            polynomials[i].setPolynomial(inputPolynomial);
            cin.clear();

            while (!polynomials[i].isValidPolynomial() || polynomials[i].getStr() == "")
            {
                cout << "Your input contains an invalid character or bad format." << endl;
                cout << "You may only input (+, -, ^, x, or an integer)" << endl << endl;
                cin.clear();
                cout << endl << "Input polynomial " << i << " -> ";
                getline(cin, inputPolynomial);
                inputPolynomial = polynomials[i].removeSpaces(inputPolynomial);
                polynomials[i].setPolynomial(inputPolynomial);
            }

            polynomials[i].addSpacing();
            polynomials[i].setTerms();
        }

        showOperation();

        cout << endl << endl <<"----------------------------------------" << endl << endl;

        validateAndSetNumberOfPolynomials();
        cin.clear();
    }
}