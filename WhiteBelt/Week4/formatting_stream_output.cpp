#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // formatting streams 
using namespace std;

int main() {
    vector<string> names = {"Garcia", "Alma", "Guaga"};
    vector<int> ages = {21, 32.01, 2500.20201};
    
    cout << setfill('.'); // fiil empty space with dots instead of spaces
    cout << left; // output elemets to theleft of the set width space
    for (const auto& n : names) {
        cout << setw(10) << n << " "; // sets width for each element
    }
    cout << endl;
    
    cout << fixed << setprecision(5); // fixed shows numbers without exponent 10e2, precision - number of figures after the dot
    for (const auto& a : ages) {
        cout << setw(10) << a << " "; // sets width for each element
    }
    return 0;
}