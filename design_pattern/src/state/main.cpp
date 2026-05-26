#include <iostream>
#include <chrono>
#include <memory>

class TemperatureSensor{
public:
    float readTemperature(){
        return 30.5f;
    }
};

class PressureSensor{
public:
    float readPressure(){
        return 30.5f;
    }
};

class Logger{
public:
    void log(const char *msg){
        std::cout<<"[log]: " << msg << std::endl;
    }
};

class FirmwareModule;

class SystemState{
public:
    virtual ~SystemState() = default;
    virtual void handle(FirmwareModule& fm) = 0;
    virtual const char *getName() = 0;
};

class FirmwareModule{
private:
    std::unique_ptr<SystemState> current_state;
    
public:
    TemperatureSensor temperature_sensor;
    PressureSensor pressure_sensor;
    Logger loger;

    void change_state(std::unique_ptr<SystemState> ns){
        std::cout << "\n====== current state : " \
        <<  (current_state ? current_state->getName() : "None" )\
        << " --> new state : " << (ns->getName())<< std::endl; 
        current_state = std::move(ns);
    }
    void run()
    {
        if(current_state)
            current_state->handle(*this);
    }   
};


class startupState : public SystemState{
public:
    void handle(FirmwareModule& fm) override;

    const char *getName(){
        return "Start Up State";
    }
};


class ReadState : public SystemState{
public:
    void handle(FirmwareModule& fm) override;

    const char *getName(){
        return "Read State";
    }
};



class FaultState : public SystemState{
public:
    void handle(FirmwareModule& fm) override;
    const char *getName(){
        return "Fault Data State";
    }
};


class ShutDown : public SystemState{
public:
    void handle(FirmwareModule& fm) override;
    const char *getName(){
        return "shut down State";
    }
};

void startupState::handle(FirmwareModule& fm){
    fm.loger.log("Initializing system");
};

void ReadState::handle(FirmwareModule& fm){
    fm.loger.log("Read data start");
    float temp = fm.temperature_sensor.readTemperature();
    float pressure = fm.pressure_sensor.readPressure();
    std::cout<< "temperature "<<temp << " pressure "<<pressure<<std::endl;
    fm.loger.log("Read data Done");
};

void FaultState::handle(FirmwareModule& fm){
    fm.loger.log("Fault state");
};

void ShutDown::handle(FirmwareModule& fm){
    fm.loger.log("shutdown state");
};


int main()
{
    FirmwareModule fm;
    fm.change_state(std::make_unique<startupState>());
    fm.run();
    fm.change_state(std::make_unique<ReadState>());
    fm.run();
    fm.change_state(std::make_unique<FaultState>());
    fm.run();
    fm.change_state(std::make_unique<ShutDown>());
    fm.run();
}

// mkdir build
// g++ -o ./build/out main.cpp
