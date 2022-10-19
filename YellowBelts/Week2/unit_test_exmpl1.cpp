#include <iostream>
#include <set>
#include <string>
#include <map>
using namespace std;

void addSynonyms (map<string,set<string>>& s, const string& w1, const string& w2) {
    s[w1].insert(w2);
    s[w2].insert(w1);
}

size_t countSynonyms(map<string,set<string>>& s, const string& w) {
    return s[w].size();
}

string checkSynonym(map<string,set<string>>& s, const string& w1, const string& w2) {
    if (s[w1].count(w2) == 1) {
        return "YES";
    } else {
        return "NO";
    }
}
int main() {
    int q;
    cin >> q;
    map<string,set<string>> synonyms;
    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "ADD") {
            string w1, w2;
            cin >> w1 >> w2;
            addSynonyms(synonyms, w1, w2);
            //synonyms[w1].insert(w2);
            //synonyms[w2].insert(w1);
        } else if (operation_code == "COUNT") {
            string word;
            cin >> word;
            cout << countSynonyms(synonyms, word) << endl;
        } else if (operation_code == "CHECK") {
            string w1, w2;
            cin >> w1 >> w2;
            cout << checkSynonym(synonyms, w1, w2) << endl;   
        }
    }
    return 0;
}