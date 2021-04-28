#include "Converter.h"

Converter:: Converter()
{

}

int Converter:: to_Stoi(string str) 
{
    int result = 0;

    for (int i = 0; i < str.length(); i++) 
    {
        result = result * 10 + str[i] - '0';
    }

    return result;
}

string Converter:: to_String(int num) 
{
    string result;

    while (num != 0) 
    {
        char digit = (num % 10) + '0';
        num /= 10; 
        result += digit;
    }

    return result;
}

void Converter:: convert()
{
    int answer;

    do 
    {
        cout << "|----------- Converter -----------|" << endl;
        cout << "| 1: Convert string to integer    |" << endl;
        cout << "| 2: Convert integer to string    |" << endl;
        cout << "| 0: Quit                         |" << endl;
        cout << "|---------------------------------|" << endl;
        cout << "Choose an operation (1, 2, or 0) -> ";

        cin >> answer;

        while (cin.fail() || (answer > 2 && answer < 0))
        {
            cin.clear();
            cout << "Invalid Input! Please enter 1, 2, or 0." << endl;
            cout << "Choose an operation (1, 2, or 0) -> ";
            cin >> answer;
        }

        string input;
        int inputty;

        switch (answer)
        {
        case 1:
            cout << "Enter a number (it is a string): ";
            cin.ignore();
            getline(cin, input);
            cout << "Result: " << to_Stoi(input) << endl << endl;
            break;
        case 2:
            cout << "Enter a number (it is an integer): ";
            cin >> inputty;
            cout << "Result: " << to_String(inputty) << endl << endl;
            break;
        case 0:
            cout << "Auf Weidersehen!" << endl;
            break;
        default:
            cout << "An error occurred!" << endl << endl;
            break;
        }
        
    } while (answer != 0);
}


