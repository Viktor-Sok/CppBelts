#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;
/*
 Evaluation of the ariphmetic expression which represented by the tree of Expression objects in memory 
Leaves of the tree are values, imtermidiate objects are arimphmetic expressions
3*(4 + 2) = 
       *
    /   \
   3    +
       / \
     4   2

Class structure:
Expression
    ValueExpr
    BinaryExpr
        ProductExpr
        SumExpr

*/
class Expression {
    /*Pure virtual class - interface*/
public: 
    virtual ~Expression() = default; // virtual constructor
    
    virtual int Evaluate() const = 0;
    virtual string ToString() const = 0;
};

using pe = shared_ptr<Expression>; // alias to the type; 

class ValueExpr : public  Expression {
    // stores values 
public:
    ValueExpr(int val) : value_(val) {}
    
    int Evaluate() const override { // override virtual function in base class 
        return value_;
    }
    string ToString() const override { // override virtual function in base class 
        return to_string(value_);
    } 
private:
    int value_;
};

class BinaryExpr : public Expression {
    // creates two branches of the tree (left, right pointer), which point either to the BinaryExpr subclass or to ValueExpr
    pe left_;
    pe right_;
    // defining virtual functions to avoid dublicating ToString() and Evaluate() methods in child classes: ProductExpr and SumExpr
    virtual char GetSymbol() const = 0; // pure virtual method
    virtual int EvaluateOnValues(int l, int r) const = 0;  // override virtual function in base class 
public:
    BinaryExpr(pe left, pe right) : left_(move(left)), right_(move(right)) {}
    
    string ToString() const final { // final means child classes cannot override the method
        return '(' + left_ -> ToString() + ')' +
                GetSymbol() +   // GetSymbol() is a pure virtual method, it will be replaced here by the child of BinaryExpr defenition
                '(' + right_ -> ToString() + ')'; 
    }
    int  Evaluate() const final { // final means child classes cannot override the method
        return EvaluateOnValues(left_ -> Evaluate(), right_ -> Evaluate());   // EvaluateOnValues() is  a pure virtual method, it will be replaced here by the child of BinaryExpr defenition
    }
};

class ProductExpr : public BinaryExpr {
    // inheritance from BinaryExpr is used here to override GetSymbol() and EvaluateONValues() virtual methods in the parent BinaryExpr
public:
    ProductExpr(pe left, pe right) : BinaryExpr(move(left), move(right)) {} // constructor of the parent class explecetly called in the initialization list
private:
    char GetSymbol() const override {
        return '*';
    } 
    int EvaluateOnValues(int left, int right) const override {
        return left * right;
    }   
};

class SumExpr : public  BinaryExpr {
    // inheritance from BinaryExpr is used here to override GetSymbol() and EvaluateONValues() virtual methods in the parent BinaryExpr
public:
    using BinaryExpr::BinaryExpr; // explicetly using parent's constructor
private:
    char GetSymbol() const override {
        return '+';
    }
    int EvaluateOnValues(int left, int right) const override {
        return left + right;
    }
};

// Functions which create onjects of the corresponding classes and return shared pointer to them
// they are used for writing expression int the code in the intellegable way
pe Value(int val) {
    return make_shared<ValueExpr>(val);
}
pe Sum(pe left, pe right) {
    return make_shared<SumExpr>(move(left), move(right));
}
pe Product(pe left, pe right) {
    return make_shared<ProductExpr>(move(left), move(right));
}

void Print(const Expression* e) {
    // Lazy evaluation happens here ToString() and Evaluate()
    if(!e) {
        cout << "Null expression provided" << endl;
        return;
    }
    cout << e -> ToString() << " = " << e -> Evaluate() << endl;
}

int main() {
    pe e1 = Product(Value(2), Sum(Value(3), Value(4)));
    //Here is what happens for evaluation of he above expression
    Print(e1.get());
    pe e2 = Sum(e1, Value(5));
    Print(e2.get());
    Print(e1.get());
    return 0;
}