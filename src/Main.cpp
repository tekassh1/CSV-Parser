#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "CSVReader.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "\nYou should input path to .csv file to the program arg. Try again.\n\n";
        return 0;
    }
    
    CSVReader csv_reader(argv[1]);

    if (!csv_reader.checkFile()) {
        cout << "\nFile doesn't exists or doesn't acceptable. Try again.\n";
        return 0;
    }

    csv_reader.parseCSV();
    cout << endl << "\t\t --- Input Table --- \n" << endl;
    cout << csv_reader.show() << endl << endl;
}