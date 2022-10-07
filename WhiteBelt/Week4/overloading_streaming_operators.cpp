#include <iostream>
#include <fstream>
#include <sstream> // to using string as stream (like file or console)
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
/* In this program we want to be able to read
 * our structure from the sream and also
 * write it to our stream using <<, >> operators.
 */
struct Duration {
    int hour;
    int min;
    
    Duration(int h = 0, int m = 0) {
        int total = h*60 + m;
        hour = total / 60;
        min = total % 60 ;
    }
}

    istream& operator >>(ifstream& stream, Duration& dur) {
    stream >> dur.hour;
    stream.ignore(1);
    stream >> dur.min;
    return stream;
}
// operator overloading, operator<< should return stream     
ostream& operator <<(ofstream& stream, const Duration& dur) {
    cout << setfill('0');
    stream << setw(2) << dur.hour << ":" << setw(2)<< dur.min << endl;
    return stream;
}
// mnemonics: operator + has the space between as if + was a name of a function
Duration operator +(const Duration& dur1, const Duration& dur2) {
    return {dur1.hour + dur2.hour, dur1.min + dur2.min};
}

bool operator <(const Duration& dur1, const Duration& dur2) {
    int total1 = dur1.hour*60 + dur1.min;
    int total2 = dur2.hour*60 + dur2.min;
    if (total2-total1 > 0) {
        return true;
    } else {
        return false;
    }
}

void printVector(const vector<Duration>& durs) {
    for (const auto& d : durs) {
        cout << d << " "; // overloaded operator<< for Duration is used
    }
    cout << endl;
}
    
void main() {
    stringstream dur_ss("01:50");
    Duration dur; // default constructor values are used
    dur_ss >> dur; // overloaded operator>> is used
    cout << dur << endl; // overloaded operator<< is used
    Duration dur1 = {2, 30};
    Duration dur2 = dur + dur1; // operator+ is overloaded
    vector<Duration> v {dur, dur1, dur2};
    // we want to sort our intervals in vector
    // we need to define operator> to sort using standard STL <algorithm> library
    sort(begin(v), end(v));
    printVector(v);
    return 0;
}