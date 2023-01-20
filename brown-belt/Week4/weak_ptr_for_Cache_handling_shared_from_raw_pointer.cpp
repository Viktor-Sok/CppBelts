#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//using Wp = weak_ptr<Data>;
//using Sp = shared_ptr<Data>;

class Data {
public:
    Data(string name) : name_(name) {}
    ~Data() {cout << "Data object was deleted\n";}
    string name_;
};

class DataCache {
public:
    shared_ptr<Data> getData(const string& name) {
        auto ret = map_[name].lock(); // lock() creates shared_ptr from weak_ptr
        if (!ret) {
            ret = make_shared<Data>(name);
            map_[name] = ret;  // copy assignment operator of weak_ptr class implicetly converts shared_ptr to weak_ptr
        }
    return ret;
    }
    void printData() {
        for (auto [k, v] : map_) {
            string out = v.lock() ? v.lock() -> name_ : "No Data object";
            cout << k << ":" << out << endl;
        }
    }
private: 
map<string, weak_ptr<Data>> map_;
};

int main() {
    // creating shared pointer from raw leads to different count block for shared - bad practice
    Data* pd = new Data("cat");
    shared_ptr<Data> spd1(pd);
    shared_ptr<Data> spd2(pd);
    cout << "Shared ponters created from teh raw pointer has different count blocks: " << endl;
    cout << "Shared pointer count: " <<"sp1 " << spd1.use_count() << ", sp2 " << spd2.use_count() << endl;
    // demostrating functionality of weak_ptr
    DataCache cache;
    auto p1 = cache.getData("name1");
    auto p2 = cache.getData("name2");
    {
    auto p3 = cache.getData("name3");
    cache.printData();
    cout << "Whemn p3 goes out of scope weak_ptr deletes it in teh class, so we are keeping memory: " << endl;
    }
    auto p4 = cache.getData("name4");
    cache.printData();
    return 0;
}