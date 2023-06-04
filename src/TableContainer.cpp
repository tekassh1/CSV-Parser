#include <iostream>

#include "TableContainer.hpp"

using namespace std;

void TableContainer::addElem(string column, string touple, string val){
    string key = column + touple;
    table_values[key] = val;
};

string TableContainer::getElem(string column, string touple){
    string key = column + touple;
    return table_values.at(key);
}

void TableContainer::addColumns(vector<string>& columns){
    this->columns = columns;
}

void TableContainer::addToupleNumber(string touple_number){
    touple_numbers.push_back(touple_number);
}

string TableContainer::to_string(){
    for (int i = 0; i < touple_numbers.size(); i++){
        string touple = touple_numbers[i];

        for (int j = 0; j < columns.size(); j++){
            string column = columns[j];
            
            
        }
    }
}

vector<string>& TableContainer::getColumns() {
    return columns;
}

vector<string>& TableContainer::getToupleNumbers() {
    return touple_numbers;
}