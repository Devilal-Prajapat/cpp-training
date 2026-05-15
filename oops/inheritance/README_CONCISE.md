# Inheritance and Polymorphism in C++

This project demonstrates inheritance, method overriding, virtual functions (polymorphism), and abstract classes.

## Concepts

### 1. Basic Inheritance
A derived class inherits members and methods from a base class using `:` operator.

```cpp
class Derived : public Base {
};
```

**Constructor/Destructor Order:**
- Construction: Base → Derived
- Destruction: Derived → Base

### 2. Method Overriding
Derived class can redefine methods inherited from the base class.

```cpp
class Base {
    void display() { std::cout << "Base\n"; }
};

class Derived : public Base {
    void display() { std::cout << "Derived\n"; }  // Overrides Base method
};
```

### 3. Virtual Functions (Polymorphism)
Virtual functions enable **runtime polymorphism** - the correct method is called based on the actual object type, not the pointer type.

```cpp
class Base {
    virtual void show() { std::cout << "Base\n"; }
};

class Derived : public Base {
    void show() override { std::cout << "Derived\n"; }  // Overrides virtual method
};

Base* ptr = new Derived();
ptr->show();  // Calls Derived::show() (correct due to virtual)
```

**Non-virtual vs Virtual Comparison:**
```cpp
Base* ptr = &d;
ptr->display();  // Calls Base::display (NOT virtual - static binding)
ptr->show();     // Calls Derived::show (virtual - dynamic binding)
```

### 4. Abstract Base Classes
Abstract classes define interfaces that derived classes must implement.

```cpp
class BaseI {
public:
    virtual void show() = 0;  // Pure virtual - must be implemented by derived classes
    virtual ~BaseI() = default;
};

// BaseI obj;  // ❌ Error: cannot instantiate abstract class

class Demo : public BaseI {
public:
    void show() override { }  // ✅ Implements pure virtual method
};
```

Used with pointers/references:
```cpp
BaseI* ptr = new Demo();  // ✅ OK: using base class pointer
ptr->show();
```

### 5. The `override` Keyword (C++11)
Explicitly marks a method as overriding a virtual method from the base class.

```cpp
void show() override { }  // Compiler verifies virtual method exists in base
```

Benefits: Catches typos and makes intent clear.

## How Virtual Functions Work

Virtual functions use **Virtual Method Tables (vtable)**:

1. Each class with virtual functions gets a vtable (array of function pointers)
2. Each object has a hidden vptr (virtual pointer) pointing to its class's vtable
3. At runtime, the program looks up the correct function in the vtable
4. This enables dynamic dispatch based on actual object type

**Performance:** Small overhead (pointer dereference) but enables polymorphism.

## Inheritance Modes

```cpp
class Derived : public Base { };      // Public - members keep their access level
class Derived : protected Base { };   // Protected - public members become protected
class Derived : private Base { };     // Private - all members become private
```

## Best Practices

1. Mark destructors as virtual in polymorphic classes to prevent resource leaks
2. Use `override` keyword for clarity and error catching
3. Prefer abstract classes for defining interfaces
4. Keep inheritance hierarchies simple and shallow
5. Prefer composition over inheritance when applicable

## Compilation and Execution

```bash
g++ -o out main.cpp
./out
```

**Expected Output:**
```
Base class constructor called
Derived class constructor called
Base class display function
Derived class display function
Base class display function
Derived class show function
BaseDemo show called
DerivedDemo show called
Derived class destructor called
Base class destructor called
```

## Key Takeaways

| Concept | Purpose |
|---------|---------|
| **Inheritance** | Code reuse, hierarchical relationships |
| **Virtual Functions** | True polymorphism via dynamic binding |
| **Abstract Classes** | Define contracts/interfaces |
| **override keyword** | Explicit overriding with compile-time checking |

## References

- [cppreference - Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [cppreference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [cppreference - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
