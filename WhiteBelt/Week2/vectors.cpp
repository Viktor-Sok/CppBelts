#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<string>& const v) {
    // printing by the elemets reference 'string& const'
    // allows to prevent copying elements into local varibale
    // if we used string s instead
    for (string& const s : v)
        // returns size of the vector
        cout << v.size() << endl; 
        cout << s << ",";
}   
int main() {
    int n;
    cin >> n;
    // defines number of the elements in the vector constructor
    vector<string> v(n);
    printVector(v);
    // use vector as simple array
    vector<int> nums = {1, 2, 3};
    cout << nums[0] << nums[1] << nums[2];
    // initializing vector of 28 elemets with zeros
    vector<int> nums1(28, 0); 
    // resize and keep previous values
    nums1.resize(4);
    // reuse vector for a different data
    nums1.assign(10,0); //increases nums1 up to 10 elements and assigns them to zero
    // clear vector
    nums1.clear();
    return 0;
}