#include <iostream>
#include <map>

// The Single Responsibility Principle states that a class should have only one reason to change,
//  meaning it should have only one job or responsibility.
//  This promotes separation of concerns and makes the code easier to maintain and understand.

class Demo {
private:
    // Private members and methods related to the internal workings of the class
    std::map<std::string, int> data; // Example of internal data storage
public:
    void add(const std::string& name, int value) {
        data[name] = value;
    }
    void calculateBills() {
        std::cout << "Calculating bills..." << std::endl;
        // Perform some calculations on the data
        int sum = 0;    
        for (const auto& value : data) {
            sum += value.second;
        }
        std::cout << "Total: " << sum << std::endl;
    }

    void printInvoice() {
        std::cout << " ***** Invoice *****" << std::endl;
        int sum = 0;
        for (const auto& value : data) {
            std::cout << value.first << ": " << value.second << std::endl;
            sum += value.second;
        }
        std::cout << "Total: " << sum << std::endl;
    }
};  


// Refactored code adhering to the Single Responsibility Principle

class DataManager {
private:
    std::map<std::string, int> data; // Example of internal data storage
public:
    void addData(const std::string& name, int value) {
        data[name] = value;
    }
    const std::map<std::string, int>& getData() const {
        return data;
    }
};  

class BillCalculator {
public:
    void calculateBills(const std::map<std::string, int>& data) {
        std::cout << "Calculating bills..." << std::endl;
        int sum = 0;
        for (const auto& value : data) {        
            sum += value.second;
        }
        std::cout << "Total: " << sum << std::endl;
    }
};

class Invoice {
public:
    void printInvoice(const std::map<std::string, int>& data) {
        std::cout << " ***** Invoice *****" << std::endl;
        int sum = 0;
        for (const auto& value : data) {
            std::cout << value.first << ": " << value.second << std::endl;          
            sum += value.second;
        }
        std::cout << "Total: " << sum << std::endl;
    }
};


int main() {

    std::cout << "Demonstrating Single Responsibility Principle" << std::endl;

    // Using without adhering to the Single Responsibility Principle
    Demo demo;
    demo.add("Item1", 100);
    demo.add("Item2", 200);
    demo.calculateBills();
    demo.printInvoice();

    // Using with adhering to the Single Responsibility Principle
    DataManager dataManager;
    dataManager.addData("Item1", 100);      
    dataManager.addData("Item2", 200);
    
    BillCalculator billCalculator;
    billCalculator.calculateBills(dataManager.getData()); // Assuming data is accessible for simplicity  
    
    Invoice invoice;
    invoice.printInvoice(dataManager.getData()); // Assuming data is accessible for simplicity
    return 0;
}

// g++ -o out single_responsibility.cpp