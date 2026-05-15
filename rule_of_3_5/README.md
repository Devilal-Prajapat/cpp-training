# Rule of 3 and Rule of 5

This project demonstrates two important C++ design principles for managing resource allocation and deallocation in classes: the **Rule of 3** and the **Rule of 5**.

## Rule of 3

The **Rule of 3** states that if a class explicitly defines a **destructor**, **copy constructor**, or **copy assignment operator**, it should define all three.

### Why is this important?

When a class manages resources (like dynamically allocated memory), the compiler-generated default implementations are often insufficient. If you manually define one of these three special member functions, you typically need to define all three to properly manage your resources.

### The Three Members

1. **Destructor (~ClassName)**
   - Responsible for cleaning up resources (e.g., deallocating memory)
   - Called when an object is destroyed
   - Without it, resources leak

2. **Copy Constructor (ClassName(const ClassName&))**
   - Responsible for creating a new object as a copy of an existing object
   - Called when: `ClassName obj1 = obj2;`
   - Without it, a shallow copy is made (both objects share the same resources)

3. **Copy Assignment Operator (operator=)**
   - Responsible for assigning one object's data to another existing object
   - Called when: `obj1 = obj2;` (both objects already exist)
   - Without it, a shallow copy is made (potential resource leaks and double deletion)

### Example: RuleOf3 Class

The `RuleOf3` class in this project demonstrates proper implementation:

```cpp
class RuleOf3
{
private:
    int *ptr;
    int size;

public:
    // Destructor
    ~RuleOf3() {
        delete[] ptr;
    }

    // Copy Constructor
    RuleOf3(const RuleOf3& obj) {
        ptr = new int[obj.size];
        // Deep copy of data
    }

    // Copy Assignment Operator
    RuleOf3& operator=(const RuleOf3& obj) {
        delete[] ptr;  // Clean up old data
        ptr = new int[obj.size];
        // Deep copy of data
        return *this;
    }
};
```

## Rule of 5

The **Rule of 5** is an extension of the Rule of 3 introduced in C++11. It states that if a class explicitly defines a **destructor**, **copy constructor**, **copy assignment operator**, **move constructor**, or **move assignment operator**, it should define all five.

### Why do we need the Rule of 5?

With C++11 came the concept of move semantics, which allows us to efficiently transfer resources from temporary objects to new objects, avoiding expensive deep copies. The Rule of 5 ensures proper move semantics support.

### The Five Members

1-3. **Destructor, Copy Constructor, Copy Assignment Operator** (same as Rule of 3)

4. **Move Constructor (ClassName(ClassName&&))**
   - Transfers ownership of resources from a temporary/rvalue object to a new object
   - Called when: `ClassName obj = std::move(temp);`
   - Avoids deep copying by stealing resources from an object that's about to be destroyed
   - Much more efficient than copying

5. **Move Assignment Operator (operator=(ClassName&&))**
   - Transfers ownership of resources from a temporary/rvalue object to an existing object
   - Called when: `obj = std::move(temp);` (both objects already exist)
   - Allows efficient resource transfer

### Example: RuleOf5 Class

The `RuleOf5` class in this project demonstrates all five special member functions:

```cpp
class RuleOf5
{
public:
    // Destructor
    ~RuleOf5() {
        delete[] ptr;
    }

    // Copy Constructor
    RuleOf5(const RuleOf5& obj) {
        ptr = new int[obj.size];
        // Deep copy
    }

    // Copy Assignment Operator
    RuleOf5& operator=(const RuleOf5& obj) {
        // Deep copy
        return *this;
    }

    // Move Constructor
    RuleOf5(RuleOf5&& obj) {
        ptr = obj.ptr;
        obj.ptr = nullptr;  // Leave source in valid state
    }

    // Move Assignment Operator
    RuleOf5& operator=(RuleOf5&& obj) {
        delete[] ptr;
        ptr = obj.ptr;
        obj.ptr = nullptr;  // Leave source in valid state
        return *this;
    }
};
```

## Key Differences: Rule of 3 vs Rule of 5

| Aspect | Rule of 3 | Rule of 5 |
|--------|-----------|----------|
| **Era** | Pre-C++11 | C++11 and later |
| **Resource Transfer** | Only copying (expensive) | Both copying and moving (efficient) |
| **Temporary Objects** | Copies are made | Resources are stolen (moved) |
| **Performance** | Slower for temporary objects | Faster, especially with temporaries |
| **Members** | 3 | 5 |

## Practical Benefits of Move Semantics

Move semantics (Rule of 5) provides significant performance improvements:

- **Avoiding unnecessary copies**: Temporary objects don't need deep copies
- **Efficient container operations**: STL containers can move elements instead of copying
- **Better resource management**: Resources are transferred directly

## Building and Running

```bash
cd /workspace/rule_of_3_5
mkdir -p build
cd build
cmake ..
make
./ruleof3_5
```

The program outputs the special member function calls, demonstrating when each function is invoked during object creation and assignment.

## When to Use

- **Use Rule of 3**: When working with pre-C++11 code or when move semantics aren't needed
- **Use Rule of 5**: In modern C++11+ code for optimal performance and resource management

## Best Practices

1. **Always define all special members consistently** - Don't define some and rely on defaults for others
2. **Use `= default` and `= delete` explicitly** in modern C++ to be clear about your intentions
3. **Consider RAII principle** - Resource Acquisition Is Initialization
4. **Prefer smart pointers** - `std::unique_ptr` and `std::shared_ptr` often eliminate the need for manual special member function definitions
5. **Use move semantics** - Except when copying is required, prefer move operations for temporary objects

## References

- [cppreference - Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [cppreference - Move constructors](https://en.cppreference.com/w/cpp/language/move_constructor)
- [cppreference - Move assignment](https://en.cppreference.com/w/cpp/language/move_operator=)
