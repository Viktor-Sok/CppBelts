#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

template <typename It>
void printRange(It begin, It end) {
    // loop for iterators is analof of for (int i = 0; i < N; i++)
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }
}

int main() {
    set<string> s = {"C", "B", "A"};
    printRange<set<string>::iterator>(s.begin(), s.end());
    // let's create vector from set by passing iterators to the vector constructor
    vector<string> v(s.begin(), s.end());
    printRange<vector<string>::iterator>(v.begin(), v.end());
    return 0;
}