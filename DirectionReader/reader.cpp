#include "reader.h"

Reader:: Reader()
{
}

//-----------------------------------------------------------------------|
//                                                                       |
// Prompts the user for their menu selection and returns their selection |
//                                                                       |
//-----------------------------------------------------------------------|

int Reader:: getMenuSelection()
{
    string operationNumber;

    cout << endl << "Please select the type of operation you would like to perform." << endl;
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "|   (1) Read directions and output directions home to console      |" << endl;
    cout << "|   (2) Read directions and output directions home to another file |" << endl;
    cout << "|   (0) Stop the program                                           |" << endl;
    cout << "|------------------------------------------------------------------|" << endl;

    cout << "Operation # ->  ";
    getline(cin, operationNumber);

    while (operationNumber.length() > 1 
           || !isdigit(operationNumber[0]) 
           || stoi(operationNumber) > 2 
           || stoi(operationNumber) < 0)
    {
        cout << "Invalid input! Please enter a number between 0 and 2 -> ";
        cin.clear();
        getline(cin, operationNumber);
    }

    return stoi(operationNumber);
}

//-----------------------------------------------------------------------|
//                                                                       |
// Checks if the inputted file is valid                                  |
//                                                                       |
//-----------------------------------------------------------------------|

bool Reader:: isValidFile(string inputFile, bool isWrite)
{
    fstream file;

    if (!isWrite)
    {
        file.open(inputFile, ios::in);

        if (!file)
        {
            cout << "File does not exist!" << endl;
            return false;
        }

        file.close();
        return true;
    }

    if (inputFile.find(".txt") == - 1 || inputFile.find(".txt") != inputFile.length() - 4)
    {
        cout << "Invalid file name!" << endl;
        return false;
    }
    else if (inputFile.substr(0, inputFile.length()) == ".txt")
    {
        cout << "Invalid file name!" << endl;
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Sets the file that is to be read                                      |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: setFileToRead(string inputFileToRead)
{
    fileToRead = inputFileToRead;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Sets the file that is to be written to                                |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: setFileToWrite(string inputFileToWrite)
{
    fileToWrite = inputFileToWrite;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Gets the file that is to be read                                      |
//                                                                       |
//-----------------------------------------------------------------------|

string Reader:: getFileToRead()
{
    return fileToRead;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Gets the file that is to be written to                                |
//                                                                       |
//-----------------------------------------------------------------------|

string Reader:: getFileToWrite()
{
    return fileToWrite;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Returns the opposite direction                                        |
//                                                                       |
//-----------------------------------------------------------------------|

string Reader:: getOppositeDirection(string direction)
{
    if (direction == "right")
    {
        return "left";
    }

    return "right";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Determines if a string is a cardinal direction                        |
//                                                                       |
//-----------------------------------------------------------------------|

bool Reader:: isCardinalDirection(string cardinalDirection)
{
    return (cardinalDirection == "north" || 
            cardinalDirection == "south" ||
            cardinalDirection == "east"  ||
            cardinalDirection == "west");
}

//-----------------------------------------------------------------------|
//                                                                       |
// Updates the cardinal direction based on the direction inputted        |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: updateCardinalDirection(string direction)
{
   if (currentCardinalDirection == "north") 
   {
        if (direction == "left") 
        {
            currentCardinalDirection = "west";
            return;
        }
        
        currentCardinalDirection = "east";
        return;
   }
   else if (currentCardinalDirection == "south") 
   {
        if (direction == "left") 
        {
            currentCardinalDirection = "east";
            return;
        }

        currentCardinalDirection = "west";
        return;
   }
   else if (currentCardinalDirection == "east") 
   {
        if (direction == "left") 
        {
            currentCardinalDirection = "north";
            return;
        }

        currentCardinalDirection = "south";
        return;
   }
   else if (currentCardinalDirection == "west") 
   {
        if (direction == "left") 
        {
            currentCardinalDirection = "south";
            return;
        }

        currentCardinalDirection = "north";
        return;
   }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Gets the opposite of the current cardinal direction                   |
//                                                                       |
//-----------------------------------------------------------------------|

string Reader:: getBackwardsCardinalDirection()
{
    if (currentCardinalDirection == "north") 
    {
        return "south";
    }
    else if (currentCardinalDirection == "south")
    {
        return "north";
    }
    else if (currentCardinalDirection == "east")
    {
        return "west";
    }
    else if (currentCardinalDirection == "west")
    {
        return "east";
    }

    return "error";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Gets the street name from a direction sentence                        |
//                                                                       |
//-----------------------------------------------------------------------|

string Reader:: getStreet(string inputAddress)
{
    int i = inputAddress.length() - 1;
    while (i >= 0)
    {
        if (isdigit(inputAddress[i]))
        {
            return inputAddress.substr(i+2);
        }

        i--;
    }

    return "Error";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Creates the directions back home for each direction set               |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: headHome(stack<string>& directions, bool isLastSet) 
{
    string startingInstruction = "Head " + getBackwardsCardinalDirection() + 
                                 " from " + 
                                 directions.top().substr(10, directions.top().length() - 1);
    directionSets.push(startingInstruction);
    directions.pop();

    string currentDirection = directions.top(); 
    string previousDirection;
    string newDirection;

    if (currentDirection.substr(0, 8) == "Continue") 
    {
        previousDirection = "Continue";
        directions.pop();
    }
    else
    {
        if (currentDirection.substr(0, 4) == "Head" && isLastSet)
        {
            newDirection = "Arrive at " + currentDirection.substr(currentDirection.find(" from ") + 6);
            directionSets.push(newDirection);
            directions.pop();
        }
        else if (currentDirection.substr(0,4) == "Head" && !isLastSet)
        {
            newDirection = "Arrive at " + currentDirection.substr(currentDirection.find(" from ") + 6);
            directionSets.push(newDirection);
            directionSets.push(" ");
            directions.pop();
        }
        else
        {
            previousDirection = getOppositeDirection(currentDirection.substr(5, currentDirection.find(" at ") - 5));
            directions.pop();
        }
    }
    
    while (!directions.empty())
    {
        currentDirection = directions.top();
        directions.pop();

        if (directions.empty() && isLastSet)
        {
            if (previousDirection == "Continue")
            {
                newDirection = "Continue on " + getStreet(currentDirection.substr(currentDirection.find(" from ") + 6));
            }
            else
            {
                newDirection = "Turn " + previousDirection + " at " + getStreet(currentDirection.substr(currentDirection.find(" from ") + 6));
            }

            directionSets.push(newDirection);
            newDirection = "Arrive at " + currentDirection.substr(currentDirection.find(" from ") + 6);
            directionSets.push(newDirection);

            return;
        }
        else if (directions.empty())
        {
            if (previousDirection == "Continue")
            {
                newDirection = "Continue on " + getStreet(currentDirection.substr(currentDirection.find(" from ") + 6));
            }
            else
            {
                newDirection = "Turn " + previousDirection + " at " + getStreet(currentDirection.substr(currentDirection.find(" from ") + 6));
            }

            directionSets.push(newDirection);
            newDirection = "Arrive at " + currentDirection.substr(currentDirection.find(" from ") + 6);
            directionSets.push(newDirection);
            directionSets.push(" ");

            return;
        }

        if (currentDirection.substr(0, 8) == "Continue" && previousDirection != "Continue") 
        {
            newDirection = "Turn " + previousDirection + " at " + currentDirection.substr(12);
            previousDirection = "Continue";
            directionSets.push(newDirection); 
        }
        else if (previousDirection == "Continue")
        {
            newDirection = "Continue on " + currentDirection.substr(currentDirection.find("at") + 3);
            previousDirection = getOppositeDirection(currentDirection.substr(5, currentDirection.find(" at ") -5));
            directionSets.push(newDirection);
        }
        else
        {
            newDirection = "Turn " + previousDirection + " at " + currentDirection.substr(currentDirection.find("at")+3);
            previousDirection = getOppositeDirection(currentDirection.substr(5, currentDirection.find(" at ") -5));
            directionSets.push(newDirection);
        }
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Reads the text from a file                                            |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: read() 
{
    ifstream MyReadFile(fileToRead);
    string direction;
    stack <string> setDirections;
    int numberOfDirectionSets = 1;
    
    while (getline (MyReadFile, direction) && direction[0] != '0') 
    {
        if (isdigit(direction[0])) 
        {
            if (numberOfDirectionSets != 1)
            {
                headHome(setDirections, false);

                while (!setDirections.empty())
                {
                    setDirections.pop();
                }

                currentCardinalDirection = "";
                numberOfDirectionSets++;
            } 
            else 
            {
                numberOfDirectionSets++;
            }
        } 
        else
        {
            string instructionDirection = direction.substr(5, direction.find(" at ") - 5);
            string cardinalDirection = direction.substr(5, direction.find(" from ") - 5);

            if (instructionDirection == "right" || instructionDirection == "left")
            {
                updateCardinalDirection(instructionDirection);
            }
            else if (isCardinalDirection(cardinalDirection))
            {
                currentCardinalDirection = cardinalDirection;
            }

            setDirections.push(direction); 
        }
    }

    headHome(setDirections, true);

    while (!setDirections.empty())
    {
        setDirections.pop();
    }

    currentCardinalDirection = "";
}

//-----------------------------------------------------------------------|
//                                                                       |
// Outputs the directions to the console                                 |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: output() 
{
    int counter = 1;

    cout << endl << "Directions " << to_string(counter) << ":" << endl;

    while (!directionSets.empty()) 
    {
        string currentDirection = directionSets.front();

        if (currentDirection == " ") 
        {
            counter++;
            cout << endl << "Directions " << to_string(counter) << ":" << endl;
            directionSets.pop();
        } 
        else 
        {
            cout << currentDirection << endl;
            directionSets.pop();
        }
    }
}

//-----------------------------------------------------------------------|
//                                                                       |
// Writes the directions to another file                                 |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: write() 
{
    fstream file; 
    file.open(fileToWrite, ios::out);

    int counter = 1;

    file << "Directions " << to_string(counter) << ":" << endl;

    while (!directionSets.empty()) 
    {
        string currentDirection = directionSets.front();

        if (currentDirection == " ") 
        {
            counter++;
            file << endl << "Directions " << to_string(counter) << ":" << endl;
            directionSets.pop();
        } 
        else 
        {
            file << currentDirection << endl;
            directionSets.pop();
        }
    }

    file.close();
    cout << "File successfully written!" << endl;
}

//-----------------------------------------------------------------------|
//                                                                       |
// Executes the program                                                  |
//                                                                       |
//-----------------------------------------------------------------------|

void Reader:: run() 
{
    int menuSelection = getMenuSelection();
    cin.clear();

    string fileToRead;
    string fileToWrite;

    while (menuSelection != 0)
    {
        if (menuSelection == 1) 
        {
            cout << "Please enter the name of the text file you would like to read -> ";
            getline(cin, fileToRead);
            cin.clear();

            while (!isValidFile(fileToRead, false))
            {
                cout << "Please enter a valid file name -> ";
                cin.clear();
                getline(cin, fileToRead);
            }

            setFileToRead(fileToRead);
            read();
            output();
        }
        else if (menuSelection == 2)
        {
            cout << "Please enter the name of the file you would like to read -> ";
            getline(cin, fileToRead);
            cin.clear();

            while (!isValidFile(fileToRead, false))
            {
                cout << "Please enter a valid file name -> ";
                cin.clear();
                getline(cin, fileToRead);
            }

            setFileToRead(fileToRead);
            read();

            cout << "Please enter the name of the file you would like to write to -> ";
            getline(cin, fileToWrite);
            cin.clear();

            while (!isValidFile(fileToWrite, true))
            {
                cout << "Please enter a valid file name -> ";
                cin.clear();
                getline(cin, fileToWrite);
            }

            setFileToWrite(fileToWrite);
            write();
        }

        cin.clear();
        menuSelection = getMenuSelection();
    }  
}