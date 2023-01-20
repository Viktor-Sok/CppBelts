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
    // auto upd = shared_ptr<Dog>(new Dog);
    auto upd = make_shared<Dog>(); // better way to create shared pointer (method temlate: make_shared<T>)
    annoyDog(upd.get()); // get() returns from shared_pointer a raw pointer which is requared as the argument got the annoyDog function
    auto upd1 = upd; // we can make a copy oh shared ptr, so two pointers point to the same object 
    annoyDog(upd.get()); // now upd is empty  
    return 0;
}