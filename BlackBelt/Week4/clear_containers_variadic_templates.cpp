#include <iostream>
#include<string>
#include<vector>

using namespace std;

template <typename ... Args>
void PrintSizes(const Args& ... args) {
    ((cout << typeid(args).name() << ": " << args.size()<< endl), ...);
}

template <typename ... Args>
void Clear(Args& ... args) {
    (args.clear(), ...);
}

int main() {
    vector v = {1, 2, 3};
    string s = "Hello";
    Clear(v,s);
    PrintSizes(v,s);
    return 0;
}