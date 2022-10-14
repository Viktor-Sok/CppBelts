#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;
using Vec = vector<string>;
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
    Vec v = {"A", "B", "C", "C", "E",};
    // split container using a condition
    // all elements which evaluete condition as true will be moved at the beggining of container
    partition(v.begin(), v.end(), [](const auto& letter){return letter == "C";});
    printRange(v.begin(), v.end());
    // copying elements to another vector v -> v1 using condition
    Vec v1(v.size());
    auto itV1_end  = copy_if(v.begin(), v.end(), v1.begin(), [](const auto& letter){return letter == "C";});
    // using iterator to the end of the array v1, we can effectively resize it (before, it was initialized the same length
    // as v)
    printRange(v1.begin(), itV1_end);

    // Intersection of sets
    // NB: There exist set_unioun, set_difference
    Set s1 = {1, 2, 3, 4};
    Set s2 = {2, 5, 1, 4};
    vector<int> result(s1.size());
    auto itRes = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), result.begin());
    result.erase(itRes, result.end()); // deleting unused memory cells from result
    printRange(result.begin(), result.end());    
    return 0;
}