#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
typedef vector<int> arr; // type defenition 


template <typename Func>
arr map(Func func, arr &vec) {
    // recieves function as template parameter
    // applies func to iterable
    arr res;
    for (auto const &i : vec) {
        res.push_back(func(i));
    }
    return res;
}

void printVec(arr const & vec) {
    for (auto const &i : vec) {
        cout << i << " ";
    }
}

int power(int base) {
    return pow(base, 2);
}

int main() {
    arr vec = {1, 2, 3};
    printVec(map(power, vec));
    return 0;
}