#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
// Global variable to demonstrate shared state between threads
int step = 0;
void task(const char *name, int count){
    while(count--){
        std::cout<<name << " "<<  step <<std::endl;
        step++;  // This is not thread-safe, but we will demonstrate mutex protection in the next function
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// mutex mtx; // mutex to protect shared variable 'step' if needed
std::mutex mtx; // mutex to protect shared variable 'step' if needed
int step_mutex = 0; // separate variable to demonstrate mutex protection    
void task_with_mutex(const char *name, int count){
    std::cout << "Using mutex to protect shared variable 'step_mutex'" << std::endl;
    while(count--){
        mtx.lock(); // lock the mutex before accessing shared variable
        std::cout<<name << " "<<  step_mutex <<std::endl;
        step_mutex++;
        mtx.unlock(); // unlock the mutex after accessing shared variable
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void task_with_lock_guard(const char *name, int count){
    std::cout << "lock_guard will automatically release the mutex when it goes out of scope" << std::endl;
    while(count--){
        std::lock_guard<std::mutex> lock(mtx); // automatically lock and unlock the mutex
        std::cout<<name << " "<<  step_mutex <<std::endl;
        step_mutex++;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Main thread creates a new thread to run the task function, then waits for it to finish using join() before exiting.

int main()
{
    std::cout<<"Hello World"<< std::endl;
    std::cout<< "main start" << std::endl;
    std::thread t1(task, "T1", 5);
    std::thread t2(task_with_mutex, "T2", 5);
    std::thread t3(task_with_lock_guard, "T3", 5);
    t1.join();  // wait for t1 to finish before main thread continues
    t2.join();  // wait for t2 to finish before main thread continues
    t3.join();  // wait for t3 to finish before main thread continues
   // t1.detach();  // run in background, main thread will not wait for t1 to finish

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get(); // wait for user input before exiting
    std::cout << "main finished" << std::endl;
    return 0;
}

// Output:
// mkdir build
// g++ -g -std=c++23 -Wall -Werror -lpthread -o build/out main.cpp