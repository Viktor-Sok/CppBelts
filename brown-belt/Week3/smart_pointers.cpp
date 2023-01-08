#include <memory>
#include <iostream>
#include <utility>
using namespace std;

struct Dog {
    Dog() {cout << "Dog has come in! :)" << endl;}
    void bark() {cout << "Dog is barcking..." << endl;}
    ~Dog() {cout << "Dog has went out!" << endl;}

};

void annoyDog(Dog* pd) {
    if(pd)
        pd -> bark();
    else
        cout << "There is no dog present! :(" << endl;
} 

int main() {
    // auto upd = unique_ptr<Dog>(new Dog);
    auto upd = make_unique<Dog>(); // better way to create unique pointer (method temlate: make_unique<T>)
    annoyDog(upd.get()); // get() returns from unique_pointer a raw pointer which is requared as the argument got the annoyDog function
    // auto upd1 = upd // won't work becouse for unique_ptr copy_constructor() = delete
    auto upd1 = move(upd); // we can move unique_ptr
    annoyDog(upd.get()); // now upd is empty  
    return 0;
}