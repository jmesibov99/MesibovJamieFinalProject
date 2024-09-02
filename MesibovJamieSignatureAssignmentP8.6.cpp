/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment:5 	Lesson #P8.6
** File:MesibovJamieSignatureAssignmentP8.6 	MesibovJamieSignatureAssignmentP8.6.cpp
** Description: Reads the file path for "worldpop.txt", calculates the
** total population (excluding the European Union line), and prints the result.
**
** Author: 	Jamie Mesibov
** Date: 	8/25/2024
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
    // Attempt to open the file 'worldpop.txt' in the current directory
    ifstream inputFile("worldpop.txt");

    // If the file isn't found, prompt the user to enter the file path
    if (!inputFile) 
    {
        string filePath;
        cout << "Could not find 'worldpop.txt'. Enter the file path: ";
        getline(cin, filePath);
        inputFile.open(filePath);
        
        // If the file still can't be opened, display an error message and exit
        if (!inputFile) 
        {
            cout << "Error: File could not be opened." << endl;
            return 1;
        }
    }

    // Variables for storing population data and total population
    long long population, totalPopulation = 0;
    string line, country;
  
    // Read each line from the file
    while (getline(inputFile, line)) 
    {
        // Find the position of the last space or tab character
        size_t pos = line.find_last_of(" \t");
        if (pos != string::npos) 
        {
            // Extract and convert the population value from the line
            try 
            {
                population = stoll(line.substr(pos + 1));
                country = line.substr(0, pos);

                // Add population to total if the country is not "European Union"
                if (country != "European Union") 
                {
                    totalPopulation += population;
                }
            }
            // Handle any errors that occur during conversion
            catch (...) 
            {
                cout << "Error parsing population from line: " << line << endl;
            }
        }
    }

    inputFile.close();  // Close the file

    
    // Output the total world population, excluding the European Union
    cout << "Total world population: " << totalPopulation << endl;

    return 0;
}
