#include <iostream>
#include "pimpl.hpp"

int main() {

    {
        Widget widget; // Widget is constructed
        widget.doSomething(); // Calls the method that uses the implementation
    } // Widget is destructed when going out of scope

    try {
        Widget anotherWidget; // Another widget is constructed
        anotherWidget.doSomething(); // Calls the method that uses the implementation
        throw std::runtime_error("An error occurred!"); // Simulate an exception
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0; // Widget is destructed when going out of scope
}


// g++ -o out main.cpp pimpl.cpp