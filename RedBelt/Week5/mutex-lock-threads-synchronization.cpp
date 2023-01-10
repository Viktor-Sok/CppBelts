#include <iostream>
#include <future>
#include <mutex> // mutual exclusion
using namespace std;

// class below demonstrates idiom RAII for mutex
// by the same logic we created our porfiler.h for measuring time
// actually there is a built-in wrapper that do the same : lock_guard<mutex> g(m);

class Lock {
    mutex& m_;
public:
    Lock(mutex& m) : m_(m) {
        cerr << "mutex is locked for Spend method" << endl;
        m_.lock();
    }
    ~Lock(){
        cerr << "mutex is realesed for Spend method" << endl;
        m_.unlock();
    }
};

struct Account {
    int balance = 0;
    mutex m;

    bool Spend(int value) {
        // below is the code which should be executed ONLY BY ONE THREAD at a time
        //lock_guard<mutex> g(m); --------------------- //take ownership of mutex
        Lock g(m);
        cerr << "Spend method does something in one thread only" << endl;
        if(value <= balance) {
            // making sure we can't spend more than on our balance
            balance -= value;
            return true;
        
        //----------------------------------------- releases mutex when destructor for lock_guard called
        }
        return false;
    }
};

int useCreditCard(Account& account) {
    // getting money from account 100'000 times by 1 dollar
    int total = 0;
    for (int i = 0; i < 100; ++i) {
        if (account.Spend(1)) {
            ++total;
        }
    }
    return total;
}

int main() {
    Account family_card{100};
    // All family members use the same account
    // All threads below must be synchronized to avoid data corruption due to thread race
    auto wife = async(useCreditCard, ref(family_card));
    auto husband = async(useCreditCard, ref(family_card));
    auto son = async(useCreditCard, ref(family_card));
    auto dauther = async(useCreditCard, ref(family_card));
    cout << "Spent: " << wife.get() + husband.get() + son.get() + dauther.get() << '\n'; 
    cout << "Balance: " << family_card.balance << '\n';
    return 0;
}