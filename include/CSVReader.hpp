#ifndef CSVReader_H
#define CSVReader_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CSVReader{
    char* file_name;
    FILE* file;
    string csv_data;
    
public:
    CSVReader(char* file_name);

    bool checkFile();
    void parseCSV();
};

#endif