#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int main {
    string s = "jcdncjef";
    // ranged based loop
    for (char c : s) {
        cout << c << ",";
    }
    vector<int> nums = {1, 2, 3, 5, 4, 2};
    // counts number of 2 in the vector
    int quantity = count(begin(nums), end(nums), 2);
    // sorting
    sort(begin(nums), end(nums));
    return 0;
}