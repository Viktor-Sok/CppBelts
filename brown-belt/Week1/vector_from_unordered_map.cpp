#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map> // use it when sorting by key is not requaried (it's much faster)
#include <vector>

using namespace std;

template <typename A, typename B>
void printVec(const vector<pair<A, B>>& v) {
    for (const auto& p : v) {
        cout << p.first << ", " << p.second << " ";
    }
} 

template <typename A, typename B>
void printMap(const unordered_map<A, B>& m) {
    for (const auto& [k, v] : m) {
        cout << k << ": " << v << endl;
    }
}

int main() {
    unordered_map<string, int> wordCount = {{"the", 100}, {"a", 200}, {"then", 10}};
    // Constracting vector from the map using iterators e.g. to sort by values (maps only sorted by keys)
    vector<pair<string, int>> v(wordCount.begin(), wordCount.end());
    printMap(wordCount);
    printVec(v);
    cout << endl;
    // Sorting using iterators and sort algorythm
    sort(begin(v), end(v), [](const auto& l, const auto& r){return l.second < r.second;});
    printVec(v);

    return 0;
}

