#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

/*
    Example of sharing resource between threads by the means of shared pointer.
    Shared pointer counter in the class shared_pointer has built-in synchronization (mutex) , so we cann acceess it from
    different threads without worrying of program error occuring
*/
using namespace std;
class Data {
public:
    Data(string data) : data_(data) {
        cout << "Data constructed\n";
    }
    ~Data() {
        cout << "Data destructed\n";
    }

    const string& Get() const {
        return data_;
    }
    string& Get() {
        return data_;
    }
private:
    string data_;
};

void shareResorce(shared_ptr<const Data> ptr) { 
    /*this function shares Data class (the sahred resource) between threads by providing shared pointer to the thread*/
    stringstream ss;
    ss << "Shared resource: " << ptr -> Get() << " in " << this_thread::get_id() << ", counter = " << ptr.use_count() << endl;
    cout << ss.str();
}
vector<future<void>> spawn() { 
    /*This function assigns tasks to the threads*/
    vector<future<void>> tasks;

    auto data = make_shared<const Data>("meow"); // shared pointer to the shared data between threads (const prevents from data curraption due to thread race)

    for (int i = 0; i < 10; ++i) {
        tasks.push_back(async([=](){shareResorce(data);})); // taking data by value (=), becouse data will be destructed after spawn function finished working

    }
    return tasks;
}

int main() {
    cout  << "Spawning tasks...\n";
    auto tasks = spawn();
    cout << "Done spawning\n"; //this statement will be executed earlier than spawn(), becouse there will be manyu threads running in parallel with main
    return 0;
}