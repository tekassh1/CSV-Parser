#include <iostream>
#include <fstream>

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

void CSVReader::parseCSV(){
    ifstream ifs(file_name);
    string line;

    if (ifs.is_open()){
        while (getline(ifs, line)) {
            vector<string> splitted_line;
            splitted_line = commaSplit(line);
            input_table.push_back(splitted_line);
        }
    }
    ifs.close();
}

FILE* CSVReader::getFile(){
    return this->file;
}

vector<vector<string>> CSVReader::getInputTable() {
    return input_table;
}

string CSVReader::getStringTableRepresentation(){
    string res;
    for (int i = 0; i < input_table.size(); i++){
        string tmp;
        for (int j = 0; j < input_table[i].size(); j++) {
            tmp += (j == 0 ? input_table[i][j] : "\t" + input_table[i][j]);
        }
        res += tmp + "\n";
        tmp = "";
    }
    return res;
}