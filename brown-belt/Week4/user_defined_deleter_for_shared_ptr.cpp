#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Data {
public:
    Data(string name) : name_(name) {}
    ~Data() {cout << "Data object was deleted\n";}
    string name_;
};

int main() {
    // default shared_ptr deleter behaivour
    {
    auto sp1 = make_shared<Data>("Cat");
    cout << "Shared_ptr will delete the object when out of scope" << endl;
    }
    {
    Data* pd = new Data("Dog");
    // Creating shared_ptr from raw pointer with user defined deleter
    auto sp2 = shared_ptr<Data>(pd, [](Data*){cout << "User defined deleter for shared_ptr" << endl;});
    }
    return 0;
}