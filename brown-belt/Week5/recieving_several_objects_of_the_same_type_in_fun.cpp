#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <span>

using namespace std;

struct Time {
    int hours;
    int min;
};
ostream& operator << (ostream& os, const vector<char>& v) {
    for (const auto& i : v)
        cout << i << " ";
    return os;
}
/*-------------Pair of iterators------------*/
using it = vector<char>::iterator;
void upperCase(it begin, it end) {
    // makes upper case letters
    for (auto i = begin; i < end; ++i)
        *i = toupper(*i);
}


/*---------------Pointer-and-Number-of-elements------*/
void upperCase1(char* p, size_t s) {
    // makes upper case letters
    for (int i = 0; i < s; ++i)
        *(p+i) = toupper(*(p+i));
}
/*---------std::span-instead-of-pointer-with-specified-number-of-elements----C++20---*/
/*
void printArray(span<int> arr) {
    for (auto e : arr) {
        cout << e << " ";
    }
}
*/
/*--------std::ranges-instead-of-iterators-std::views-----------*/

/*--------------using Templates ... --------------*/
int main() {
    vector<char> v = {'a', 'b', 'c'};
    upperCase(begin(v), end(v));
    cout << v << endl;

    vector<char> v1 = {'h', 'm', 'f'};
    char* p = &v1[0];
    upperCase1(p, 3);
    cout << v1 << endl;

    
    return 0;
}