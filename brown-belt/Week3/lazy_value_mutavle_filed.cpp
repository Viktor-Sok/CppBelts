#include <iostream>
#include <map>
#include <functional>
#include <optional>
#include <utility>

using namespace std;

template <typename T>
class LazyValue {
    /*Value will be calculated  as needed*/
    std::function<T()> init_; // function<> function wrapper, to pass function as argument to a function
    // mutable means that const methods can mpdify this field
    mutable optional<T> value; // optional is used to avoid usage of some boolean flags in if statement in the method get
public:

    explicit LazyValue(function<T()> init) : init_(move(init)) {} // move let us avoid copying of a function

    const T& Get() const {  // returns const reference to value in the wrapper optional and method is constant itself
        if(!value) // checks if value is still not initialized, optional let us avoid using bolean flag here
            value = init_();
        return *value;  // unpacking optional wrapper
    }

};

map<string, int> lazyFun() {
    /*Function to be passed as argument in the LazyValue class constructor*/
    return {{"one", 1}, {"two", 2}, {"three", 3}};
}

int main() {
    LazyValue<map<string, int>> lazyVal(lazyFun); // function lazyFun passed as argumant
    for (const auto& e : lazyVal.Get()) { // perfoming lazy evaluation by Get() function
        cout << e.first << ": " << e.second << endl;
    }
    return 0;
}