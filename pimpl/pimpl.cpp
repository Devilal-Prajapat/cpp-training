#include <iostream>
#include "pimpl.hpp"

// Definition of the implementation class
class Widget::Impl {
public:
    void doSomething() {
        std::cout << "Doing something in the implementation!" << std::endl;
    }
};


Widget::Widget() : pImpl(new Impl()) {
    std::cout << "Widget constructed." << std::endl;
}           

Widget::~Widget() {
    delete pImpl; // Clean up the implementation
    std::cout << "Widget destructed." << std::endl;
}

void Widget::doSomething() {
    std::cout << "Widget is doing something..." << std::endl;
    pImpl->doSomething(); // Delegate to the implementation
}