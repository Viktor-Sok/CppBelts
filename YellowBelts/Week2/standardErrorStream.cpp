#include <iostream>
int main() {
// e.g. if we send program to online testing system then
// any output to standars error stream will be ignored
std::cout << "Normal stream" << std::endl;
std::cerr << "Everyting is OK!" << std::endl;
getchar();
return 0;
}