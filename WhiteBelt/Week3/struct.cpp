#include <iostream>
#include <string>
using namespace std;

struct Lecture {
    // this field wiil be intiialized by default
    string author = "Charls Dickens";
    int duration;
};

struct DetailedLecture {
    Lecture lec_title;
    int raiting;
};

void printLec(Lecture& const lec) {
    cout << lec.author << " " << lec.duration << endl;
}

Lecture getLec() {
    // returns struct Lecture initializing it
    return {"Max", 10};
}
int main() {
    // initializing structure
    Lecture first_lec = {"Viktor", 20};
    return 0;
    // passing struct into function and initializing at the same time
    printLec({"Sonya", 30});
    // recieving struct from a function
    Lecture second_lec = getLec();
    // initializing structure within structure
    DetailedLecture det_lec = {{"Anton", 50}, 5};
    // accesing embedded structures
    cout << det_lec.lec_title.author << endl;
    // default values in struct
    Lecture lec; 
    cout << lec.author << endl; // Will be Charls Dickens by default
}