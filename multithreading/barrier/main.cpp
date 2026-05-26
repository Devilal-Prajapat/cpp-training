#include <iostream>
#include <thread>
#include <chrono>
#include <barrier>


void ledTask(std::barrier<>& sync){
    std::cout<< "Led Initialization" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sync.arrive_and_wait();
    std::cout<< "At Sync Point" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<< "Led Initialization Done" << std::endl;
}

void buttonTask(std::barrier<>& sync){
    std::cout<< "Button Initialization" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sync.arrive_and_wait();
    std::cout<< "At Sync Point" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<< "Button Initialization Done" << std::endl;
}


int main(void){
    constexpr int numberOfthreds = 2;
    std::cout<< "Main Thread" << std::endl;
    std::barrier<> sync(numberOfthreds);
    std::jthread T1(ledTask, std::ref(sync));
    std::jthread T2(buttonTask, std::ref(sync));

    // sync.wait() //@note wait should not be called here, this shoud be in callable thread
    std::cout << "Main Exit" <<std::endl;
    return 0;
}

// mkdir build
// g++ -o ./build/out main.cpp -std=c++20 -lpthread -Wall -Werror
