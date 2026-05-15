#include <iostream>

class Base{
public:
    Base(){
        std::cout << "Base class constructor called" << std::endl;
    }
    
    void display(){
        std::cout << "Base class display function" << std::endl;
    }
    virtual void show(){
        std::cout << "Base class show function" << std::endl;
    }
    ~Base(){
        std::cout << "Base class destructor called" << std::endl;
    }
};

class Derived : public Base{
public:
    Derived(){
        std::cout << "Derived class constructor called" << std::endl;
    }

    void display() {             
        std::cout << "Derived class display function" << std::endl;
    }
    void show() override {
        std::cout << "Derived class show function" << std::endl;
    }
    ~Derived(){
        std::cout << "Derived class destructor called" << std::endl;
    }
};


class BaseI{
    public:
    virtual void show() = 0;
    virtual ~BaseI() = default;
};

class BaseDemo: public BaseI{
    public:
    void show(){
        std::cout << "BaseDemo show called" << std::endl;
    }    
};

class DerivedDemo: public BaseI{
    public:
    void show(){
        std::cout << "DerivedDemo show called" << std::endl;
    }    
};



int main(){
    Base b;
    Derived d;

    b.display(); // Calls Base class display function
    d.display(); // Calls Derived class display function

    Base* basePtr = &d; // Base class pointer pointing to Derived class object
    basePtr->display(); // Calls Base class display function (not polymorphic)
    basePtr->show(); // Calls Derived class show function (polymorphic)

   //  BaseI baseIObj; // This will cause a compilation error because BaseI is an abstract class
    BaseDemo baseDemo;
    DerivedDemo derivedDemo;        
    BaseI* baseIPtr1 = &baseDemo; // Base class pointer pointing to BaseDemo object
    BaseI* baseIPtr2 = &derivedDemo; // Base class pointer pointing to DerivedDemo object   
    baseIPtr1->show(); // Calls BaseDemo show function
    baseIPtr2->show(); // Calls DerivedDemo show function
    return 0;
}

// g++ -o out  main.cpp -Wall