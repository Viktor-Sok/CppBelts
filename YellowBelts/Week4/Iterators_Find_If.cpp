#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<string> langs = {"Python", "C++", "Java", "C#"};
    // find_if is standard algorithm recieves begin and end iterator and returns pointer if for the element for which condition is true
    // find_if(cont.begin(), cont.end(), <condition>)
    auto res = find_if(langs.begin(), langs.end(), [](const string& lang) {return lang[0] == 'C';});
    // *res returns reference to an element in the container
    // *res is non-constant reference so we can modify container in-place
    string& refString = *res;
    cout <<  refString << endl;
    // modifying element of the container in-place
    *res = "D++";
    cout <<  refString << endl;
    // it's possible to checker wheter the element was found or not
    // cont.end() points right after the last element in container
    // Moving iterator (incrementing)
    cout << *(++res) << endl;
    auto res1 = find_if(langs.begin(), langs.end(), [](const string& lang) {return lang[0] == 'M';});
    if (res1 == langs.end()) {
        cout << "not found" << endl;
    } else {
        cout<<"found"<< endl;
    }
    return 0;
}