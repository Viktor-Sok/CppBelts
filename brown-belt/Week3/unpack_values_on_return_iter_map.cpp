#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum Names {
    one = 1, two, three, wrong_value 

};
vector<string> lookupForEnumNames = {"one", "two", "three","wrong_value"};

pair<string, int> getNameOfNumber(int n) {
    Names names = (n > 0 || n < 4) ?  (Names)n : wrong_value;
    string name = lookupForEnumNames[names - 1];
    return {name, n};
}

int main() {
    auto [name, n] = getNameOfNumber(2); // unpacking pair
    cout << "Return pair from a functioin: " << name << ": " << n << endl;
    map<string, int> m;
    auto [it, inserted] = m.insert({"one", 1}); // it iterator to the inserted value, inserted is a bool flag
    if(inserted) {
        cout << "Insertion in the map: " << it -> first << ": " << it -> second << endl;
    }

    return 0;
}