#include <iostream>
#include <optional>

using namespace std;
// optional is used instead of using boolean flags for returning values, e.g. std::pair<T, bool>
// useful for creating cache for storing frequent user's input for a database
optional<string> create(bool b) {
    if(b)
        return "Godzilla";
    return {}; // empty constructor for optional
}
int main() {
    bool b = true;
    if(auto str = create(b)) {
        cout << "Successfully created: " << *str << endl;
        str.reset();
        cout << "optional<string> after reset: " << *str << endl;
    } else {
        cout << str.value_or("creation failed") << endl;
    }
     
    return 0;
}