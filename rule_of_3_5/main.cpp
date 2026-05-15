#include <iostream>


class RuleOf3
{
private:
    int *ptr;
    int size;

public:
    RuleOf3(int sz):size(sz){
        std::cout << "RuleOf3 constructor "<< size << std::endl;
        ptr = new int[size];
        for(int i = 0;i<size; i++){
            ptr[i] = i;
        }
    }

    RuleOf3(const RuleOf3& obj):size(obj.size){
        std::cout << "RuleOf3 copy constructor "<< size << std::endl;
        ptr = new int[size];
        for(int i = 0;i<size; i++)
        {
            ptr[i] = obj.ptr[i];
        }
    }

    RuleOf3& operator=(const RuleOf3& obj){
        std::cout << "RuleOf3 copy assignment "<< std::endl;
        if(&obj != this){
            delete[] ptr;
            size = obj.size;
            ptr = new int[size];
            for(int i = 0;i<size; i++)
            {
                ptr[i] = obj.ptr[i];
            }
        }
        return *this;        
    }        
    ~RuleOf3(){
        std::cout << "RuleOf3 destructor "<< std::endl;
        delete [] ptr;
    }
};

class RuleOf5
{
private:
    int *ptr;
    int size;

public:
    RuleOf5(int sz):size(sz){
        std::cout << "RuleOf5 constructor "<< size << std::endl;
        ptr = new int[size];
        for(int i = 0;i<size; i++){
            ptr[i] = i;
        }
    }

    RuleOf5(const RuleOf5& obj):size(obj.size){
        std::cout << "RuleOf5 copy constructor "<< size << std::endl;
        ptr = new int[size];
        for(int i = 0;i<size; i++)
        {
            ptr[i] = obj.ptr[i];
        }
    }

    RuleOf5& operator=(const RuleOf5& obj){
        std::cout << "RuleOf5 copy assignment "<< size << std::endl;
        if(&obj != this){
            
            delete[] ptr;
            size = obj.size;
            ptr = new int[size];
            for(int i = 0;i<size; i++)
            {
                ptr[i] = obj.ptr[i];
            }
        }
        return *this;        
    }   

    RuleOf5(RuleOf5&& obj):size(obj.size),ptr(obj.ptr){
        std::cout << "RuleOf5 move constructor "<< size << std::endl;
        obj.ptr = nullptr;
        obj.size = 0;
    }

     RuleOf5& operator=(RuleOf5&& obj){
        std::cout << "RuleOf5 move assignment "<< size << std::endl;
        if(&obj != this){
            delete[] ptr;
            size = obj.size;
            ptr = obj.ptr;
            obj.ptr = nullptr;
            obj.size = 0;
            
        }
        return *this;    
    }

    ~RuleOf5(){
        std::cout << "RuleOf5 distructor "<< size << std::endl;
        delete [] ptr;
    }
};

int main(void){

    // RuleOf3 r1(5);
    // RuleOf3 r2 = r1; // copy constructor
    // RuleOf3 r3(10);
    // r3 =  r1;

    RuleOf5 r1(5);
    RuleOf5 r2 = r1; // copy constructor
    RuleOf5 r3(std::move(r2)); // move constructor
    RuleOf5 r4(1); // parameter construtcor
    r4=  std::move(r1); // move assignment
}