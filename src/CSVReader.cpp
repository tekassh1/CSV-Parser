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

            if (!isNumber(touple_number))
                return false;

            table_container.addToupleNumber(touple_number);
            values.erase(values.begin());

            if (values.size() != table_container.getColumns().size())
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
    line += ",";
    stringstream ss(line);

    while(getline(ss, tmp, ',')){
        out.push_back(tmp);
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

void CSVReader::calculateCells(){
    vector<string> columns = table_container.getColumns();
    vector<string> touples = table_container.getToupleNumbers();

    for (int i = 0; i < touples.size(); i++){
        string touple = touples[i];
        for (int j = 0; j < columns.size(); j++){
            string column = columns[j];

            string elem = table_container.getElem(column, touple);
            if (elem == "#ЗНАЧ!")
                continue;
            
            if (isOperation(elem)){
                string key = column + touple;
                string new_val = performCalculation(key);
                table_container.removeElem(key);
                table_container.addElem(column, touple, new_val);
            }
            else
                continue;
        }
    }
}

string CSVReader::performCalculation(string key){
    vector<string> values;
    string elem = table_container.getElem(key);

    if (elem == "#ЗНАЧ!")
        return "#ЗНАЧ!";

    char op;
    int sep_pos;

    if (elem.find('+') != string::npos) {
        sep_pos = elem.find('+');
        op = '+';
    }
    if (elem.find('-') != string::npos) {
        sep_pos = elem.find('-');
        op = '-';
    }
    if (elem.find('*') != string::npos) {
        sep_pos = elem.find('*');
        op = '*';
    }
    if (elem.find('/') != string::npos) {
        sep_pos = elem.find('/');
        op = '/';
    }

    string cell1 = elem.substr(1, sep_pos - 1);
    string cell2 = elem.substr(sep_pos + 1, elem.length());

    string cell1_content = table_container.getElem(cell1);
    string cell2_content = table_container.getElem(cell2);

    int num1;
    int num2;

    // If cells that we need to operate are operations (recursive count and check for cycle)
    if (isOperation(cell1_content)){
        calculate_rec_calls.insert(cell1_content);
        string op_rec = performCalculation(cell1_content);
        calculate_rec_calls.erase(cell1_content);
        if (op_rec == "#ЗНАЧ!") {
            
        }
        else {
            cell1_content = op_rec;
        }
    }
    if (isOperation(cell2_content)){
        calculate_rec_calls.insert(cell2_content);
        string op_rec = performCalculation(cell2_content);
        calculate_rec_calls.erase(cell2_content);
        if (op_rec == "#ЗНАЧ!") {
            
        }
        else {
            cell2_content = op_rec;
        }
    }

    num1 = stoi(cell1_content);
    num2 = stoi(cell2_content);
    int res;

    switch (op)
    {
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        if (num2 == 0)
            return "#ЗНАЧ!";
        res = num1 / num2;
        break;
    default:
        break;
    }

    return to_string(res);
}