#include <iostream>
#include <utility>
#include <string>
#include <exception>

using namespace std;
/*
This code demonstrates how to tuckle exceptions happening in Test struct which is used in Vector class
We have to write try-catch blocks in Vector(size_t n), in Vector(const Vector& other) and in Reserve(size_t n)
which leads to a lot of code repetition so we have to come up with something more smart
e.g. every class should be responsibale for onlly one resource RAII
in our case Vector has RAW MEMORY (operetor new/ operator delete) and OBJECTS created in this memory (new (buf) T()/ ~T())
*/

template <typename T>
class Vector {
private:
    T* data; // pointer to data in the heap
    size_t sz; // number of occupied memory cells
    size_t cp; // total capacity of the reserved cells, if the exeeded the memory reallocation needed

    static T* Allocate(size_t n) {
        // raw memory allocation
        return static_cast<T*>(operator new(n * sizeof(T)));
    }

    static void Deallocate(T* buf) {
        operator delete(buf);
    }

    static void Construct(void* buf) {
        // constructing object in the preveously allocated memory
        new (buf) T();
    }
    static void Construct(void* buf, const T& elem) {
        new (buf) T(elem);
    }
    static void Construct(void* buf, T&& elem) {
        new (buf) T(move(elem));
    }
    static void Destroy(T* buf) {
        // calls destructor for T object
        buf -> ~T(); 
    }
public:
    size_t Size() const {
        return sz;
    }

    size_t Capacity() const {
        return cp;
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    T& operator[](size_t i) {
        return data[i];
    }

    explicit Vector(size_t n = 0);
    Vector(const Vector& other);
    void Reserve(size_t n);
    ~Vector();

    Vector(Vector&& other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    
    void Resize(size_t n);
    void PushBack(const T& elem);
    void PushBack(T&& elem);
    void PopBack();
 
    T& EmplaceBack(...);   

    T* begin() {
        return data;
    }
    
    T* end() {
        return data + sz;
    }
    
};

template<typename T>
Vector<T>::Vector(size_t n) {
    data = Allocate(n); // if exception happens in Object T, then Vector is not considered created and Deallocate won't be called as a result memory leaks
    size_t created = 0; // counts the number of succesfully constructed objects
    try { // we don't have to include Allocate(n) iside try block becoase in the case of exception Allocate(n) will rewind the stack and destructors will be properly called
    for (;created < n; ++created)
        Construct(data + i); // some of the T object might be created and if exception occured no destructors for T objects will be called 
    } catch (...) {
        for (size_t i = 0; i < created; ++i)
            Destroy(data + i);
        Deallocate(data);
        throw; // passsing the exception further 
    }
    sz = cp = n;
}
template<typename T>
Vector<T>::Vector(const Vector& other) {
    sz = other.sz;
    data = Allocate(sz);
    for (size_t i = 0; i < sz; ++i)
        Construct(data + i, other[i]);
}
template<typename T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < sz; ++i)
        Destroy(data + i);
    Deallocate(data);
}
template <typename T>
void Vector<T>::Reserve(size_t n) {
    // Let us encrease capacity of an existing vector
    if (cp < n) { 
        auto data1 = Allocate(n); // allocation of the new chunk of the memory
        for (size_t i = 0; i < sz; ++i) {
            Construct(data1 + i, move(data[i])); // Construct object T in new memory by copy constructor of T
            Destroy(data + i); // Destroy T object in the old chunk of memory
        }
        Deallocate(data); // return old memory to the OS
        data = data1; // reassing field data to the newly created chunk of memory
        cp = n; // actualize capacity
    }
}


struct Student {
    string Name;
    double Rating;
    Student() = default;
    // eplicit requares explicetly write initialization like Student(), and not just {..., ...}
    explicit Student(string name, double rating) : Name(name), Rating(rating) {}
    void Print() const {
        cout << Name << " " << Rating << "\n";
    }
    Student(const Student& s) {
        this -> Name = s.Name;
        this -> Rating = s.Rating;
    }
    Student(Student&& s) {
        this -> Name = move(s.Name);
        this -> Rating = move(s.Rating);
        s.Name = ""; s.Rating = 0;
   }
};

struct Test {
    // User defined type where exceptions might occur
    // So we need to handle those exceptions in the class that uses Test struct i.e. in Vector class
    inline static size_t numObj = 0;
    Test() {
        ++numObj;
        if (numObj > 5)
            throw runtime_error("Too many objects!");
    }
    Test(const Test&) {
        ++numObj;
        if (numObj > 5)
            throw runtime_error("Too many objects!");

    }
    ~Test() {
        --numObj;
    }
}; 

int main() {
    Vector<Test> v(2);
    cout << "Size: " << v.Size() << " Capacity: " << v.Capacity() << endl;
    v.Reserve(4);
    cout << "Capacity extended to 4 by Reserve: " << "\n";
    cout << "New Size: " << v.Size() << " New Capacity: " << v.Capacity() << endl;
    try {
    Vector<Test> v(6); 
    // if error occurs in the Test struct we have to tackle it in the Vector constructur
    // becouse it can lead to memory leaks
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "Undefinied error occured!" << endl;
    }

    return  0;
}