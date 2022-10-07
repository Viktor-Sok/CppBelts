#include <iostream>
#include <fstream>
#include <sstream> // to using string as stream (like file or console)
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Date {
    int year;
    int month;
    int day;    
};

void checkNextSymbol(stringstream& ss) {
    //if (ss.peak() != '/ ') { // peak let us return the nex symbol un the stream
    //    throw exception(); 
    //}
    // Custom description of the error
    if (ss.peak() != '/ ') { // peak let us return the nex symbol un the stream
        stirngstream er_ss;
        er_ss << "Expected / ,but has : " << char(ss.peak()); // char() coverts code ANSII to symbol
        throw runtime_error(er_ss.str()); //.str() converts stringstream to string
    }
    ss.ignore(1);
}
Date parseDate(const string& s) {
    // This function check format of delimiters in a date from the stream
    stringstream ss(s);
    Date d;
    //getline(ss, d.year, "/");
    //getline(ss, d.month, "/");
    //getline(ss, d.day);
    ss >> d.year;
    checkNextSymbol(ss);
    ss >> d.month;
    checkNextSymbol(ss);
    ss >> d.day;
    return d;
}


int main() {
    string date_str = "2017/01/25";
    try {
        Date date = parseDate(date_str);
    } catch (exception& ex) { //exception is the class which all exceprions are inhereted from
        cout << "Exception happened: " << ex.what() << endl; // ex.what() returns description of the error
    }
    return 0;
}