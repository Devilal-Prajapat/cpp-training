#include <iostream>
#include <vector>
#include <algorithm>

enum class EventType{
    MEASUREMENT,
    BATTLOW
};

class EventData{
    public:
    EventType ev;
    std::string name;
};

class Iobserver{
 public:
    virtual ~Iobserver() = default;
 virtual void onnotication(EventData &e) = 0;
};

class displayObs: public Iobserver{
    public:
    void onnotication(EventData &e){
        switch(e.ev){
            case EventType::MEASUREMENT:
                std::cout << e.name << std::endl;
                break;
            case EventType::BATTLOW:
                std::cout << e.name << std::endl;
                break;
            default:
            break;
        }
    //std::cout << "disp obs" << std::endl;
    }
};


class buzzerobs: public Iobserver{
    public:
    void onnotication(EventData &e){
        switch(e.ev){
            case EventType::MEASUREMENT:
                std::cout << e.name << " beep "<< std::endl;
                break;
            case EventType::BATTLOW:
                std::cout << e.name << " beep beep beeep "<<std::endl;
                break;
            default:
            break;
        }
    //std::cout << "disp obs" << std::endl;
    }
};

class Isubject{
 public:
    virtual ~Isubject() = default;
 virtual void notify(EventData &e) = 0;
};

class Sensor: public Isubject{
private:
 std::vector<Iobserver *> observer;
 public:
    Sensor(){};
    void attach(Iobserver* obs){
        observer.push_back(obs);
    }
    void deattach(Iobserver* obs){
        observer.erase(
            std::remove(observer.begin(),
                        observer.end(),
                        obs),
            observer.end());

    }
 
    void read_data(){
        EventData e;
        e.ev= EventType::MEASUREMENT;
        e.name = "measurement event";
        notify(e);
        e.ev= EventType::BATTLOW;
        e.name = "batt low event";
        notify(e);
    }
    
    void notify(EventData &e)
    {
        for(auto *r :observer)
        {
             r->onnotication(e);
        }
    }
};

int main(){

    Sensor s;
    displayObs disp;
    buzzerobs bobs;
    s.attach(&disp);
    s.attach(&bobs);
    s.read_data();
}
 