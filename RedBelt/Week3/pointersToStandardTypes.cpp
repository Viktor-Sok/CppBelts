#include <iostream>
using namespace std;

int main() {
    int a = 2;
    int* p1 = new int; // pointer to memory without inisialization
    p1 = &a; // getting adress of the variable a
    int* p2 = new int(5); // constructor initialization
    int* p3 = new int {4}; // uniform initialization
    int& rp2 = *p2; // dereferencing a pointer returns reference

    cout << *p1 << " " << rp2 << " " << *p3 << endl;
    return 0;
}
