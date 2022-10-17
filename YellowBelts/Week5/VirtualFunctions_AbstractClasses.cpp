#include <iostream>
#include <string>

using namespace std;


// Animal abstarction (Animal: Cat, Dog, ...; The same Actions: Eat, Sleep ;  Different actions: Meow, Bark; Different fields: species)
class Animal {
protected: // protected field can be accessed from publicly inhereted child classes but not in the main program
    string species = "Animal";
public:
// =0 means Animal is the abstract class (its instance cannot be created)
// and we requared to implement makeSound in every child class
    virtual void makeSound() const = 0;  // interface for child classes, implementation inside them
};

class Cat : public Animal {
public:
    Cat() {
        species = "Cat";
    }
    // override is neccesary in case we rename/delete virtual function in the Parent class,
    // becouse in that case compilator will warn us
    void makeSound() const override { // const specifier means it can't change class's fields
        cout << "Meow!" << endl;
    }
};
class Dog : public Animal {
public:
    Dog() {
        species = "Dog";
    }
    void makeSound() const override { // const specifier means it can't change class's fields
        cout << "Bark!" << endl;
    }
};

// Function which will accept both Cat/Dog.
// So, in some sense inherirance let us achive the similiar functionality as templates
// Inherited classes can be passed into function as parent class type
void voice(const Animal& a) {
    // object of class Animal MUST BE passed by reference, othervies we
    // our code wan't be working properly, becouse if we pass by value
    // compilator would think that we want to convert class Dog/Cat into Animal
    // and we will loose all the information (fields, methods) from the child classes
    a.makeSound();
}

int main() {
    
    Cat c;
    Dog d;
    voice(c); // the same function voice() will give a different effect
    voice(d); //  becouse c and d diffferent childs of the parent class animal
    return 0;
}