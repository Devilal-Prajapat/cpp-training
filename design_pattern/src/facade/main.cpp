#include <iostream>
#include <chrono>
#include <thread>
class Led{
private:
    int state{0};

public:
    void init(){
        std::cout<< "Led Init" << std::endl;
    }


    void blink()
    {
        state = !state;
        std::cout<< "Led blink [state " << state << "]"<<std::endl;
    }
};


class ADC{
private:
    int raw_data{0};
public:
    void init(){
        std::cout<< "ADC Init" << std::endl;
    }

    int raw_read(){
        return 512;
    }

    void ReadADC()
    {
        raw_data = raw_read();
        std::cout<< "ADC  [Read " << raw_data << "]"<<std::endl;
    }
};


class Facade{
private:
    Led led;
    ADC adc;

public:
    void init(){
        led.init();
        adc.init();
    }

    void run(){
        led.blink();
        adc.ReadADC();
    }
};


int main(void){
    Facade f;
    f.init();
    while(1){
        f.run();
        std::cout<< "Main sleep for 1s"<< std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// module1
// module2
// module3

//Facade has module1, module2, module3
// reduce complexity
// provide simple interface to client. 
// code readability


// mkdir build
// g++ -o ./build/out main.cpp

