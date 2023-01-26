#include <iostream>
#include <string>

using namespace std;

class SwimmingPool {
private:
    double length;
    double width;
    double depth;
    int nlanes;
    int npeople;
    // very ambigous constructor, direct initialization would look like SwimmingPool(50., 20., 2., 4, 28)
    SwimmingPool(double a, double b, double c, int d, int e)
    : length(a), width(b), depth(c), nlanes(d), npeople(e) {}
public:
    void stats() {
        cout << "Number of lanes: " << nlanes << " Number of people: " << npeople << endl;
    }
    friend class SwimmingPoolBuilder;
};

class SwimmingPoolBuilder {
public:
    SwimmingPoolBuilder& setLength(double a) {
        length = a;
        return *this;  // returning reference to the object let us call setters in chain
    } 
    SwimmingPoolBuilder& setWidth(double b) {
        width = b;
        return *this;
    } 
    SwimmingPoolBuilder& setDepth(double c) {
        depth = c;
        return *this;
    } 
    SwimmingPoolBuilder& setNlanes(int d) {
        nlanes = d;
        return *this;
    } 
    SwimmingPoolBuilder& setNpeople(int e) {
        npeople = e;
        return *this;
    } 

    SwimmingPool build() const {
        return {length, width, depth, nlanes, npeople};
    }
private:
    double length;
    double width;
    double depth;
    int nlanes;
    int npeople;
    
};

int main() {
    // initializing class with ambigous constructor using builder class
    // returning refernce to the object let us apply setters by chain
    auto pool = SwimmingPoolBuilder().setLength(50.).setWidth(20.).setDepth(2.).setNlanes(4).setNpeople(28).build();
    pool.stats();
    return 0;
}