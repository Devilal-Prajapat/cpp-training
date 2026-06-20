#include <iostream>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <chrono>


#if 0

class ThreadPool{
    std::vector<std::thread> pool_;
    int max_thread;
    std::mutex mtx;
    std::queue<std::function<void()>> Tasks;
    bool is_running = true;
public: 
    ThreadPool(int count) : max_thread(count){
        for(int i = 0; i< max_thread; i++){
            pool_.emplace_back([this](){
                while (is_running)
                {
                    std::function<void()> task;
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        if(Tasks.empty())
                            continue;
                        task = Tasks.front();
                        Tasks.pop();
                    }
                    task();
               }                
            });
        }
    }

    void stop(){
        is_running = false;
        for(auto &p : pool_){
            if(p.joinable())
                p.join();
        }
    }

    void insert(std::function<void()> task){
        std::lock_guard<std::mutex> lock(mtx);
        Tasks.push(task);
    } 
};
#else
#include <condition_variable>

class ThreadPool{
    std::vector<std::thread> pool_;
    int max_thread;
    std::mutex mtx;
    std::queue<std::function<void()>> Tasks;
    std::condition_variable cv;
    bool is_running = true;
public: 
    ThreadPool(int count) : max_thread(count){
        for(int i = 0; i< max_thread; i++){
            pool_.emplace_back([this](){
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this]{
                            return (!Tasks.empty() || !is_running );
                        });

                        if(!is_running && Tasks.empty())
                            break;
                        task = std::move(Tasks.front());
                        Tasks.pop();
                        lock.unlock();
                    }
                    task();
               }                
            });
        }
    }

    void stop(){
        {
            std::lock_guard<std::mutex> lock(mtx);
            is_running = false;         
        }
        cv.notify_all();
        for(auto &p : pool_){
            if(p.joinable())
                p.join();
        }        
    }

    void insert(std::function<void()> task){
        {
            std::lock_guard<std::mutex> lock(mtx);
            Tasks.push(std::move(task));
        }
        cv.notify_one();        
    }

    ~ThreadPool(){
        if(is_running)
            stop();
    } 
};
#endif

void TaskA(int val){
    static int count = 0;
    std::cout << val << " count "<< count++  << " TaskA\n";
}

void TaskB(int val){
    static int count = 0;
    std::cout << val << " count "<< count++ << " TaskB\n";
}

void TaskC(int val){
    static int count = 0;
    std::cout << val << " count "<< count++ <<" TaskC\n";
}

int main(void){
    ThreadPool pool(2);
    int val = 0;
    while(true){
        if(val> 5)
        {
             // pool.stop();
            break;
        }else{

            pool.insert([val](){
                TaskA(val);
            });
            pool.insert([val](){
                TaskB(val);
            });
           // std::this_thread::sleep_for(std::chrono::milliseconds(20));
            pool.insert([val](){
                TaskC(val);
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            val++;
        }
    }
}