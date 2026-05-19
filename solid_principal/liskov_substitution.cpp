#include <iostream>
#include <stdexcept>

class liskovSubstitution {
public:   
     virtual void display() {
        std::cout << "Base class display function" << std::endl;
    }
};  

class Derived : public liskovSubstitution {
public:
    void display() override {
        std::cout << "Derived class display function" << std::endl;
    }
};  

void showDisplay(liskovSubstitution* obj) {
    obj->display();
}   


// add code that break the Liskov Substitution Principle 
class BrokenDerived : public liskovSubstitution {
public:
    // This override violates the Liskov Substitution Principle by
    // throwing an exception when used where the base is expected.
    void display() override {
        throw std::runtime_error("BrokenDerived cannot be used where liskovSubstitution is expected");
    }
    void additionalFunction() {
        std::cout << "This function is not in the base class" << std::endl;
    }
};  

int main() {
    std::cout << "Demonstrating Liskov Substitution Principle" << std::endl;
    liskovSubstitution* baseObj = new liskovSubstitution();
    liskovSubstitution* derivedObj = new Derived();             
    // Intentionally use a base-class pointer to a BrokenDerived instance
    // to demonstrate substitutability failure.
    liskovSubstitution* brokenObj = new BrokenDerived();

    showDisplay(baseObj);     // Output: Base class display function
    showDisplay(derivedObj);  // Output: Derived class display function

    try {
        showDisplay(brokenObj); // Will throw for BrokenDerived
    } catch (const std::exception& e) {
        std::cout << "Error when calling showDisplay on BrokenDerived: " << e.what() << std::endl;
    }

    delete baseObj;
    delete derivedObj;
    delete brokenObj;

    return 0;
}