#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
// Global variable to demonstrate shared state between threads
int step = 0;
void task(const char *name, int count){
    while(count--){
        std::cout<<name << " "<<  step <<std::endl;
        step++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Main thread creates a new thread to run the task function, then waits for it to finish using join() before exiting.

int main()
{
    std::cout<<"Hello World"<< std::endl;
    std::cout<< "main start" << std::endl;
    std::thread t1(task, "T1", 5);
   
    t1.join();  // wait for t1 to finish before main thread continues
   // t1.detach();  // run in background, main thread will not wait for t1 to finish

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get(); // wait for user input before exiting
    std::cout << "main finished" << std::endl;
    return 0;
}

// Output:
// g++ -g -std=c++23 -Wall -Werror -lpthread -o build/out main.cpp