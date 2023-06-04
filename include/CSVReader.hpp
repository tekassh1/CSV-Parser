#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "TableContainer.hpp"

using namespace std;

class CSVReader{
    char* file_name;
    FILE* file;
    string csv_data;
    TableContainer table_container;

    bool isNumber(string input);
    bool isOperation(string input);
    vector<string> commaSplit(string line);

public:
    CSVReader(char* file_name);

    bool checkFile();
    bool parseCSV();

    vector<vector<string>> getInputTable();
    string show();
};