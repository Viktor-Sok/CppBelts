#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
    LogDuration(string comment = "") : start(steady_clock::now()), comment_(comment) {}
    ~LogDuration() {
        auto finish = steady_clock::now();
        auto dur = finish - start;
        if(comment_ != "") comment_.append(": "); 
        cerr << comment_<< duration_cast<milliseconds>(dur).count() << " ms" << endl;
    }
private:
    steady_clock::time_point start; 
    string comment_;
};