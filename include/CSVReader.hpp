#ifndef CSVReader_H
#define CSVReader_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class CSVReader{
    char* file_name;
    FILE* file;
    string csv_data;
    vector<vector<string>> input_table;

    vector<string> commaSplit(string line);

public:
    CSVReader(char* file_name);

    bool checkFile();
    void parseCSV();

    FILE* getFile();
    vector<vector<string>> getInputTable();
    string getStringTableRepresentation();
};

#endif