#include <iostream>

class Animal {
public:
    virtual void makeSound() const {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override {   
        std::cout << "Dog barks." << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        std::cout << "Cat meows." << std::endl;
    }
};  

int main() {
    int i = 42;
    double d = static_cast<double>(i); // Implicitly converts int to double
    std::cout << "Integer: " << i << ", Double: " << d << std::endl;

    double x = 3.14;
    int y = static_cast<int>(x); // Explicitly converts double to int (truncation)
    std::cout << "Double: " << x << ", Integer: " << y << std::endl;

    Animal* animal = new Dog(); // Upcasting: Dog* to Animal*
    animal->makeSound(); // Calls Dog's makeSound() due to virtual function
    
    Dog* dogptr = dynamic_cast<Dog*>(animal); // Downcasting: Animal* to Dog*
    if (dogptr) {
        dogptr->makeSound(); // Calls Dog's makeSound() due to virtual function
    }

   Cat* catPtr = dynamic_cast<Cat*>(animal); // Attempting to downcast to Cat*
    if (catPtr) {
        catPtr->makeSound(); // This will not be called since the cast fails
    } else {
        std::cout << "Failed to cast Animal* to Cat*." << std::endl;
    }


    delete animal; // Clean up

    const int a = 10;
    int* ptr = const_cast<int*>(&a); // Remove const qualifier (unsafe)
    *ptr = 20; // Modifying a const variable leads to undefined behavior
    std::cout << "Const variable modified: " << a << std::endl; // Output may be unpredictable due to undefined behavior    

    int num = 5;
    void* voidPtr = &num; // Implicitly converts int* to void*
    int* intPtr = reinterpret_cast<int*>(voidPtr); // Explicitly converts void*
    std::cout << "Original number: " << num << ", Reinterpreted number: " << *intPtr << std::endl;  

    return 0;
}

// g++ -o out main.cpp