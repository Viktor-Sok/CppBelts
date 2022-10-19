#include <iostream>
#include <set>
#include <string>
#include <map>
using namespace std;

typedef map<string,set<int>> Syn; // C-style typedef
using Syn1 = map<string,set<int>>; // C++ style, better for templates

int main() {
    Syn1 s = {{"one", set({1, -1})},{"two", set<int>({2, -2})}};

    return 0;
}