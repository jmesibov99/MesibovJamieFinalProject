/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment:5	Lesson #P8.2
** File:MesibovJamieSignatureAssignmentP8.2 	MesibovJamieSignatureAssignmentP8.2.cpp
** Description: Using UNIX dictionary file, cross-check a user-provided file for misspelled words and print them.
**
** Author: 	Jamie Mesibov
** Date: 	8/18/2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Convert a string to lowercase
string toLowerCase(string inputString)
{
    for (int i = 0; i < inputString.length(); i++)
    {
        inputString[i] = tolower(inputString[i]);
    }
    return inputString;
}

// Remove punctuation from a string manually
string removePunctuation(string inputString)
{
    string cleanString = "";
    const string punctuation = ".,!?;:()[]{}\"'";
    for (int i = 0; i < inputString.length(); i++)
    {
        if (punctuation.find(inputString[i]) == string::npos)
        {
            cleanString += inputString[i];
        }
    }
    return cleanString;
}

int main()
{
    // Try to open the dictionary file from the same folder as the program
    string dictionaryFilePath = "words.txt";
    ifstream dictionaryFile(dictionaryFilePath);

    // If the file can't be opened, request the file path from the user
    if (!dictionaryFile)
    {
        cout << "Dictionary file not found in the program's directory." << endl;
        cout << "Enter the path of the dictionary file: ";
        getline(cin, dictionaryFilePath);
        dictionaryFile.open(dictionaryFilePath);

        if (!dictionaryFile)
        {
            cout << "Error: Could not open the dictionary file at " << dictionaryFilePath << endl;
            return 1;
        }
    }

    // Read words from the dictionary file into a vector
    vector<string> wordsVector;
    string word;
    while (dictionaryFile >> word)
    {
        wordsVector.push_back(toLowerCase(word));
    }
    dictionaryFile.close();

    // Path of the file to be checked
    string fileToCheckPath;
    cout << "Enter the path of a file to be spell-checked: ";
    getline(cin, fileToCheckPath);

    // Open the file to be checked
    ifstream fileToCheck(fileToCheckPath);
    if (!fileToCheck)
    {
        cout << "Error: Could not open the file to be spell-checked at " << fileToCheckPath << endl;
        return 1;
    }

    // Check each word in the file to be checked
    int misspelledWordsCount = 0;
    while (fileToCheck >> word)
    {
        word = toLowerCase(word);
        word = removePunctuation(word);

        // Check if the word is in the dictionary
        bool found = false;
        for (const string& dictWord : wordsVector)
        {
            if (word == dictWord)
            {
                found = true;
                break;
            }
        }

        if (!found && !word.empty())
        {
            cout << "Misspelled word: " << word << endl;
            misspelledWordsCount++;
        }
    }
    fileToCheck.close();

    // Print message if no misspelled words were found
    if (misspelledWordsCount == 0)
    {
        cout << "No misspelled words found." << endl;
    }

    return 0;
}
