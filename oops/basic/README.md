# Object-Oriented Programming (OOP) Concepts

This project demonstrates fundamental Object-Oriented Programming concepts in C++, including access specifiers, class members, and static members/methods.

## Concepts Demonstrated

### 1. Empty Classes

An empty class with no members or methods still has a size in memory (typically 1 byte).

```cpp
class Empty {
};
```

**Output:** `size of empty class : 1`

This 1 byte is allocated to ensure that different instances of the empty class have different addresses in memory.

### 2. Access Specifiers

Access specifiers control the visibility and accessibility of class members from outside the class.

#### Private Members
- **Visibility:** Only accessible within the class itself
- **Use case:** Hide internal implementation details
- **Example:** `id_`, `name_` in the `Demo` class

```cpp
class Demo {
private:
    int id_;
    std::string name_;
    // ❌ Cannot be accessed from outside the class
    // d.id_ = 10;              // Compiler error
    // d.name_ = "example";     // Compiler error
};
```

#### Protected Members
- **Visibility:** Accessible within the class and derived classes (inheritance)
- **Use case:** Allow subclasses to access internal data
- **Example:** `age_` in the `Demo` class

```cpp
class Demo {
protected:
    int age_;
    // ❌ Cannot be accessed from outside the class (even in main)
    // d.age_ = 20;             // Compiler error
    // ✅ Can be accessed by derived classes
};
```

#### Public Members
- **Visibility:** Accessible from anywhere
- **Use case:** Provide interface to interact with the class
- **Example:** `count_` in the `Demo` class

```cpp
class Demo {
public:
    int count_;
    // ✅ Can be accessed from anywhere
    d.count_ = 10;              // OK
};
```

### 3. Getters and Setters (Encapsulation)

Methods used to safely access and modify private data members while maintaining control over validation and constraints.

```cpp
void set_id(int id) {
    id_ = id;
}

int get_id() const {
    return id_;
}
```

**Benefits:**
- **Validation:** Can check data validity before setting
- **Flexibility:** Can add logic without changing the interface
- **Maintainability:** Internal representation can change without affecting external code
- **const correctness:** `get_id()` is marked `const` because it doesn't modify the object

### 4. Static Members

Static members belong to the class itself, not to individual objects. All instances share a single copy.

```cpp
class Example {
    static int count_;
public:
    Example() {
        count_ += 1;  // Shared across all instances
    }
};

int Example::count_ = 0;  // Must be initialized outside the class
```

**Characteristics:**
- Declared with `static` keyword
- Initialized outside the class definition
- Shared by all instances
- Lives for the entire program lifetime
- Useful for tracking class-level information

### 5. Static Methods

Static methods operate on static members and can be called without creating an object.

```cpp
class Example {
    static int count_;
public:
    static int get_count() {
        return count_;  // ✅ Can only access static members
    }
};

// Can be called without creating an object
std::cout << Example::get_count();
```

**Important Rules:**
- Can only access static members
- Cannot access instance members (`this` pointer is not available)
- Called using the class name (`::`), not an object

### 6. The Demo Class

The `Demo` class demonstrates all concepts together:

```cpp
class Demo {
private:
    int id_;                    // Private - hidden from outside
    std::string name_;          // Private - hidden from outside
protected:
    int age_;                   // Protected - hidden but accessible to subclasses
public:
    int count_;                 // Public - accessible from anywhere
    Demo() {}                   // Default constructor
    
    // Setters - control how data is modified
    void set_id(int id) { id_ = id; }
    void set_age(int age) { age_ = age; }
    void set_name(std::string name) { name_ = name; }
    
    // Getters - provide controlled access to data
    int get_id() const { return id_; }
    std::string get_name() const { return name_; }
    
    // Display method
    void display() {
        std::cout << id_ << " " << name_ << " " << age_ << " " << count_ << std::endl;
    }
};
```

## Code Walkthrough

### Access Specifiers Demonstration
```cpp
Demo d;
d.set_id(1);              // ✅ Public method
d.set_name("Demo");       // ✅ Public method
d.set_age(18);            // ✅ Public method
d.display();

// d.id_ = 10;            // ❌ Error: private member
// d.name_ = "demo";      // ❌ Error: private member
// d.age_ = 20;           // ❌ Error: protected member
d.count_ = 10;            // ✅ OK: public member
```

### Static Members and Methods
```cpp
Example ex;               // First instance - count becomes 1
Example ex1;              // Second instance - count becomes 2
ex.display();             // Displays "count 2"
std::cout << Example::get_count();  // Displays "2"
```

## Key OOP Principles

### 1. Encapsulation
- Bundle data (members) and methods together
- Hide internal details (private members)
- Provide controlled interface (public methods)

### 2. Data Hiding
- Use access specifiers to prevent unauthorized access
- Protect invariants and maintain consistency

### 3. Abstraction
- Methods like `get_id()` abstract away implementation details
- Users interact with a simplified interface

### 4. Reusability
- Base classes can be extended through inheritance (using `protected` members)
- Static members can be shared across all instances

## Best Practices

1. **Make members private by default** - Only make public what needs to be
2. **Use getters/setters** - Provides flexibility and validation
3. **Mark getters as `const`** - Indicates they don't modify the object
4. **Initialize static members outside the class** - Required in C++
5. **Use static for class-level information** - Counters, configurations, etc.
6. **Avoid public data members** - Use methods for better control

## Access Specifier Quick Reference

| Specifier | Class | Derived Class | Outside |
|-----------|-------|---------------|---------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

## Compilation and Execution

```bash
cd /workspace/oops
g++ -o out main.cpp
./out
```

**Expected Output:**
```
size of empty class : 1
1 Demo 18 10
1 Demo 18 10
count 2
count 2
```

## Related Concepts

- **Inheritance** - Extends the use of `protected` members
- **Polymorphism** - Works with access specifiers and virtual methods
- **Const Correctness** - Methods marked `const` promise not to modify state
- **Constructors and Destructors** - Initialize and clean up objects

## References

- [cppreference - Access specifiers](https://en.cppreference.com/w/cpp/language/access)
- [cppreference - Static](https://en.cppreference.com/w/cpp/language/static)
- [Encapsulation](https://en.cppreference.com/w/cpp/language/access#Explanation)
- [Class Members](https://en.cppreference.com/w/cpp/language/data_members)
