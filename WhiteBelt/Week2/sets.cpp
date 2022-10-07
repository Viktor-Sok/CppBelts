#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

void printSet(set<string>& const s) {
    for (auto x : s) {
        cout << x << " ";
    }
}
int main() {
    set<string> famous_persons;
    famous_persons.insert("Arnold");
    famous_persons.insert("Van Damm");
    // elemets of the set are sorted automatically and they are unique
    printSet(famous_persons);
    // delete elements
    famous_persons.erase("Arnold");
    // set initialization
    set<string> months = {"January", "February"};
    // set from vector (example of iterator usage)
    vector<string> v = {"a", "b", "b"};
    set<string> s(begin(v), end(v));
    
    return 0;
}