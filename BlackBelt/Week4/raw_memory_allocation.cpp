#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Student {
    string Name;
    double Rating;

    void Print() const {
        cout << Name << " " << Rating << "\n";
    }
};

int main() {
    {
     // Allocate on the stack
     Student s{"Oleg", 5.0};
     s.Print();   
    }
    {
     // Allocate in the heap
     Student* s = new Student{"Ivan", 3.0}; // new requests Operating system to allocate memory then creates object in it
     s -> Print();
     delete s; // deltes object and returns memory to Operating System
    }
    {
     // Allocate object in the reserved memory on the stack
     alignas(Student) char buf[1024]; // alingas aligns memory in order to effeciently accomodate Student structure
     Student* s = new (buf) Student{"Anton", 4.0}; // new creates object in reserved buffer
     s -> Print();
     s -> ~Student();
    }
    {
     // Allocate object in the reserved memory in the heap 
     char* buf = new char[1024]; // buffer in the heap
     Student* s = new (buf) Student{"Petr", 4.0}; // new creates object in reserved buffer
     s -> Print();
     s -> ~Student();
     delete [] buf;
    }
    {
     // Allocate memory in the heap with operator new
     void* mem = operator new(sizeof(Student)); // reserves sizeof(Student) bytes of memory in the heap
     Student* s = new (mem) Student{"Kostyan", 2.0};
     s -> Print();
     s -> ~Student();
     operator delete(mem); // deletes memory
    }

    {
        // std::allocator let us separate memory allocation from the initialization of an object and destruction of an object from memory de-allocation
        // widely used for STL containers
        allocator<Student> my_alloc;
        // allocate space fro 3 objets of type Student
        Student* s = my_alloc.allocate(3); // containmer of 3 elemts of type Student, you can use 1 to achive the same functionality as with operator new
        // construct those objects using pointer s
        my_alloc.construct(s, Student {"Student1", 3.0});
        my_alloc.construct(s + 1, Student {"Student2", 3.0});
        my_alloc.construct(s + 2, Student {"Student3", 3.0});
        // use objects
        for (int i = 0; i < 3; ++i)
            (s + i) -> Print();
        // destroy objects
        my_alloc.destroy(s);
        my_alloc.destroy(s + 1);
        my_alloc.destroy(s + 2);
        // deallocate memory
        my_alloc.deallocate(s, 3); // deallocates memore starting from s pointer and deallocates 3 objects
        }



    return 0;
}