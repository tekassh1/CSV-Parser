#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

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
                    values[i] = "#VALUE!";
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

void CSVReader::show(){
    vector<string> columns = table_container.getColumns();
    vector<string> touples = table_container.getToupleNumbers();

    cout << setw(12) << left << "  ";
    for (int i = 0; i < columns.size(); i++)
            cout << setw(12) << left << columns[i] + ',';
    cout << endl;

    for (int i = 0; i < touples.size(); i++){
        cout << setw(12) << left << touples[i] + ',';
        for (int j = 0; j < columns.size(); j++){
            string val = table_container.getElem(columns[j], touples[i]);
            cout << setw(12) << left << val + ',';
        }
        cout << endl;
    }
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
            if (elem == "#VALUE!")
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
    calculate_rec_calls.insert(key);

    if (elem == "#VALUE!") {
        calculate_rec_calls.erase(key);
        return "#VALUE!";
    }

    char op;
    int sep_pos;

    if (elem.find('+') != string::npos) {
        sep_pos = elem.find('+');
        op = '+';
    }
    else if (elem.find('-') != string::npos) {
        sep_pos = elem.find('-');
        op = '-';
    }
    else if (elem.find('*') != string::npos) {
        sep_pos = elem.find('*');
        op = '*';
    }
    else if (elem.find('/') != string::npos) {
        sep_pos = elem.find('/');
        op = '/';
    }

    string cell1_addr = elem.substr(1, sep_pos - 1);
    string cell2_addr = elem.substr(sep_pos + 1, elem.length());

    if (!table_container.isExists(cell1_addr))
        return "#VALUE!";
    if (!table_container.isExists(cell2_addr))
        return "#VALUE!";

    string cell1_content = table_container.getElem(cell1_addr);
    string cell2_content = table_container.getElem(cell2_addr);

    int num1;
    int num2;

    // If cells that we need to operate are operations (recursive count and check for cycle)
    if (isOperation(cell1_content)){
        if (calculate_rec_calls.find(cell1_addr) != calculate_rec_calls.end()){
            calculate_rec_calls.erase(key);
            return "#VALUE!";
        }
        string op_rec = performCalculation(cell1_addr);

        if (op_rec == "#VALUE!") {
            calculate_rec_calls.erase(key);
            return op_rec;
        }
        else {
            cell1_content = op_rec;
        }
    }
    else if (cell1_content == "#VALUE!") {
        calculate_rec_calls.erase(key);
            return "#VALUE!";
    }

    if (isOperation(cell2_content)){
         if (calculate_rec_calls.find(cell2_addr) != calculate_rec_calls.end()){
            calculate_rec_calls.erase(key);
            return "#VALUE!";
        }
        string op_rec = performCalculation(cell2_addr);

        if (op_rec == "#VALUE!") {
            calculate_rec_calls.erase(key);
            return op_rec;
        }
        else {
            cell2_content = op_rec;
        }
    }
    else if (cell2_content == "#VALUE!") {
        calculate_rec_calls.erase(key);
        return "#VALUE!";
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
            return "#VALUE!";
        res = num1 / num2;
        break;
    default:
        break;
    }

    calculate_rec_calls.erase(key);
    return to_string(res);
}