#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

class TrafficLight;

//-------------------------------------------------
// State Interface
//-------------------------------------------------
class State {
public:
    virtual void handle(TrafficLight* light) = 0;
    virtual ~State() = default;
};

//-------------------------------------------------
// Context Class
//-------------------------------------------------
class TrafficLight {
private:
    std::unique_ptr<State> currentState;

public:
    void setState(std::unique_ptr<State> state) {
        currentState = std::move(state);
    }

    void request() {
        currentState->handle(this);
    }
};
//-------------------------------------------------
// Concrete States
//-------------------------------------------------
class RedState : public State {
public:
    void handle(TrafficLight* light) override;
};

class GreenState : public State {
public:
    void handle(TrafficLight* light) override;
};

class YellowState : public State {
public:
    void handle(TrafficLight* light) override;
};

//-------------------------------------------------
// State Implementations
//-------------------------------------------------
void RedState::handle(TrafficLight* light) {
    std::cout << "RED Light - STOP" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    light->setState(std::make_unique<GreenState>());
}

void GreenState::handle(TrafficLight* light) {
    std::cout << "GREEN Light - GO" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    light->setState(std::make_unique<YellowState>());
}

void YellowState::handle(TrafficLight* light) {
    std::cout << "YELLOW Light - WAIT" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    light->setState(std::make_unique<RedState>());
}

//-------------------------------------------------
// Main
//-------------------------------------------------
int main() {

    TrafficLight trafficLight;

    trafficLight.setState(std::make_unique<RedState>());

    while (true) {
        trafficLight.request();
    }

    return 0;
}