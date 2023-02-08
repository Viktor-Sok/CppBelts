#include <iostream>

using namespace std;

/*
template <typename T>
T Sum(const T& x) {
    return x;
}

template <typename T, typename ... Args>
T Sum(const T& x, const Args& ... args) { // (... args) parameter packing into args
    return x + Sum(args ...); // (args ...) parameter unpacking
}
*/
template <typename ... Args>
auto Sum(const Args& ... args) {
    return (args + ...); // fold expression
}

int main() {
    cout << Sum(1., 2.3, 5.) << endl;
    return 0;
}