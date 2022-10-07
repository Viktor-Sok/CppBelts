#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main {
    vector<int> v {1, 2, 3};
    // let's increase all the elements by 1
    //without reference & code won't work, becouse ++i will be applied to the copy 
    //of the element and not with element itself
    for (auto& i : v) {
        ++i;
    }
    
    return 0;
}