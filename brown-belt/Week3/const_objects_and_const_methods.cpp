#include <iostream>
#include <string>

using namespace std;

class Lock {
public:
    string state = "Locked";
    void just_print() const { // const qualifier is requaried to work with function get_lock_description
        cout << "The Lock fo the house!" << endl;
    }    
};

void get_lock_description(const Lock& l) {
    // method just_print() doesn't change any fields and internal state of the Lock object
    // but it won't compile without const specifier becouse we pass Lock Object into fuinction by constant reference 
    l.just_print();
}

int main() {
    Lock l;
    get_lock_description(l);
    return 0;
}