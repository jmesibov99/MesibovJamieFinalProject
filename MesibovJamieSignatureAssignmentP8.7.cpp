/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment:5 	Lesson #P8.7
** File:MesibovJamieSignatureAssignmentP8.7 	MesibovJamieSignatureAssignmentP8.7 .cpp
** Description: Encrypts and decrypts text files using a keyword-based alphabetic cypher
**
** Author: 	Jamie Mesibov
** Date: 	8/30/2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to generate the cipher map based on the keyword
void generateCipherMap(const string& keyword, char cipherMap[26]) 
{
    bool used[26] = { false };
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Remove duplicates from the keyword
    string key = keyword;
    for (size_t i = 0; i < key.size(); ++i) 
    {
        key[i] = toupper(key[i]);
    }

    // Iterate through keyword
    int index = 0;
    for (size_t i = 0; i < key.size(); ++i) 
    {
        char c = key[i];
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) 
        {
            cipherMap[index++] = c;
            used[c - 'A'] = true;
        }
    }

    // Append the rest of the alphabet in reverse order
    for (int i = 25; i >= 0; --i) 
    {
        if (!used[i]) 
        {
            cipherMap[index++] = 'A' + i;
        }
    }
}

// Function to encrypt or decrypt text
string processText(const string& text, const char cipherMap[26], bool decrypt) 
{
    string result;
    for (size_t i = 0; i < text.size(); ++i) 
    {
        char c = text[i];
        if (isalpha(c)) 
        {
            char upperC = toupper(c);
            int index = upperC - 'A';
            if (decrypt) 
            {
                for (int j = 0; j < 26; ++j) 
                {
                    if (cipherMap[j] == upperC) 
                    {
                        result += 'A' + j;
                        break;
                    }
                }
            }
            else {
                result += cipherMap[index];
            }
        }
        else {
            result += c;
        }
    }
    return result;
}

// Function to process the file
void processFile(const string& inputFile, const string& outputFile, const string& keyword, bool decrypt) 
{
    ifstream infile(inputFile.c_str());
    if (!infile) 
    {
        cout << "Error opening input file." << endl;
        return;
    }

    ofstream outfile(outputFile.c_str());
    if (!outfile) 
    {
        cout<< "Error opening output file." << endl;
        return;
    }

    char cipherMap[26];
    generateCipherMap(keyword, cipherMap);

    string line;
    while (getline(infile, line)) 
    {
        string processedLine = processText(line, cipherMap, decrypt);
        outfile << processedLine << endl;
    }
}

// Main function
int main(int argc, char* argv[]) 
{
    if (argc != 5) 
    {
        cout << "Usage: crypt -d|-e -k<KEYWORD> <input file> <output file>" << endl;
        return 1;
    }

    string mode = argv[1];
    string keyword = argv[2];
    string inputFile = argv[3];
    string outputFile = argv[4];

    if (mode != "-d" && mode != "-e") 
    {
        cout << "Invalid mode. Use -d for decryption and -e for encryption." << endl;
        return 1;
    }

    if (keyword.empty()) 
    {
        cout << "Keyword must be provided." << endl;
        return 1;
    }

    bool decryptMode = (mode == "-d");
    processFile(inputFile, outputFile, keyword, decryptMode);

    return 0;
}
