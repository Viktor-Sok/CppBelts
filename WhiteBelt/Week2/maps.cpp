#include <iostream>
#include <map>
#include <string>
using namespace std;

void printMap(map<int,string>& const m) {
    // auto will be actually sid::pair<const int, string>
    for (auto& const item : m)
        cout << item.first << ": " << item.second << endl;   
    // C++17
    for (auto& const [key, val] : m) {
        cout << key << ": " << value << endl; 
    }
}
int main() {
    // keys : int, values: string
    // keys are automatically sorted in map
    map<int,string> events;
    events[1950] = "Stroustrup birthfay";
    events[1941] = "Dennis Ritchie's birth";
    printMap(events);
    // delete element by key
    events.erase(1941);
    // initializing maps
    map<string, int> m = {{"one", 1},{"two", 2},{"three", 3}};
    // any attemt toa acces key that doesn't exist will automatically create item
    m["four"]; // now m is gonna have key four
    return 0;
}
