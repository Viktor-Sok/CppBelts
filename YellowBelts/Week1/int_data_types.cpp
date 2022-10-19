#include <iostream>
#include <fstream>
#include <sstream> // to using string as stream (like file or console)
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint> //c -std-int library for different types of int
#include <limits> // to find limits of different data types
using namespace std;

int main() {
    int x = 3; //32 (4 bytes) bit the most efficient on the machine processor where program compiled
    unsigned int y; // also effective on the processor architecture
    size_t z; // type whcih returned by containers like vector.size()
    //  The following types have fixed size (int depends on the processor architecture)
    // int32_t, uint32_t, int8_t, int_16t, int64_t 
    cout << sizeof (long int) << endl;
    cout << numeric_limits<long int>::min() << " "<<numeric_limits<long int>::max() << endl;
    return 0;
}
