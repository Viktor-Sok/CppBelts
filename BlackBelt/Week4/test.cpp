#include <iostream>

using namespace std;
struct Student {
    string Name;
    double Rating;

    void Print() const {
        cout << Name << " " << Rating << "\n";
    }
};
int name() {
    
     // Allocate object in the reserved memory in the heap
     Student {"Petr", 4.0}; 
     char* buf = new char[1024]; // buffer in the heap
     Student* s = new (buf) Student{"Petr", 4.0}; // new creates object in reserved buffer
     s -> Print();
     s -> ~Student();
     delete [] buf;
    return 0;
}