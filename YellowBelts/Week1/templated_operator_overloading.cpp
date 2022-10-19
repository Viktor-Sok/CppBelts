#include <iostream>
#include <tuple>
#include<vector>
#include <assert.h>
#include <utility> // contains Pair data stracture

using namespace std;

template <typename T1, typename T2>
pair<T1,T2> operator *(const pair<T1,T2>& p1, const pair<T1,T2>& p2) {
    // defines multiplication operator for pairs
    return make_pair(p1.first*p2.first, p1.second*p2.second);
}

template <typename T>
ostream& operator <<(ostream& o_ss, const vector<T>& v) {
    // overloading << for putting vector into output stream
    for (const auto& i : v) {
        o_ss << i << " ";
    }
    return o_ss;
}


int main() {
    vector<int> v = {1, 2, 3};
    auto p1 = make_pair(1, 1.2);
    auto p2 = make_pair(2, 3.2);
    auto p = p1 * p2; // * defined for pairs above
    cout << p.first << " " << p.second << endl; 
    // vector to stream
    cout << v << endl;
    return 0;
}   