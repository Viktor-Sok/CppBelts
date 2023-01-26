#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/* Using exceptions for returning is a bad idea - it's slow
   It's much more efiicient to use std::variant for that purpose
*/

struct Error {
    double x;
    Error(int x) : x(x) {}
    string s = "Division by zero!";
};

double divide(double x, double y) {
    if (abs(y) > 1e-5) {
        return x/y;
    } else {
        Error err(x); // our custom object
        throw err; // throw will return our object abd we have to catch arror with the tapy Error
    }
}

int main() {
    try {
        auto res = divide(5, -1e-6);
        cout << "Division result: " << res << endl;
    } catch (const Error& e) { // we are catching our structure here, basically throw returns it from function
        cout << "We cannot divide " << e.x << " : " << e.s << endl;
    }
    return 0;
}