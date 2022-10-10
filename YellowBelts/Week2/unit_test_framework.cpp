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
    // function which improves assert
    // hint let you find where particular in the code error occyred
    // throws error and prints values
    if(t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

int main() {
    // try/catch block let us tackle the error without haulting the program, execution. i.e.
    // we can run several unit tests at once wnd see their results
    try {
        functionWithUnitTest();
    } catch (runtime_error& e) {
        cout << "test funtionWithUnitTest failed: " << e.what() << endl;
    }
    return 0;
}