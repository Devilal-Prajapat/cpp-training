#include <iostream>


// The Open/Closed Principle states that software entities (classes, modules, functions, etc.) should be open for extension but closed for modification. This means that you should be able to add new functionality to a class without changing its existing code.
//  This promotes code stability and reduces the risk of introducing bugs when adding new features. 

// Base class for payment processing
class PaymentProcessor {
public:
    virtual void processPayment(double amount) = 0; // Pure virtual function
};

// Credit card payment processor
class CreditCardPaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
};


class PayPalPaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
};

int main() {
    std::cout << "Demonstrating Open/Closed Principle" << std::endl;
    PaymentProcessor* paymentProcessor;

    // Using credit card payment processor
    paymentProcessor = new CreditCardPaymentProcessor();
    paymentProcessor->processPayment(100.0);
    delete paymentProcessor;

    // Using PayPal payment processor
    paymentProcessor = new PayPalPaymentProcessor();
    paymentProcessor->processPayment(200.0);
    delete paymentProcessor;

    return 0;
}

// g++ -o out open_close.cpp