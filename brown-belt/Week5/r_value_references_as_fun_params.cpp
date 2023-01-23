#include <iostream>
#include <string>
#include <utility>

using namespace std;
struct Time {
    int hours;
    int min;
};

void printRvalue(string s, Time&& t) {
    cout << s << t.hours << " : " << t.min << endl;
}   
/*
// specialization, becouse different objects T will have different fields
template<typename T>
void printBothRLvalue(string, T&&){};
template<> // template specialization
void printBothRLvalue<Time>(string s, Time&& t) {
    cout << s << t.hours << " : " << t.min << endl;
}
*/

template<typename T>
void printBothRLvalue(string, T&& t){
    cout << s << t.hours << " : " << t.min << endl;
};

int main() {
    Time t {3, 40};
    //printRvalue("Time: ", t); doesn't work with lvalue
    printRvalue("Time: ", move(t)); // move make t as a temprorary object
    printRvalue("Time: ", Time {2, 50}); 

    // function template with T&& accepts both rvalue and lvalue
    printBothRLvalue("Time: ", t);
    printBothRLvalue<Time>("Time: ", Time {2, 15});
    return 0;
}