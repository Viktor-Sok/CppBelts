#include <iostream>
#include <utility> // pair
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// forward declaration
template<typename T1, typename T2>
ostream& operator <<(ostream& , const pair<T1, T2>& );

template <typename Collection>
string printCollection(const Collection& c, char delim) {
    // prints out  a container with specified delimiter
    stringstream ss;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            ss << delim;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}
template <typename T1, typename T2>
ostream& operator <<(ostream& o_ss, const pair<T1, T2>& p) {
    // operator << overloading for pair is requared to print map elements
    o_ss << '(' << p.first << ',' << p.second << ')';
    return o_ss;
}

template <typename T>
ostream& operator <<(ostream& o_ss, const vector<T>& v) {
    // overloading << for putting vector into output stream
    return o_ss << '[' << printCollection(v, ',') << ']';
    
}

template <typename T1, typename T2>
ostream& operator <<(ostream& o_ss, const map<T1, T2>& m) {
    // overloading << for putting vector into output stream
    o_ss << '{' << printCollection(m, ',') << '}';
    return o_ss;
}

int main() {
    vector<int> v = {1, 2, 3};
    map<string, int> m {{"first", 1}, {"second", 2}};
    auto p = make_pair(23, "C++");
    cout << v << "\n" << m << "\n" << p << endl;




    return 0;
}