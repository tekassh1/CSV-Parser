#include <iostream>
#include "CSVReader.hpp"

using namespace std;

CSVReader::CSVReader(char* file_name){
    this->file_name = file_name;
}

bool CSVReader::checkFile(){
    if (this->file = fopen(file_name, "r")) {
        fclose(file);
        return true;
    } 
    else {
        return false;
    }   
}

void CSVReader::parseCSV(){
    
}