#include <iostream>
#include <fstream>
#include <regex>

#include "CSVReader.hpp"

using namespace std;

CSVReader::CSVReader(char* file_name){
    this->file_name = file_name;
}

bool CSVReader::checkFile(){
    if (file = fopen(file_name, "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }   
}

bool CSVReader::parseCSV(){
    ifstream ifs(file_name);
    string line;

    bool is_first = true;
    if (ifs.is_open()){
        while (getline(ifs, line)) {
            if (is_first) {
                vector<string> columns = commaSplit(line);
                columns.erase(columns.begin());
                table_container.addColumns(columns);
                is_first = false;
                continue;
            }

            vector<string> values = commaSplit(line);
            string touple_number = values[0];
            table_container.addToupleNumber(touple_number);
            values.erase(values.begin());

            if (values.size() > table_container.getColumns().size())
                return false;

            for (int i = 0; i < values.size(); i++) {
                if (!isNumber(values[i]) && !isOperation(values[i])) {
                    values[i] = "#ЗНАЧ!";
                }
                table_container.addElem(table_container.getColumns()[i], touple_number, values[i]);
            }
        }
        ifs.close();
    }
    return true;
}

vector<string> CSVReader::commaSplit(string line){
    string tmp = "";
    vector<string> out;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',' || i == line.length() - 1) {
            if (line[i] != ',')
                 tmp += line[i];
                 
            out.push_back(tmp);
            tmp = "";
        }
        else
            tmp += line[i];
    }
    return out;
}

string CSVReader::show(){
    vector<string> columns = table_container.getColumns();
    vector<string> touples = table_container.getToupleNumbers();
    string res = "";
    res += "\t\t";

    for (int i = 0; i < columns.size(); i++){
            res += columns[i];
            if (i != columns.size() - 1)
                res += ",\t\t";
    }
    res += "\n";

    for (int i = 0; i < touples.size(); i++){
        res += touples[i];
        for (int j = 0; j < columns.size(); j++){
            res += "\t\t" + table_container.getElem(columns[j], touples[i]);
            if (j != columns.size() - 1)
                res += ",";
        }
        res += "\n";
    }
    return res;
}

bool CSVReader::isNumber(string input){
    for (int i = 0; i < input.length(); i++){
        if (!isdigit(input[0])) {
            if (i == 0 && (input[0] == '-'))
                continue;
            return false;
        }
    }
    return true;
}

bool CSVReader::isOperation(string input){
    regex expr("^=[a-zA-Z]+[0-9]+[+*/\-][a-zA-Z]+[0-9]+$");
    return regex_match(input, expr);
}