#include <iostream>

class Empty{

};

class Demo{
private:
    int id_;
    std::string name_;
protected:
    int age_;
public:
    int count_;
    Demo(){}
   // Demo(int id, std::string name, int age) : id_(id), name_(name),age_(age){}

    void set_id(int id)
    {
        id_ = id;
    }

    void set_age(int age)
    {
        age_ = age;
    }

    void set_name(std::string name)
    {
        name_ = name;
    }

    int get_id() const{
        return id_;
    }

    std::string get_name() const{
        return name_;
    }

    void display(){
        std::cout << id_ << " " << name_ << " " << age_<< " "<< count_ <<std::endl;
    }   
};


class Example{
    static int count_;
public:   
    Example(){
        count_ += 1;
    }
    static int get_count(){   
        // static methods can only access static members of the class
        return count_;
    }

    void display(){
        std::cout << "count " << count_ << std::endl;
    }

};

int Example::count_ = 0;

int main(void){
    Empty e;
    std::cout << "size of empty class : " << sizeof(e) << std::endl;

    Demo d;
    d.set_id(1);
    d.set_name("Demo");
    d.set_age(18);
    d.display();
    //_____________access specifiers
    // d.id_ = 10;                // @compiler error declared private here
    // d._name_  = "devilal";     // @compiler error declared private here
    // d.age_ = 20;               // @compiler error declared protected here
    d.count_ = 10;                // can be accessed because it is public  
    d.display();

    //_____________ static members and methods
    Example ex;
    Example ex1;
    ex.display();
    std::cout << "count " << Example::get_count() << std::endl; //can be accessed without creating an object because it is static
    return 0;

}

//g++ -o out  main.cpp -Wall