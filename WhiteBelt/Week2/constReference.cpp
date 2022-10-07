#include <iostream>
#include <vector>
using namespace std;

int sum(int a, int b) {
    return a + b;
}

void printSum(int& const s) {
    cout << s << endl;
}

int main() {
    int a = 5;
    int b = 4;
    // it's only possible to pass result from function to anotehr function by reference
    // if function recieves it by const reference 
    printSum(sum(a, b)); 
    return 0;
}