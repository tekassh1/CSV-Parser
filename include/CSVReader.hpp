#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>

#include "TableContainer.hpp"

using namespace std;

class CSVReader{
    char* file_name;
    FILE* file;
    string csv_data;
    TableContainer table_container;
    unordered_set<string> calculate_rec_calls;

    bool isNumber(string input);
    bool isOperation(string input);
    vector<string> commaSplit(string line);
    string performCalculation(string key);
    
public:
    CSVReader(char* file_name);

    bool checkFile();
    bool parseCSV();
    void calculateCells();

    string show();
};