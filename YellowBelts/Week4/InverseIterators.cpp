#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename It>
void printRange(It begin, It end) {
    // loop for iterators is analof of for (int i = 0; i < N; i++)
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    vector<char> v = {'a', 'b', 'c', 'd'};
    // print vector in reverse order using reversed iterators
    printRange<vector<char>::reverse_iterator>(v.rbegin(), v.rend());
    // sort in descending order using reversed iterators
    sort(rbegin(v), rend(v));
    printRange(v.begin(), v.end());
    return 0;
}