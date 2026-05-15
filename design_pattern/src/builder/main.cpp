#include <iostream>
class UartBuilder;

class IDriver{
public:
    virtual ~IDriver() = default;
    virtual void init() = 0;
    virtual void write(char c) = 0;
    virtual void read() = 0;
    virtual void display() = 0;
};

class UartManager: public IDriver{
private:
    int rx_pin_{};
    int tx_pin_{};
    int baud_rate_{};
    UartManager(){};
public:
    friend class UartBuilder;
    void init(){
        std::cout << "UartManager Init " << std::endl;
    }

    void write(char c)
    {
        std::cout << "UartManager write " << c << std::endl;
    }

    void read(){
        std::cout << "UartManager read "<< std::endl;        
    }

    void display(){
        std::cout<< "tx "<< tx_pin_ << " rx "<< rx_pin_ << " baud_rate "<< baud_rate_ << std::endl; 
    }
};


class SpiManager : public IDriver{
private:
    int rx_pin_{};
    int tx_pin_{};
    int ss_pin_{};
    int speed_{};
    SpiManager(){};
public:
    friend class SPIBuilder;
    void init(){
        std::cout << "SpiManager Init " << std::endl;
    }

    void write(char c)
    {
        std::cout << "SpiManager write " << c << std::endl;
    }

    void read(){
        std::cout << "SpiManager read "<< std::endl;        
    }

    void display(){
        std::cout<< "tx "<< tx_pin_ << " rx "<< rx_pin_ << " ss "<< ss_pin_ << " speed_ "<< speed_ << std::endl; 
    }
};

class SPIBuilder{
private:
    SpiManager spi_mgr;
public:
    SPIBuilder& add_rx_pin(int pin){
        spi_mgr.rx_pin_ = pin;
        return *this;
    }

    SPIBuilder& add_tx_pin(int pin){
        spi_mgr.tx_pin_ = pin;
        return *this;
    }

    SPIBuilder& add_speed(int speed){
        spi_mgr.speed_ = speed;
        return *this;
    }

    SPIBuilder& add_ss_pin(int pin){
        spi_mgr.ss_pin_ = pin;
        return *this;
    }


    SpiManager build(){
        return spi_mgr;
    }
};

class UartBuilder{
private:
    UartManager uart_mgr;
public:
    UartBuilder& add_rx_pin(int pin){
        uart_mgr.rx_pin_ = pin;
        return *this;
    }

    UartBuilder& add_tx_pin(int pin){
        uart_mgr.tx_pin_ = pin;
        return *this;
    }

    UartBuilder& add_baud_rate(int baud){
        uart_mgr.baud_rate_ = baud;
        return *this;
    }

    UartManager build(){
        return uart_mgr;
    }
};

class Director{
public:
    static UartManager create_default(){
        return UartBuilder().add_rx_pin(2).add_tx_pin(3).add_baud_rate(9600).build();
    }
    static UartManager create_high_speed(){
        return UartBuilder().add_tx_pin(2).add_baud_rate(115200).build();
    }
    static SpiManager create_default_spi(){
        return SPIBuilder().add_rx_pin(2).add_tx_pin(3).add_ss_pin(4).add_speed(1000000).build();
    }
    static SpiManager create_high_speed_spi(){
        return SPIBuilder().add_tx_pin(2).add_ss_pin(4).add_speed(10000000).build();
    }
};

int main(void){

    // direct usage of builder
    UartManager uartm = UartBuilder().add_rx_pin(2).add_tx_pin(3).add_baud_rate(9600).build();
    uartm.display(); 

    // usage of director    
    Director::create_high_speed().display();
    UartManager uart = Director::create_high_speed();
    uart.display();

    SpiManager spi = Director::create_default_spi();
    spi.display();
    return 0;   
}

//g++ -o main main.cpp -Wall