#include <iostream>
using namespace std;

template <typename T>
class SimpleVector {
private:
    T* data; // pointer to manage array
    size_t size;
public:
    explicit SimpleVector(size_t size) : size(size) {
        data = new T[size]; // assigning pointer T to a block of memory size*size_of(T)
    }
    //explicit SimpleVector(initializer_list<T> list) : data(list) {

    //}

    ~SimpleVector() {
        delete[] data; // empty the heap, important to use with square brackets
    }
    T& operator[](size_t s) {
        // Accessing vector elements read/write access
        if (s < 0 or s > size - 1)
            throw runtime_error("Index is out of bounds");
        return *(data + s); // or data[s] is alternative
    }
    // Methods for range-based for loop
    // Also they allow to use standard algorithms
    const T* begin() const{
        return data;
    }
    const T* end() const {
        return data + size;
    }
};

int main() {
    SimpleVector<int> v(5);
    for (int i = 0; i < 5 ; ++i) {
        v[i] = i*i;
    }              
    for (auto e : v) {
        cout << e << " " << endl;
    }                                                                                                                                                                                                                                                                                                 
    return 0;
}