#include <iostream>

using namespace std;

struct Data {
    int number;
    char c1;
    char c2;
    char c3;
    int region;
};

int main() {
    cout << sizeof(Data) << endl;
    // offsetof shows the location of the stuct field starting from the beginning of struct
    // shuffling fields in struct Data results in different sizeof()
    // The reason of that is padding, compilator tries to aadjuct size of ech filed to the largest one foe alingment
    // It's  necessary for effective access to the memory
    cout << offsetof(Data, number) << endl; 
    cout << offsetof(Data, c1) << endl;
    cout << offsetof(Data, c2) << endl;
    cout << offsetof(Data, c3) << endl;
    cout << offsetof(Data, region) << endl;
    return 0;
}


