# Inheritance and Polymorphism in C++

This project demonstrates key inheritance concepts in C++, including single inheritance, method overriding, virtual functions (polymorphism), and abstract classes.

## Concepts Demonstrated

### 1. Basic Inheritance

Inheritance allows a derived (child) class to inherit members and methods from a base (parent) class.

**Key Points:**
- `:` operator is used to indicate inheritance
- `public` specifies the type of inheritance (public, protected, private)
- Derived class inherits all members and methods from Base class
- Constructors and destructors are called in order: Base → Derived

### 2. Constructor and Destructor Chaining

When an object of derived class is created or destroyed, both constructors/destructors execute in sequence.

**Construction Order:** Base constructor → Derived constructor
**Destruction Order:** Derived destructor → Base destructor

### 3. Method Overriding

A derived class can redefine a method inherited from the base class.

### 4. Virtual Functions and Polymorphism

Virtual functions enable **runtime polymorphism** - the correct method is called based on the object's actual type, not the pointer/reference type.

**Why Use Virtual Functions?**
- Enables true polymorphic behavior
- Calls the correct method based on actual object type
- Enables writing flexible, reusable code
- Foundation for loose coupling between classes

#### The `override` Keyword (C++11)
The `override` keyword explicitly states that a method overrides a virtual method from the base class.

**Benefits:**
- Prevents accidental misspellings in method names
- Makes intent clear to code readers
- Catches errors at compile time

### 5. The Difference: display() vs show()

In the example code, there are two methods that work differently:

**Why the difference?**
- `display()` is NOT virtual → binding is static (compile time)
- `show()` IS virtual → binding is dynamic (runtime)

| Method | Virtual | Type | Result |
|--------|---------|------|--------|
| `display()` | ❌ No | Static binding | Base method called |
| `show()` | ✅ Yes | Dynamic binding | Derived method called |

### 6. Abstract Base Classes

An abstract class is a class that cannot be instantiated. It serves as a blueprint and must be inherited.

**Pure Virtual Function (`= 0`):**
- Has no implementation in the base class
- Must be implemented by derived classes
- Makes the class abstract (cannot create objects of it)

**Compiling Abstract Classes:**
- Cannot instantiate an abstract class
- Must implement all pure virtual methods in derived classes
- Can use pointers/references to abstract classes

### 7. Using Abstract Base Classes for Polymorphism

Abstract classes are commonly used to define interfaces that derived classes must implement.

## Key OOP Concepts

### 1. Inheritance
- Enables code reuse
- Creates hierarchical relationships
- Derived class extends base class functionality

### 2. Polymorphism
- "Many forms" - same interface, different behaviors
- Achieved through virtual functions and method overriding
- Enables writing generic code that works with different types

### 3. Abstract Base Classes
- Define contracts that derived classes must fulfill
- Cannot be instantiated
- Enforce consistent interface across multiple implementations

### 4. Virtual Destructors
**Why Virtual Destructors?** - Ensures both derived and base destructors are called when deleting via base class pointer. Without virtual destructor, only base destructor is called, causing resource leaks.

## Inheritance Modes

### 1. Public Inheritance
- Public members of Base remain public in Derived
- Protected members of Base remain protected in Derived
- Private members of Base are not accessible in Derived

### 2. Protected Inheritance
- Public and protected members of Base become protected in Derived

### 3. Private Inheritance
- All members of Base become private in Derived

## Best Practices

1. **Use `virtual` for polymorphic methods** - Be explicit about intended behavior
2. **Mark virtual destructors** - Prevents resource leaks in inheritance hierarchies
3. **Use `override` keyword** - Catches accidental method signature changes
4. **Use abstract classes for interfaces** - Define contracts clearly
5. **Prefer composition over inheritance** - When applicable, use "has-a" over "is-a"
6. **Keep inheritance hierarchies shallow** - Complex hierarchies are hard to maintain
7. **Use virtual functions judiciously** - There's a small runtime cost

## Virtual Function Mechanism (Vtable and Vptr)

### Virtual Pointer (Vptr)
Every object of a class with virtual functions has a hidden **vptr** (virtual pointer):
- Automatically added by the compiler
- Points to the class's virtual method table
- Initialized in the constructor
- Takes 4-8 bytes per object (size of a pointer)

### Virtual Method Table (Vtable)
Each class with virtual functions gets a static **vtable** (virtual method table):
- Array of function pointers, one for each virtual method
- Shared by all instances of the class
- Each derived class has its own vtable with overridden methods
- Lives for the entire program lifetime

### Memory Layout Diagram

**Base Object:**
```
┌──────────────────────────┐
│    vptr ─────────────────┼──┐
├──────────────────────────┤  │
│   member variables       │  │
└──────────────────────────┘  │
                              │
                              ▼
                    ┌──────────────────────┐
                    │  Base::vtable        │
                    ├──────────────────────┤
                    │ &Base::show()    [0] │
                    ├──────────────────────┤
                    │ &Base::display() [1] │
                    ├──────────────────────┤
                    │ &Base::~Base()   [2] │
                    └──────────────────────┘
```

**Derived Object:**
```
┌──────────────────────────┐
│    vptr ─────────────────┼──┐
├──────────────────────────┤  │
│   member variables       │  │
└──────────────────────────┘  │
                              │
                              ▼
                    ┌──────────────────────┐
                    │ Derived::vtable      │
                    ├──────────────────────┤
                    │ &Derived::show() [0] │  (overridden)
                    ├──────────────────────┤
                    │ &Base::display() [1] │  (not overridden)
                    ├──────────────────────┤
                    │ &Derived::~Derived() │
                    │              [2]     │  (overridden)
                    └──────────────────────┘
```

### Base Pointer to Derived Object

```
Scenario: Base* ptr = new Derived();

Pointer Type: Base*
Actual Object: Derived

When calling ptr->show():

┌─────────────────┐
│  Base* ptr      │
│   (points to)   │
│                 │
│    ▼            │
│ ┌────────────┐  │
│ │ Derived obj│  │
│ ├────────────┤  │
│ │ vptr ──────┼──┼──┐
│ │ members    │  │  │
│ └────────────┘  │  │
│                 │  │
│        vptr─────┘  │ Follow vptr
│        looks at    │ (NOT ptr type!)
│        Derived:: ◄─┤
│        vtable      │
│                 │
└─────────────────┘

Result: Derived::show() is called! ✓ (not Base::show())
```

### How Runtime Method Resolution Works
When you call a virtual function via a base class pointer:

1. Follow the object's **vptr** to find its vtable
2. Look up the virtual method in the vtable
3. Call the function address found in the vtable

**Step-by-Step:**
```
Base* ptr = new Derived();
ptr->show();

Step 1: Look at ptr→vptr
        ptr is Base*, but object is Derived
        vptr points to Derived::vtable (not Base::vtable!)

Step 2: In Derived::vtable, find show() at index [0]
        show() entry = &Derived::show

Step 3: Call &Derived::show()  ← Correct method!
```

### Key Differences: Static vs Dynamic Binding
- **Static Binding (non-virtual):** Method determined at compile time
- **Dynamic Binding (virtual):** Method determined at runtime via vtable lookup

**Performance:** Small overhead (one pointer dereference) enables true polymorphism

## Compilation and Execution

Run: `g++ -o out main.cpp && ./out`

## Inheritance vs Composition

**Inheritance ("is-a"):** Use for IS-A relationships (e.g., Car IS-A Vehicle)

**Composition ("has-a"):** Use for HAS-A relationships (e.g., Car HAS-A Engine)

**Guideline:** Prefer composition unless there's a clear IS-A relationship.

## Related Concepts

- **Method Resolution Order (MRO)** - How methods are resolved in inheritance hierarchies
- **Multiple Inheritance** - Inheriting from multiple base classes
- **Virtual Base Classes** - Used in multiple inheritance to avoid duplication
- **RTTI (Run-Time Type Information)** - Determining object type at runtime
- **Type Casting** - `dynamic_cast` for safe polymorphic casting

## References

- [cppreference - Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [cppreference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [cppreference - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [cppreference - Destructors](https://en.cppreference.com/w/cpp/language/destructor)
- [cppreference - Override Specifier](https://en.cppreference.com/w/cpp/language/override)
