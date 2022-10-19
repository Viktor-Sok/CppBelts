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
    vector<string> v = {"A", "B", "C", "D"};
    // find algorithm
    auto res = find(v.begin(), v.end(), "B");
    // deleting range (B, C, D)
    v.erase(res, v.end());
    printRange(v.begin(), v.end());
    // inserting element before the place an iterator points to 
    v.insert(res, "X");
    printRange(v.begin(), v.end());
    // inserting a range of elements from other container (between A and X)
    vector<string> v1 = {"Y", "Z"};
    v.insert(res, v1.begin(), v1.end());
    printRange(v.begin(), v.end());
    
    // other uses of insert :
    //v.insert(res,{1,2,3})
    //v.insert(res, count, value)
    // removing from vector (Z)
    auto rm = remove_if(v.begin(), v.end(), [](const string& e){return e == "Z";});
    printRange(v.begin(), v.end());
    // removig all the elements after Z (basically it has benn done above)
    v.erase(rm, v.end());
    printRange(v.begin(), v.end());
    // removing consequately equal values
    //NB all functions from <algorithm> return iterators, they don't modify containers 
    // and donn't depend on particular type of container, if we want to modify container we
    // use those iterators and pass tme to container specific methods
    // e.g. unique and erase below
    vector<string> v2 = {"A", "A", "C", "C", "1", "1"};
    auto un = unique(v2.begin(), v2.end());
    v2.erase(un, v2.end());
    printRange(v2.begin(), v2.end());
    //Other algotithms
    //  auto it = min_element(v2.begin(), v2.end())
    //  auto it = max_element(v2.begin(), v2.end())
    //  auto it = minmax_element(v2.begin(), v2.end()) //returns pair of iterators
    return 0;
}
