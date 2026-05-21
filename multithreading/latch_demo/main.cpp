#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <latch>
#include <filesystem>
#include <vector>

using namespace std::chrono_literals;

#if 0
void Initialization()
{
    std::cout<<"[ Initializtion Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout<<"[ Initializtion Thread End ]"<< std::endl;
}

void DatabaseInit()
{
    std::cout<<"[ DatabaseInit Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(500ms);
    std::cout<<"[ DatabaseInit Thread End ]"<< std::endl;

}

void RedisInit()
{
   std::cout<<"[ RedisInit Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(1000ms);
    std::cout<<"[ RedisInit Thread End ]"<< std::endl;
}

#else
void Initialization(std::latch& Latch)
{
    std::cout<<"[ Initializtion Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout<<"[ Initializtion Thread End ]"<< std::endl;
    Latch.count_down();
}

void DatabaseInit(std::latch& Latch)
{
    std::cout<<"[ DatabaseInit Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(500ms);
    std::cout<<"[ DatabaseInit Thread End ]"<< std::endl;
    Latch.count_down();

}

void RedisInit(std::latch& Latch)
{
   std::cout<<"[ RedisInit Thread Start ]"<< std::endl;
    std::this_thread::sleep_for(1000ms);
    std::cout<<"[ RedisInit Thread End ]"<< std::endl;
    Latch.count_down();
}

void Init_AppConfig(std::latch& Latch)
{
    std::cout<<"[ Init_AppConfig Thread Start ]"<< std::endl;
    std::filesystem::create_directories("config");
    std::filesystem::path configPath("config/app.log");
    while(!std::filesystem::exists(configPath)){
           
        std::this_thread::sleep_for(1000ms);
    }
    Latch.count_down();
    std::cout<<"[ Init_AppConfig Thread End ]"<< std::endl;
}
#endif
int main(void){

   constexpr int noOfThreads{4};
    // std::jthread InitThread{Initialization};
    // std::jthread DatabaseThread{DatabaseInit};
    // std::jthread RedisThread{RedisInit};

  
    std::latch Latch(noOfThreads);
    std::vector<std::jthread> threads;
    threads.emplace_back(Initialization, std::ref(Latch));
    threads.emplace_back(DatabaseInit, std::ref(Latch));
    threads.emplace_back(RedisInit, std::ref(Latch));
    threads.emplace_back(Init_AppConfig, std::ref(Latch));
    Latch.wait();
    std::cout << "[ Main thread Sleep ]" << std::endl;
    std::this_thread::sleep_for(2000ms);
    // process();
    std::cout << "[ Main Exit ]" << std::endl;
    return 0;
}

// mkdir build
// g++ -g -std=c++23 -Wall -Werror -lpthread -o build/out main.cpp