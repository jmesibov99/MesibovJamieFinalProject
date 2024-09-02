/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 5 	Lesson #P8.10
** File: MesibovJamieSignatureAssignmentP8.10 	MesibovJamieSignatureAssignmentP8.10 .cpp
** Description: Encrypts and decrypts text using the Playfair cipher with a keyword-
** based 5x5 matrix.
**
** Author: 	Jamie Mesibov
** Date: 	9/1/2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Function to create the Playfair cipher matrix
void createMatrix(const string& key, vector<vector<char>>& matrix) 
{
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // I and J are considered the same
    string keyString = key;

    // Remove duplicates from the key
    string temp;
    for (char c : keyString) 
    {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Treat I and J as the same
        if (temp.find(c) == string::npos) 
        {
            temp += c;
        }
    }
    keyString = temp;

    // Add the alphabet letters not in the key
    for (char c : alphabet) 
    {
        if (keyString.find(c) == string::npos) 
        {
            keyString += c;
        }
    }

    // Fill the 5x5 matrix
    int index = 0;
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 5; ++j) 
        {
            matrix[i][j] = keyString[index];
            ++index;
        }
    }
}

// Function to find the position of a character in the matrix
void findPosition(const vector<vector<char>>& matrix, char c, int& row, int& col) 
{
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 5; ++j) 
        {
            if (matrix[i][j] == c) 
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to process the text for encryption or decryption
string processText(const vector<vector<char>>& matrix, string text, bool encrypt) 
{
    string result;

    // Prepare the text (remove non-letters, replace J with I, make pairs)
    string cleanText;
    for (char c : text) 
    {
        if (isalpha(c)) 
        {
            c = toupper(c);
            if (c == 'J') c = 'I';
            cleanText += c;
        }
    }

    // Add padding 'X' if necessary to ensure even length for pairing
    if (cleanText.length() % 2 != 0) 
    {
        cleanText += 'X';
    }

    // Process each pair
    for (size_t i = 0; i < cleanText.length(); i += 2) 
    {
        char a = cleanText[i];
        char b = cleanText[i + 1];

        int rowA, colA, rowB, colB;
        findPosition(matrix, a, rowA, colA);
        findPosition(matrix, b, rowB, colB);

        if (rowA == rowB) // Same row
        { 
            result += matrix[rowA][(colA + (encrypt ? 1 : 4)) % 5];
            result += matrix[rowB][(colB + (encrypt ? 1 : 4)) % 5];
        }
        else if (colA == colB) // Same column
        { 
            result += matrix[(rowA + (encrypt ? 1 : 4)) % 5][colA];
            result += matrix[(rowB + (encrypt ? 1 : 4)) % 5][colB];
        }
        else // Rectangle swap
        { 
            result += matrix[rowA][colB];
            result += matrix[rowB][colA];
        }
    }

    // Handle the case where an extra 'X' was added for padding
    if (!encrypt && result.back() == 'X') 
    {
        result.pop_back(); // Remove the extra 'X'
    }

    return result;
}

int main() 
{
    string keyword, text;
    char choice;
    vector<vector<char>> matrix(5, vector<char>(5));

    // Prompt user for keyword
    cout << "Enter the keyword: ";
    getline(cin, keyword);

    createMatrix(keyword, matrix);

    // Prompt to select encryption mode
    cout << "Would you like to (E)ncrypt or (D)ecrypt? ";
    cin >> choice;
    cin.get();  // Consume the newline character

    cout << "Enter the text: ";
    getline(cin, text);

    if (choice == 'E' || choice == 'e') 
    {
        cout << "Encrypted text: " << processText(matrix, text, true) << endl;
    }
    else if (choice == 'D' || choice == 'd') 
    {
        cout << "Decrypted text: " << processText(matrix, text, false) << endl;
    }
    else 
    {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
