#include <iostream>
#include <string>
#include <utility>

using namespace std;

/*
User implementation of std::optional from standard library to show basic organization of a class
Also class demostrates zero/three/five rule in C++about copy/move constructors and correspobding copy/move assingment operator
*/

struct Student {
    string Name;
    double Rating;
    Student() = default;
    // eplicit requares explicetly write initialization like Student(), and not just {..., ...}
    explicit Student(string name, double rating) : Name(name), Rating(rating) {}
    void Print() const {
        cout << Name << " " << Rating << "\n";
    }

    // Copy constructor
    // For simple type as Student default copy constructor will make do
    // but when deep copy (data in the heap) requared yuo have it write explecetly
    
    Student(const Student& s) {
        this -> Name = s.Name;
        this -> Rating = s.Rating;
    }
    

   // Move constructor
   // then we call <Student Student_object1(std::move(Student_object))> 
   // this constructor will be called
   Student(Student&& s) {
        this -> Name = move(s.Name);
        this -> Rating = move(s.Rating);
        s.Name = ""; s.Rating = 0;
   }
};

struct BadOptionalAccess{
    // User defined error, will be used in class Optional
    char error[500] =  "Optional is empty (use error handling to resolve it)";
    const char* what() const{
        return error;
    }   
}; 

template <typename T>
class Optional {
private:
    // alignas for correct memory alingment
    // if we use T t; instead, then every time we call default constructor object of type t will be constructed
    // but here we only reserve the memory fot it: memory allocation are separate from object T creation
    alignas(T) unsigned char data[sizeof(T)]; // this is buffer for the object T
    T* t; // pointer that points at the beginnig ?CRUTCH that NEEDS TO BE E<IOMINATED?
    bool defined = false; // flag showing whether object is stored

public:
    bool HasValue() const;
    T GetValue() const;

    Optional() = default; // DEFAULT CONSTRUCTOR, if we don't define it explicetly then ther will be no default construct becouse we have user defined constr below
    Optional(const T& elem); // ORDINARY CONSTRUCTOR Optional object from T by copying
    Optional(T&& elem); // ORDINARY CONSTRUCTOR for TEMRORARY objects construct Optional from T by moving T 
    Optional(const Optional<T>& other) = default; // COPY CONSTRUCTOR 
    Optional(Optional<T>&& other); // MOVE CONSTRUCTOR 

    /*
    // when COPY INITIALIZATION and MOVE INITIALIZATION operators not defined
    // ORDINARY CONSTRUCTOR and ORDINARY CONSTRUCTOR for TEMPRORARY objects will be callled
    Optional& operator=(const T& elem); // COPY INITIALIZATION OPERATOR: constructing object Optional from T by assignment (copying of T will happen )
    Optional& operator=(T&& elem); // MOVE INITIALIZATION OPERATOR Optional through assingment by moving from T to the object data field 

    // we can delete default assingment copt and move operators which will prevent object from copying and moving
    // we can assingn them to default which is equvalent to just non-writing them below
    Optional& operator=(const Optional& other) = default; // COPY ASSINGMENT operator
    Optional& operator=(Optional&& other) = default; // MOVE ASSINGMENT OPERATOR
    */
    Optional<T>& operator=(const T& elem) { // by using this we can initialize object later created by default constructor with null values
        t = new (data) T(elem);
        defined = true;       
        return *this;
    }
    Optional<T>& operator=(const Optional<T>& other) = default; // COPY ASSINGMENT operator

    T& operator*(); // dereferencing  Optional object
    const T& operator*() const; // ? needed to handle possible const T values?
};

template <typename T>
// CONSTRUCTOR for Lvalue parameter
Optional<T>::Optional(const T& elem) {
    t = new (data) T(elem);
    //memcpy(data, T, sizeof(T)); // copying will happen, copy initialization should work for type T
    defined = true; 
}

template <typename T>
// CONSTRUCTOR for Rvalue parameter
Optional<T>::Optional(T&& elem) {
    t = new (data) T(move(elem));
    defined = true;
}

template <typename T1>
// MOVE CONSTRUCTOR
Optional<T1>::Optional(Optional<T1>&& other) : Optional(other.GetValue()) {
    other.t = nullptr;
    other.defined = false;
}

template <typename T>
bool Optional<T>::HasValue() const {
    return defined ? true : false;
}

template <typename T>
T Optional<T>::GetValue() const{
    if (defined)    
        return *t;
    throw BadOptionalAccess {};
}

int main() {
    string s = "Name";

    // Checking correctness via throw and try-catch
    cout << ">>>Checking correctness via throw and try-catch:" << "\n";
    Optional<string> o; //   DIRECT DEFAULT INITIALIZATION (default constructor is called)
    try {
        cout << o.GetValue() << "\n";
    } catch (const BadOptionalAccess & e) {
        cout << e.what() << endl;
    }

    // Checking correctnes via HasValue bool method
    cout << ">>>Checking correctnes via HasValue bool method:" << "\n";
    Optional<string> o1 = s; // COPY INITIALIZATION (copy initialization operator= is called)
    if (o1.HasValue()) {
        cout << o1.GetValue() << "\n";
    }
    
    //  user defined object Student
    cout << ">>>User defined object Student initialization:" << "\n";
    Student st {"Petr", 4.0};
    // both ways of initilaization (construction) from st work
    Optional<Student> o2(st); // DIRECT INITIALZIATION
    Optional<Student> o3 = st; // COPY INITIALIZATION (copy initialization operator= is called)
    if (o2.HasValue()) {
        o2.GetValue().Print();
    }

    // initialization (construction) from temproray object (rvalue)
    cout << ">>>Initialization (construction) from temproray object (rvalue):" << "\n";
    Optional<Student> o4(Student {"Dima", 5.0}); // CONSTRUCTOR FOR TEMPRORARY OBJECTS will be called Optional<Student>(&& elem)
    //Optional<Student> o4({"Dima", 5.0}); // DOESN'T work becouse Student have EXPLICIT constructor
    Optional<Student> o5 = Student("Viktor", 1.0); //  MOVE INITIALIZATION operator will be called
    if (o4.HasValue()) {
        o4.GetValue().Print();
    }

    // initialization (construction) from temproray bjects using std::move
    cout << ">>>Initialization (construction) from temproray bjects using std::move:" << "\n";
    Student st1("Oleg", 3.2);
    Student st11("Oleg1", 3.21);
    Optional<Student> o6(move(st1)); // CONSTRUCTOR for TEMRORARY objects will be called
    Optional<Student> o7 = move(st11); // MOVE INITIALIZATION OPERATOR  will be called
    st1.Print(); // the fields of st1 were zeroed after moving by invoking Student(Student&& s) move constructor 
    st11.Print(); // st11 were zeroed by the same reason
    if (o6.HasValue()) {
        o6.GetValue().Print();
    }

    // constructing object by copying from another object
    cout << ">>>Constructing object by copying from another object:" << "\n";
    Optional<Student> o8(o6); // COPY CONSTRUCTOR is called
    Optional<Student> o9 = o7; // COPY ASSINGMENT OPERATOR is called
    if (o8.HasValue()) {
            o8.GetValue().Print();
        } 
    if (o9.HasValue()) {
        o9.GetValue().Print();
    }     

    // constructing object by moving from another object
    cout << ">>>Constructing object by moving from another object:" << "\n";
     Optional<Student> o10(move(o8)); // MOVE CONSTRUCTOR is called
    Optional<Student> o11 = move(o9); // MOVE ASSINGMENT OPERATOR is called
    if (!o8.HasValue() && !o9.HasValue()) {
        cout << "Objects o8 and 09 were cleared when moving" << "\n";
    }
    if (o10.HasValue()) {
            o10.GetValue().Print();
        } 
    if (o11.HasValue()) {
        o11.GetValue().Print();
    }  

    // using default constructor for later initialization
    cout << "Using default constructor for later initialization:" << "\n";
    Optional<Student> o12, o13;
    o12 = Optional<Student>(Student("Pfff", 4.0)); // COPY ASSINGMENT OPERATOR will be called
    o12.GetValue().Print();
    o13 = Student("Pfff1", 4.1); // COPY INITIALIZATION operator will be called
    o13.GetValue().Print();
    return 0;
}

