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
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(__LINE__) {message};