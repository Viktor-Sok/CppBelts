#include <iostream>
#include <tuple>
#include <assert.h>
#include <utility> // contains Pair data stracture

using namespace std;

tuple<int, string> myFun(int n, string s) {
    return make_tuple(n, s);
}

int main() {
    // will wrok in C++17, automativally inferred template parameters
    tuple t(23, "C++", true);
    //tuple<int, string, bool> t1(23, "C++", true);
    // auto t = tie(23, "C++", true); won't work, because tie creates references to variables, but 23 is not a variable somethere in emory
    auto t1 = make_tuple(23, "C++", true);
    assert(t == t1);
    // accesing the element of a tuple
    cout << get<1>(t1) << endl;
    // Pair for two elememts, more convinient access to the elemnts than tuple
    pair<int, string> p(23, "C++");
    auto p1 = make_pair(23, "C++");
    // get tuple from a function
    // tie(var1, var2, var3) = myFun();
    // since C++17- structure bindings
    auto [var1, var2] = myFun(3, "B");
    cout << var1 << " " << var2 << endl;
    return 0;
}