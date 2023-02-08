#include <iostream>
#include <utility>
#include <string>
#include <exception>
#include <memory> // std::uninitialized_copy_n() can be used in Vector Copy Constructor istead of excplicit error handling, try-catch statement is already implemented inside

using namespace std;
/*
Nothrow (or nofail) exception guarantee — the function never throws exceptions. Nothrow (errors are reported by other means or concealed) is expected of destructors and other functions that may be called during stack unwinding. The destructors are noexcept by default. (since C++11) Nofail (the function always succeeds) is expected of swaps, move constructors, and other functions used by those that provide strong exception guarantee.
Strong exception guarantee — If the function throws an exception, the state of the program is rolled back to the state just before the function call. (for example, std::vector::push_back)
Basic exception guarantee — If the function throws an exception, the program is in a valid state. No resources are leaked, and all objects' invariants are intact.
No exception guarantee — If the function throws an exception, the program may not be in a valid state: resource leaks, memory corruption, or other invariant-destroying errors may have occurred.
*/

template <typename T>
class RawMemory {
public:
    // this class has overloaded + and [] operators, so it would work similary to a pointer
    T* buf = nullptr; // pointer to the raw memory for type T
    size_t cp = 0; // total capacity of the reserved cells, if the exeeded the memory reallocation needed

    static T* Allocate(size_t n) {
        // raw memory allocation
        return static_cast<T*>(operator new(n * sizeof(T)));
    }

    static void Deallocate(T* buf) {
        operator delete(buf);
    }

    RawMemory() = default;    
    RawMemory(size_t n) : buf(Allocate(n)), cp(n) {}
    RawMemory(const RawMemory&) = delete; // It makes no sense to copy empty memory
    RawMemory& operator=(const RawMemory&) = delete; //there is no sense in copying empty memory as well
    RawMemory& operator=(RawMemory&& other) noexcept {
        Swap(other);
        return *this;
    }
    RawMemory(RawMemory&& other) {
        Swap(other);
    }
    void Swap(RawMemory& other) noexcept    {   
        swap(buf, other.buf);
        swap(cp, other.cp);
    }

    ~RawMemory() {
        Deallocate(buf);
    }

    // const version fro + and [] operators is requared to allow read/write access fro non-const objects T and 
    // only read access fr const T objects
    T* operator+(size_t i) {
        return buf + i;
    }
    const T* operator+(size_t i) const {
        return buf + i;
    }

    T& operator[](size_t i) {
        return buf[i];
    }
    const T& operator[](size_t i) const {
        return buf[i];
    }


};

template <typename T>
class Vector {
private:
    RawMemory<T> data; 
    size_t sz = 0; // number of occupied memory cells

    
public:
    size_t Size() const {
        return sz;
    }

    size_t Capacity() const {
        return data.cp;
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    T& operator[](size_t i) {
        return data[i];
    }

    Vector() = default;
    explicit Vector(size_t n);
    Vector(const Vector& other);
    void Reserve(size_t n);
    ~Vector();

    Vector(Vector&& other) noexcept;
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other) noexcept;
    
    void Resize(size_t n);
    void PushBack(const T& elem); // copy pushback
    void PushBack(T&& elem); // move pushback

    //template <typename ... Args> void EmplaceBack(const Args& ... args);
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
Vector<T>::Vector(size_t n) : data(n) { // memory allocation happens in list initialization
    sz = n;
    uninitialized_value_construct_n(data.buf, n);
}
template<typename T>
Vector<T>::Vector(const Vector& other) : data(other.sz){
    sz = other.sz;
    uninitialized_copy_n(other.data.buf, other.sz, data.buf);
}
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    data.Swap(other.data);
    swap(sz, other.sz);
}

// Basic Exception Guarantee
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){

    // Copy and Swap idiom, efficent when capacity of the vector we try to copy to is less than size of the source vector
    if(data.cp < other.sz) {
        Vector<T> temp(other);
        data.Swap(temp.data);
        swap(sz, temp.sz);
    } else {
        // we are going to assume that ther is a copy assinment operator for type T
        for (size_t i; i < sz && i < other.sz; ++i) { // THIS LEADS TO BASIC EXCEPTION GUARANTEE
            data[i] = other.data[i];
        }
        // the left elements we need to construct in raw memory (copy constructor for type T assumed)
        if (sz < other.sz) {
            uninitialized_copy(other.data + sz, other.data + other.sz, data + sz);
        } else { 
        // some uf left elemts must be destoyed
            destroy(data + other.sz, data + sz);
        }
        sz = other.sz;
    }
    return *this;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    data.Swap(other.data);
    swap(sz, other.sz);
    return *this;
}
template<typename T>
Vector<T>::~Vector() {
    destroy_n(data.buf, sz);
}

// Strong Exception Guarantee
template <typename T>
void Vector<T>::PushBack(const T& elem) {
    if (sz = data.cp) {
        // logic which changes the capacity of the vector if neccesary
        Reserve(sz == 0 ? 1 : 2 * sz);
    }
    new (data + sz) T(elem); // assuming that T has Copy Constructor
    ++sz;
}

// Strong Exception Guarantee
template <typename T>
void Vector<T>::PushBack(T&& elem) {
    if (sz = data.cp) {
        // logic which changes the capacity of the vector if neccesary
        Reserve(sz == 0 ? 1 : 2 * sz);
    }
    new (data + sz) T(move(elem)); // assuming that T has Move Constructor
    ++sz;
}
template <typename T>
void Vector<T>::PopBack() {
    //data + sz - 1 -> ~T();
    destroy_at(data + sz - 1);
    --sz;
}

// Strong Exception Guarantee
template <typename T>
void Vector<T>::Resize(size_t n) {
    // resizes Vector i.e. constructs T objects, it's possible to scpecify the second method parameter which would be template to fill with
    Reserve(n);
    if (sz < n) {
        uninitialized_value_construct_n(data + sz, n - sz);
    } else {
        destroy_n(data + n, sz - n);
    }
    sz = n; // if we were to write it somhere earlier our method would give NO Exception Guarantee
}

// Strong Exception Guarantee
template <typename T>
void Vector<T>::Reserve(size_t n) {
    // Let us increase capacity (Raw memory) of an existing vector
    if (data.cp < n) { 
        RawMemory<T> data1(n);
        uninitialized_move_n(data.buf, sz, data1.buf);
       destroy_n(data.buf, sz); // Destroy T object in the old chunk of memory 
       data.Swap(data1); // reassing field data to the newly created chunk of memory
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