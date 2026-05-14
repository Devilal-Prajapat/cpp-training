#include <iostream>

/*
    For singleton pattern
    make constructor private
    delete the copy constructor and delete the copy assignment operator
    construct the static method getInstance and return the static object via reference or via pointer.
   
    public:
    static singleton& getInstance(){ 
        static singleton instance;
        return instance;
    }

    class Singleton{
    private:
        Singleton(){}
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&)=delete;
        static Singleton* instance;
    public:
        static Singleton* getInstance(){
            if(instance == nullptr){
                instance = new Singleton();
            }
            return instance;
        }

        void log(std::string str){
            std::cout<< str << std::endl;
        }
    };
    Singleton* Singleton::instance=nullptr;
*/

#if 0
class Logger{
private:
    Logger(){ }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&)=delete;
public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void log(std::string str){
        std::cout<< str << std::endl;
    }
};
#else
class Logger{
private:
    Logger(){ }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&)=delete;
    static Logger* instance;
public:
    static Logger* getInstance(){
        if(instance == nullptr){
            instance = new Logger();
        }
        return instance;
    }

    void log(std::string str){
        std::cout<< str << std::endl;
    }
};
Logger* Logger::instance=nullptr;
#endif



int main(void)
{
    #if 0
    // Logger& l1 = Logger::getInstance();
    // std::cout << &l1 << std::endl;

    // Logger& l2 = Logger::getInstance();
    // std::cout << &l2 << std::endl;
    // l2.log("hello world");
    Logger::getInstance().log("Hello world");
    #else
    Logger::getInstance()->log("Hello world from singleton");
    #endif
}
