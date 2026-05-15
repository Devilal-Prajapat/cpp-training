#include <iostream>

int g_Var = 10;   // @note: this will be go in [ .data section]
int g_uninit;    // @note: this will be go in [ .bss section]
const int g_const = 5; // @note: this will be go in [ .ro section]
static int g_static_var;

void fun(int *p_var){
    static int static_var = 3;  // @note: this will be go in [ .data section]
    int a = 6;                  // @note: this will be go in [ stack section]
    int *heap_var = new int;     // @note: heap_var be go in [ stack section] 
                                // but memory address pointed by this in [ heap section ]
    *heap_var = 7;
    static_var += 1;
    std::cout << "============================\n";
    std::cout<< "heap_var " << *heap_var << '\n';
    std::cout<< "static_var " << static_var << '\n';
    std::cout<< "a "<< a << '\n';
    p_var = heap_var; // @note for p_var, we can change the value,but can't assign the new address as p_var is local function arg;
    delete heap_var;
    heap_var = nullptr;
}

int main(){
    int x = 5;     // @note: this will be go in [ stack section]
    int *ptr = &x; // @note: this will be go in [ stack section]
    std::cout << "before x " << x << " *ptr " << *ptr << '\n';
    *ptr = 100;    //@note: 100 will go in code section
    std::cout << "after x " << x << " *ptr " << *ptr << '\n';
    fun(ptr);
    fun(ptr);
    std::cout << "after fun x " << x << " *ptr " << *ptr << '\n';
    return 0;   
}

/*
#==================================================#
#                code/text section                 #
#==================================================#
#                .ro  section                      #   [constat data]  // g_const
#==================================================#
#                data section                      #   [ all initialized global and static data]  // g_Var, static_var
#==================================================#
#                .bss section                      #   [ all uninitialized global and static data] // g_static_var, g_uninit
#==================================================# 
#                heap section                      #   [ dyanmically alloacted data ] // memory allocated by new keyword
#==================================================#
#                stack section                     #   [ all local variable, function parameter] // x, ptr, a, heap_var,
#==================================================#

*/

// g++ -o memory_map main.cpp

