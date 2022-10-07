#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
bool greaterThan2(int x) {
    if (x>2) {
        return true;
    }
    return false;
}

int main() {
    // min and max can compare any type which have <, > relations
    cout << min(2,3) << " " << max(2,4) << endl;
    // sort
    vector<int> v {2, 1, 4, 3, 0};
    sort(begin(v), end(v)); // algorithm recieves iterators
    // count how many times an element icluded in the container
    cout << count(begin(v), end(v), 2) << endl;
    // count_if - applying bolean mask to a container
    int n = 2;
    cout << count_if(begin(v), end(v), greaterThan2) << endl; // number of elements greater than 2
    cout << count_if(begin(v), end(v), [n](int x){x>n ? return true : return false;}) << endl;
    return 0;
}   