#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define LOOP(i, n) for(int i = 0; i<n; ++i)
using namespace std;

class MyFavBooks {
private:
    string bookName;
public:
    MyFavBooks(){} // default constructor
    MyFavBooks(string& const name){ bookName = name;} 
     // const method allow as to call it when passing object to 
     // a function by const reference &
    int getBookName const {
        return bookName;
    }
};

void printBookName(MyFavBooks& const book) {
    cout << book.getBookName() << endl;
}

MyFavBooks getBook(bool is_empty) {
    if (is_empty) {
        // returns empty object
        return {};
    } else {
        // returns initialized objec
        return {"Carmilla"};
    }
    
}
int main() {
    // intializing object when passing to function
    // using curly braces {} is equavalent option to using constructor name
    printBookName(MyFavBooks());
    printBookName({});
    printBookName(MyFavBooks("The Dazzler"));
    printBookName({"The Dazzler"});
    // initializing object when passing to another method
    vector<MyFavBooks> books;
    books.push_back({"The Dazzler"});
    books.push_back({"Matilda"});
    // getting object from a function
    MyFavBooks book1 = getBook(false);
    return 0;
}