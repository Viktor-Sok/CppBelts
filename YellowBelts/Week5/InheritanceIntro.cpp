#include <iostream>
#include <string>

using namespace std;

// Fruit abstraction (Fruits: Apple, Orange, ... Different fields: health, type))
struct Fruit {
    // this field will be changed by child classes
    // Parent class acts as  a container for the fields of child classes 
    int health = 0;
    string type = "fruit";
};

struct Apple : public Fruit { // public inheretance will keep public/protected fields of the parent as public/protected
    Apple() {
        // constructor changes the field of public member of the parent class Fruit
        health = 10;
        type = "apple";
    };
};
//
struct  Orange : public Fruit {
    Orange() {
        health = 5;
        type = "orange";
    };
};

// Animal abstarction (Animal: Cat, Dog, ...; The same Actions: Eat, Sleep ;  Different actions: Meow, Bark; Different fields: species)
class Animal {
protected: // protected field can be accessed from publicly inhereted child classes but not in the main program
    string species = "Animal";
public:
    void eat(const Fruit& f) {
        cout << species << " eats " << f.type << ". " << f.health << "hp." << endl;
    }
};

class Cat : public Animal {
public:
    Cat() {
        species = "Cat";
    }
    void Meow() const { // const specifier means it can't change class's fields
        cout << "Meow!" << endl;
    }
};
class Dog : public Animal {
public:
    Dog() {
        species = "Dog";
    }
    void Bark() const { // const specifier means it can't change class's fields
        cout << "Bark!" << endl;
    }
};

// Function which will accept both Cat/Dog or Apple/Orange as Animal/Fruit.
// So, in some sense inherirance let us achive the similiar functionality as templates
// Inherited classes can be passed into function as parent class type
void doMeal(Animal& a, Fruit& f) {
    a.eat(f);
}

int main() {
    Apple a;
    Orange o;
    Cat c;
    Dog d;
    doMeal(c, a);
    doMeal(d, o);
    return 0;
}