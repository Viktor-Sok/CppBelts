#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // all the algorithms with iterators
#include <set>
#include <iterator> // back_inseter here

using namespace std;
typedef vector<string> Vec; // Vec look like a new variable of type vector<string> which is itself is a new type
// using Vec = vector<string>; // analog
typedef set<int> Set;

template <typename It>
void printRange(It begin, It end) {
    // loop for iterators is analof of for (int i = 0; i < N; i++)
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}


int main() {
    Vec v = {"A", "B", "C", "C", "D",};
    Vec res; // size of res will be determined in runtime
    // we are gonna use back_inserter iterator
    copy_if(v.begin(), v.end(), back_inserter(res), [](const auto& letter){return letter == "C";});
    printRange(res.begin(), res.end());
    // insert into set
    Set s1 = {1, 2, 3, 4};
    Set s2 = {2, 5, 1, 4};
    Set result;
    auto itRes = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(result, end(result)));
    printRange(result.begin(), result.end()); 
    return 0;
}