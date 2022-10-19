#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
using vecIt = vector<string>::iterator;  //type of iterator for vector


// template function for printing range with iterators
template <typename It>
void printRange(It begin, It end) {
    // loop for iterators is analof of for (int i = 0; i < N; i++)
    for (auto it = begin; it < end; ++it) {
        cout << *it << " ";
    }
}

int main() {
    vector<string> a = {"A", "B", "C"};
    printRange<vecIt>(a.begin(), a.end());
    return 0;
}