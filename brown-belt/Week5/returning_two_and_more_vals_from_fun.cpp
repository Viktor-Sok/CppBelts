#include <iostream>
#include <string>
#include <array>
#include <tuple>
#include <utility>
#include <memory>

using namespace std;

using Pair = pair<int, string>;
using Tuple = tuple<int, char, string>;

struct Data {
    // this structure may occupy a lot of memory on the stack
    // we don't want it to be returned from a function
    // because it will requare copying, move semantics doesn't work well with a lot of data on the stack
    // solution is to return a poiter to this structure
    array<int, 5> arr; // array stores its values on the stack
    string s;
};

unique_ptr<Data> makeObjWithDataOnStack() {
    // creates pointer to the object which has a lot of data on stack
    // and returns pointer, necouse RVO won't work well for such object
    //const auto data_ptr = make_unique<Data>(Data {{1, 2, 3, 4, 5}, "name"});
    auto data_ptr = make_unique<Data>();
    data_ptr -> arr = {1, 2, 3, 4, 5};
    data_ptr -> s = "Word";
    return data_ptr;
}


struct Ret {
    // structure for returning data from a function
    int i;
    string s;
};

Pair numberName() {
    int i = 3;
    string name = "Three";
    // It's important to move, becouse RVO and copy elision doesn't work when returning multiple objects
    return {i, move(name)}; //also possible make_pair(move(i), move(name)) 
}

Tuple charNumberANSII() {
    char ch = 'h';
    string s = to_string(int(ch));
    return {int(ch), ch, move(s)}; // make_tuple(move(), move(), move());
}

Ret numberName1() {
    return {3, move("three")}; 
}


ostream& operator <<(ostream& os, array<int, 5> arr) {
    for (const auto& e : arr)
        os << e << " ";
    return os;
}

int main() {
    // return pair
    auto [i, name] = numberName();
    cout << "Pair returned: " << i << " " << name << endl;
    // return tuple into existing vars
    int k; char ch; string s;
    tie(k, ch, s) = charNumberANSII();
    cout << "Tuple returned: " << k << " " << ch << " " << s << endl;
    // return structure, auto [a, b] and tie(a, b) also work for structures
    auto [m, word] = numberName1();
    cout << "Struct returned: " << m << " " << word <<  endl;
    // returning object with lots of data on the stack
    auto [arr, word1] = *makeObjWithDataOnStack(); // dereferencing smart pointer
    cout << "Unique pointer to the object returned: " << arr << " " << word1 << endl;
    return 0;
}