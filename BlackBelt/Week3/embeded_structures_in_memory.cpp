#include <iostream>

#define SIZEOF(T) (cout << #T << ":\t" << "sizeof = " << sizeof(T) << '\t' << "alignof = " <<  alignof(T) << '\n')
using namespace std;

struct Inner {
    int i; //4
    char c; //1
};

struct Outer {
    Inner is1; //8
    Inner is2; //8
    char c; //1
};

int main() {
    SIZEOF(Inner);
    return 0;
}