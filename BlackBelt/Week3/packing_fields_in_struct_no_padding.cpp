#include <iostream>
#include <array>

#define SIZEOF(T) (cout << #T << ":\t" \
                        << "sizeof = " << sizeof(T) << '\t' \
                        << "alignof = " <<  alignof(T) << '\n')

using namespace std;

struct Data {
    int number; // 4
    char c1; // 1
    char c2;
    char c3;
    int region;
};

#pragma pack(push, 1)
struct Data1{
    int number; // 4
    char c1;  // 1
    char c2; 
    char c3;
    int region;
};
#pragma pack(pop) 

struct Data2 {
    uint16_t number:10; //2, 10 bit
    char c1; // 1
    char c2;
    char c3;
    uint16_t region:10;
};

// look up array to save space used by struct, we can now store indexies of this array in the struct
const static int N = 10;
const std::array<char, N> Letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L'};

struct Data3 {
    uint16_t number:10; //2, 10 bit
    uint8_t c1:4; //1, 4 bit
    uint8_t c2:4;
    uint8_t c3:4;
    uint16_t region:10; 
};

struct Data4 {
    // fieals are stored inside bytes, the same field can occupy different bytes, so
    // it's bad for performance, but saves memory, inside uint32_t which is 4 bytes will be
    //stored all the fields, it will raise errot if we try something like this
    // Data4 obj;
    // auto x = &obj.region // impossible to get adress in bytes, becouse field is stored in 10 bits
    // sizeof(obj.number) // sizeof can't give answer in bytes, becouse it's 10 bit
    uint32_t number:10; //2, 10 bit
    uint32_t c1:4; //1, 4 bit
    uint32_t c2:4;
    uint32_t c3:4;
    uint32_t region:10; 
};
static_assert(sizeof(Data4) == 4, "Wrong size!"); // prevents us from the typing error if we forget specify 10 or 4 bits above

int main() {
    SIZEOF(Data);
    SIZEOF(Data1);
    SIZEOF(Data2);
    SIZEOF(Data3);
    SIZEOF(Data4);
    return 0;
}
