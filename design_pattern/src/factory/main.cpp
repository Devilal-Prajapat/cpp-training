#include <iostream>
#include <memory>
#include <typeinfo>

class Icar{
public:
    virtual ~Icar(){};
    virtual void color()= 0;
    virtual void max_speed(int s) = 0;
};

class bmwx: public Icar{
    private:
        int speed;
    public:
    void color(){
    std::cout<< "BMWX color "<< std::endl;
    }
     void max_speed(int s){
     std::cout<< "BMWX spedd "<<s << std::endl;
     }  
};

class bmwy: public Icar{
    private:
        int speed;
    public:
    void color(){
    std::cout<< "BMWy color "<< std::endl;
    }
     void max_speed(int s){
     std::cout<< "BMWy spedd "<<s << std::endl;
     }  
};

// class factory{
//     public:
//     static Icar* getCar(int type){
//         Icar *ptr;
//         switch(type){
//             case 1:
//                 ptr =  new bmwx;
//                 break;
//             case 2:
//                 ptr = new bmwy;
//                 break;
//             default:
//             ptr = nullptr;
//         }
//     return ptr;
//     }
// };

class factory{
    public:
    static std::unique_ptr<Icar> getCar(int type){
         switch(type){
            case 1:
                return std::make_unique<bmwx>();
                break;
            case 2:
                return std::make_unique<bmwy>();
                break;
            default:    
            return nullptr;            
         }
    }

};

int main(){
    // Icar *bmw = factory::getCar(1);
    // bmw->color();
    // std::cout << typeid(*bmw).name() << std::endl;
    // bmw = factory::getCar(2);
    // bmw->color();
    // std::cout << typeid(*bmw).name() << std::endl;

    // without factory
    // std::unique_ptr<Icar> bmw = std::make_unique<bmwx>();
    // bmw->color();
    // std::cout << typeid(*bmw).name() << std::endl;

    // with factory
    std::unique_ptr<Icar> bmw = factory::getCar(1);
    bmw->color();
    std::cout << typeid(*bmw).name() << std::endl;
    
    // bmw = std::move(factory::getCar(2));
    // bmw->color();
    // std::cout << typeid(*bmw).name() << std::endl;
    return 0;
}