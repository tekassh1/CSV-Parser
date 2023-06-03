#include <iostream>
#include <string>
#include <fstream>

#include "CSVReader.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "\nYou should input path to .csv file to the program arg. Try again.\n\n";
        return 0;
    }
    
    CSVReader csv_reader(argv[1]);
    cout << csv_reader.checkFile() << endl;
}