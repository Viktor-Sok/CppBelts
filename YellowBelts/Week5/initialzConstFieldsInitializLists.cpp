#include <iostream>
#include <string>

using namespace std;

class Tree {
public:
    const string type;
    // initializer list let us initialize const variable
    Tree(const string& t = "animal") : type(t) {
        // here is not possible to initialize 
        // const type, becouse at this poit object already created (inside the brackets)
    } 
};

class Pine : public Tree {
public:
    // calling constructor of the parent class using initializer list
    Pine() : Tree("pine") {}
};

int main() {
    Pine p;
    cout << p.type << endl;
    return 0;
}