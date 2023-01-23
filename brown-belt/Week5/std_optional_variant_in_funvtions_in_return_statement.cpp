#include <iostream>
#include <string>
#include <vector>
#include <optional> // e.g. tu either return a value or en empty entety (let us avoid using additional bool flag)
#include <algorithm> 
#include <variant> // let us return different types from a function
#include <exception>

using namespace std;

namespace Mine {
/* All my functions defined in Mine namespace*/
optional<char> find(const vector<char>& v, char c) {
    auto it = ::find(v.begin(), v.end(), c); // global namespace used in case if we have the same fun inside Mine
    if(it != end(v))
        return *it;
    else 
        return nullopt; // you can use just {} 
}

enum class Animal {
    Cat = 1, Dog, Parrot
};

variant<int, Animal, string> numberAnimalWord(int i) {
    // This function is able to return different data types
    switch(i) {
        case 1: 
            return static_cast<Animal>(i);
        case 2: 
            return static_cast<Animal>(i);
        case 3: 
            return static_cast<Animal>(i);
        case 4:
            return i;
        default:
            return "No matches";
    }
}
};

int main() {
    // Using std::optional to avoid using bool flag
    vector<char> v = {'a', 'b', 'c'};
    auto res = Mine::find(v, 'a');
    cout << "Succecful search: " << res.value() << endl;

    // Error handling with std::optional
    auto res1 = Mine::find(v, 'm');
    try {
    cout << "Succecful search: " << res1.value() << endl;;  // rases std::bad_optional_access
    }
    catch(bad_optional_access& e) {
        cout << "Unsuccesful search: " << e.what() << endl;
    }

    // using std::veriant to return different types from a fucntion
    auto res2 = Mine::numberAnimalWord(8);
    if(holds_alternative<int>(res2))
        cout << get<int>(res2) << endl;
    else if (holds_alternative<Mine::Animal>(res2)) // holds_alternative checks whether res2 stores value of Animal type
        cout << "Output is enum, it's hard to print ..." << endl;
    else 
        cout << get<string>(res2) << endl; // get let us access value stored in the wrapper std::variant

    return 0;
}