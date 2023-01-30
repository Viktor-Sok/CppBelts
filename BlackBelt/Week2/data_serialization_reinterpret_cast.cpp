#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string buf = "Text to be serialized ...";
    int number = 5'036'750;
    {
        ofstream out("data.bin");
        out.write(buf.c_str(), buf.size()); //serialization from buffer to the output file stream
        out.close();
    }
    {
        ifstream in("data.bin");
        string buff(buf.size(), ' ');
        in.read(buff.data(), buff.size()); // desirialization from a binary file to the file input stream
        cout << buff << endl;
    }
    {
        ofstream out("data1.bin");
        out.write(reinterpret_cast<char*>(&number), sizeof(number));  // this kind of cast tells compileer to iinterpret int* as char*
        out.close();
    }
    {
        // data in the text form (take more space than binary files)
        ofstream out("data1.txt");
        out << number;
        out.close();
    }

    return 0;
}