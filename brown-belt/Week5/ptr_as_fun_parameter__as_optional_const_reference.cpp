#include <iostream>
#include <string>

using namespace std;

void Print(istream& is, const string* ps = nullptr) {
    /*ps acts as optional const reference for some heavy objects*/
    string s;
    is >> s;
    if(ps)
        cout << s + *ps << endl;
    else
        cout << s;
    return;
}
int main() {
    string a = ".format";
    Print(cin, &a);
    return 0;
}