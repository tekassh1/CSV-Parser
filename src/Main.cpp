#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "\nYou should input path to .csv file to the program arg. Try again.\n\n";
        return 0;
    }

    string file_path = argv[1];
    ifstream fin;
    FILE* file;
}