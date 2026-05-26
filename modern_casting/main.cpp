#include <iostream>


class Base{
    public:
        virtual ~Base() = default;
        virtual void Show(){
            std::cout << "Base show " << std::endl;
        }

};

class Derived : public Base{
public:
    void Show() override{
        std::cout << "Derived show " << std::endl;
    }
};

class Derived2 : public Base{
public:
    void Show() override{
        std::cout << "Derived show " << std::endl;
    }
};

class foo{
    int a{0};
public:
    void display(){
        std::cout <<"foo "<< a << std::endl;
    }
};

class bar{
    double b{2.4};
public:
    void display(){
        std::cout <<"bar "<< b << std::endl;
    }
};


int main(void){
    float f_val{12.56712912};
    int i_val = (int)f_val;
    std::cout<< f_val << " "<< i_val<< std::endl;
    int i_val_modern = static_cast<int>(f_val);
    std::cout<< f_val << " "<< i_val_modern<< std::endl;

    //=========================================
    //  static_cast used for:
    //  standard conversions (e.g., int to float)
    //  upcasting (Derived* to Base*)
    //  downcasting (Base* to Derived*) - unsafe without runtime checks      

    Derived d;
    Base* b = static_cast<Base*>(&d);
    b->Show();  // This is upcasting and is safe because: every Derived IS-A Base
   
    // Base* b = new Derived();
    Derived* d1 = static_cast<Derived*>(b);
    d1->Show(); 
    // This compiles. BUT:
    // no runtime checking happens
    // dangerous if object is not actually Derived

    Derived* d2 = static_cast<Derived*>(b);   //down cast
    d2->Show(); 
    //  Undefined Behavior Program may:
    //  crash
    //  corrupt memory
    //  behave unpredictably

    //=========================================
    //dynamic_cast used for:
    // safe polymorphic downcasting
    // runtime type checking
    // Requires:
    // at least one virtual function in base class

    Base* b3 = new Derived();
    Derived* d3 = dynamic_cast<Derived*>(b3);
    if (d3) {
        std::cout << "Cast successful"<<std::endl;
        d3->Show();
    }

    // type check 
    Derived2 *d4 = dynamic_cast<Derived2*>(b3);
    if (d4) {
        std::cout << "Cast successful";
        d4->Show();
    }else{
        std::cout << "Cast Failed"<<std::endl;
    }

    //=========================================
    // reinterpret_cast
    // Used for:
    // low-level casts
    // pointer conversions
    // dangerous and non-portable   

    foo f;
    bar b_;
    foo *fptr = &f;
    bar *bptr = reinterpret_cast<bar *>(fptr);
    // bar *bptr = fptr; // compile time error: cannot convert foo* to bar* without a cast
    bptr->display();


    int a  = 10;
    const int *ptr = &a;
    std::cout<< "pointer to const int "<< (*ptr) << std::endl;
   // *ptr = 20 // compiler error;

    int *i_ptr = const_cast<int *>(ptr);

    std::cout<< "before "<< (*i_ptr) << std::endl;
    *i_ptr = 30;
    std::cout<< "before "<< (*i_ptr) << std::endl;



    return 0;
}

// mkdir build
// g++ -o ./build/out main.cpp -std=c++20 -lpthread -Werror