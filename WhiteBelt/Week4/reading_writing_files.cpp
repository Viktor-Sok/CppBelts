#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
void readUpToDelimeter() {
    ifstream input ("myFile.txt")
    string line1, line2;
    if (input) {
        getline(input, line1, '-'); // delimiter is a dash
        getline(input, line2, '-');
        cout << line1 << " " << line2 << endl;
    }
    input.close();
}

void readUpToDelimiterStreamingOperators() {
    ifstream input ("myFile.txt")
    int line1, line2;
    if (input) {
        input >> line1;
        input.ignore(1); // ignore one symbol in the stream
        input >> line2;
        cout << line1 << " " << line2 << endl;
    }
    input.close();
}

void lineByline() {s
    ifstream input("myFile.txt");
    if(input) {
        string line;
        while(getline(input, line)) {
            // do something with line
        }
    }
}

int main() {
    // read formatted file by delimeters(e.g. 12-10-22) using getline
    readUpToDelimeter();
    // read formatted file by delimeters(e.g. 12-10-22) using streaming operator >>
    // >> is overloaded bitwise shift operator
    readUpToDelimiterStreamingOperators();
    // reading line by line using getline
    lineByline();
    // writing file in append mode
    ofstream output("myFileOut.txt", ios::app); // in append mode
    output << "Write something" << endl;
    return 0;
}