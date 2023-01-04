#include <iostream>
#include <vector>
#include <numeric> // accumulate function
#include <future> // to use async function

using namespace std;

int sumOfVectors(const vector<int>& v1, const vector<int>& v2) {
    future<int> res1 = async([&v1] {return accumulate(begin(v1), end(v1), 0);}); // exetutes in the other thread, &v1 get by reference
    int res2 =  accumulate(begin(v2), end(v2), 0);
    return res1.get() + res2;
}
int main() {
    cout << sumOfVectors({1, 2, 3, 4}, {1, 1, 1}); // expected answer is 13
    return 0;
}