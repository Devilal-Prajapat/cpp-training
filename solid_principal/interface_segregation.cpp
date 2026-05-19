#include <iostream>
#include <stdexcept>
// Clients should not be forced to depend on interfaces they do not use.
// therefore, we should split the interfaces into smaller, more specific ones so that clients only need to know about the methods that are relevant to them.

class IMachine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class OldPrinter : public IMachine {
public:
    void print() override {
        std::cout << "Printing..." << std::endl;
    }

    void scan() override {
        // Not supported
        std::cout << "Scan not supported" << std::endl;
        // throw std::runtime_error("Scan not supported");
    }

    void fax() override {
        // Not supported
       std::cout << "Fax not supported" << std::endl;
        // throw std::runtime_error("Fax not supported");
    }
};

// you forced the overriding of methods scan and fax that are not relevant to the OldPrinter class, which violates the Interface Segregation Principle.

// Refactored code adhering to the Interface Segregation Principle
class IPrinter {
public:
    virtual void print() = 0;       
};

class IScanner {
public:
    virtual void scan() = 0;
};      

class IFax {
public:    virtual void fax() = 0;
};


class OldPrinter_ : public IPrinter {
public: 
   void print() override {
        std::cout << "Printing..." << std::endl;
    }
};


int main() {
    std::cout << "Demonstrating Interface Segregation Principle" << std::endl;

    OldPrinter printer;
    printer.print();
    printer.scan(); // This will throw an exception, as scan is not supported by OldPrinter
    printer.fax();  // This will throw an exception, as fax is not supported by OldPrinter

    //  Refactored code adhering to the Interface Segregation Principle
    OldPrinter_ printer_;
    printer_.print();          
    return 0;
}