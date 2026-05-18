#include <iostream>

class Resource {
    private:
    // Add any necessary member variables here
    int *ptr; // Example member variable
    int size; // Example member variable
public:
    Resource(int sz) : size(sz) {
        ptr = new int[size]; // Allocate resource
        std::cout << "Resource acquired." << std::endl;
    }           

    ~Resource() {
        delete[] ptr; // Deallocate resource
        std::cout << "Resource released." << std::endl;
    }
};  


int main() {
    {
        int *rawPtr = new int[10]; // Manually allocated resource
        std::cout << "Resource manually acquired." << std::endl;
        for (int i = 0; i < 10; ++i) {
            rawPtr[i] = i; // Use the resource
        }
        for (int i = 0; i < 10; ++i) {
            std::cout << rawPtr[i] << " "; // Output the resource
        }

        delete[] rawPtr; // Manually deallocated resource
        std::cout << "\nResource manually released." << std::endl;
    }

    // Simulating an exception without RAII

    try{    
        int *rawPtr = new int[10]; // Manually allocated resource
        std::cout << "Resource manually acquired." << std::endl;
        for (int i = 0; i < 10; ++i) {
            rawPtr[i] = i; // Use the resource
        }
        throw std::runtime_error("An error occurred!"); // Simulate an exception
        delete[] rawPtr; // This line will never be reached, causing a memory leak
        std::cout << "Resource manually released." << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }


    //  Using RAII to manage resources
    {
        Resource res(10); // Resource is acquired here
        // Do something with the resource
    } // Resource is automatically released here when 'res' goes out of scope

    // Simulating an exception to demonstrate RAII
    try {
        Resource res(20); // Resource is acquired here
        // Do something with the resource
        throw std::runtime_error("An error occurred!"); // Simulate an exception
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    

    return 0;
}