#include <iostream>
#include <deque>
#include <algorithm> // all the algorithms with iterators
#include<vector>
#include <set>
#include<string>
using namespace std;
using Vec = vector<int>;
using Set = set<int>;

template <typename It>
void printRange(It begin, It end) {
    // loop for iterators is analof of for (int i = 0; i < N; i++)
    for (auto it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}


int main() {
    // count and find for unsorted vector
    Vec v = {1, 2, 3 ,2, 5, 2};
    // find_if to find elemts that agree to specific condition
    int n = count(begin(v), end(v), 2);
    auto it = find(begin(v), end(v), 3);
    cout << n << " " << it - begin(v) << endl; // difference between iterators returns index of the element in a vector
    // count and find for set
    Set s = {5, 2, 2, 5, 5, 3};
    printRange(begin(s), end(s));
    int n1 = s.count(5); // ether 1 or 0 becouse there is no dublicates in set
    auto it1 = s.find(3);
    cout << n1 << " " << *it1 << endl;
    // find position of  the all blank spaces in a string
    string str = "1 234 56 789";
    for (auto it = find(begin(str), end(str), ' '); it != end(str); it = find(next(it), end(str), ' ')) {
        cout << it - begin(str) << " ";
    }
    //search in the sorted vector
    /*
    bool found = binary_search(begin(v), end(v), 2); // checks existence of an element
    auto it = lower_bound(begin(v), end(v), 2); // first element less or equal to val, returns iterator to that element
    auto it = upper_bound(begin(v), end(v), 2); // first element greater than  the val
    pair its = equal_range(begin(v), end(v), 2); // pair of iterators to lower and upper bound for a val , if it1 = it2 then there is no such element
    */
   //search in the set
   //s.count(), s.find(), s.lower_bound(), s.upper_bound(), s.equal_range 
    return 0;
}
    