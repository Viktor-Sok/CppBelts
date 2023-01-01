#include <string>
#include <string_view>
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>                                                                                

using namespace std;

vector<string_view> split_into_words3(string_view str) { 
    // using string view
    //string_view str = s; // copy constructor from string to string_view
    vector<string_view> res;
    //size_t pos = 0;
    //const size_t end = str.npos;
    size_t found;
    while(found != string::npos) {
        //size_t space = str.find(' ', pos);
        //res.push_back(space == end ? str.substr(pos) : str.substr(pos, space - pos));
        //if (space == end)
        //    break;
        //else
        //    pos = space + 1;
        found = str.find(' ');
        res.push_back(str.substr(0, found));
        str.remove_prefix(found + 1);
    }
    return res; 
}
vector<string> split_into_words2(const string& s) {
    // using algorithms from STL
    vector<string> res;
    auto begin = s.begin();
    const auto end = s.end();
    while(true) {
        auto it = find(begin, end, ' ');
        res.push_back(string(begin, it)); //string(it1, it2) string constructor from two iterators
        if (it == end) {
            break;
        } else {
            begin = it + 1;
        }
    }
    return res;
}

vector<string> split_into_words1(const string& s) {
    // using string methods
    vector<string> res;
    size_t found = s.find_first_of(" ");
    size_t temp = 0;
    while (found != string::npos) {
        res.push_back(s.substr(temp, found - temp));
        temp = found;
        found = s.find_first_of(" ", temp + 1);
    }
    res.push_back(s.substr(temp, s.size()));
    return res;
    
}
int main () {
    string s = "El hombre con el oso   ";
    auto words = split_into_words3(s);
    for (const auto& e : words) {
        cout << e << "\n";
    }
    return 0;
}