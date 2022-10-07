#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define LOOP(i, n) for(int i = 0; i<n; ++i)
using namespace std;

class MyFavBooks {
public:
    string bookName;
     // const method allow as to call it when passing object to 
     // a function by const reference &
    int getBookName const {
        return bookName;
    }
};

void printBookName(MyFavBooks& const book) {
    cout << book.getBookName() << endl;
}

int main() {
    MyFavBooks book;
    book.bookName = "The Dazzler";
    printBookName(book);
    return 0;
}