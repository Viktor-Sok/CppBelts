#include <iostream>

#define SIZEOF(T) (cout << #T << ":\t" \
                        << "sizeof = " << sizeof(T) << '\t' \
                        << "alignof = " <<  alignof(T) << '\n')
using namespace std;

struct Base1 { //8
    int i; //4
    char c; //1
};

struct Base2 {  //8
    bool b; //1
    float f; //4
};

struct Outer : Base1, Base2 { //20
    // this kind of inheritance is stored in memory the same way as if fields of Base1 and Base2 were just define inside class Outer
    short sh; //2
};

int main() {
    SIZEOF(Base1);
    SIZEOF(Base2);
    SIZEOF(Outer);
    return 0;
}