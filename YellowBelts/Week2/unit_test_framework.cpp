#include <iostream>
#include <cassert>
#include <sstream>
#include <set>
#include <string>
#include <map>
#include <exception>
using namespace std;


template <class T, class U>
void assertEqual(const T& t, const U& u, const string& hint) {
    // throws error and prints values
    if(t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

int main() {
    // improving assert
    
    return 0;
}