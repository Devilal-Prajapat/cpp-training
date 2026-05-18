# RAII (Resource Acquisition Is Initialization)

## Overview

RAII is a fundamental C++ programming technique that ties the lifecycle of a resource (memory, file handles, database connections, etc.) to the lifetime of an object. Resources are acquired in the constructor and automatically released in the destructor.

## Key Concept

**"Resources are tied to object lifetime"** — When an object is created, resources are acquired. When the object is destroyed (goes out of scope), resources are automatically released.

## Benefits

- **Automatic resource cleanup**: No manual deallocation needed
- **Exception safety**: Resources are released even if an exception occurs
- **Prevention of memory leaks**: Eliminates forgot-to-delete bugs
- **Clear ownership**: Resources are owned by specific objects

## Code Example

### Without RAII (Manual Management)

```cpp
// Manual allocation - prone to memory leaks
int *ptr = new int[10];
ptr[0] = 5;
delete[] ptr; // Easy to forget, especially with exceptions
```

### With RAII

```cpp
class Resource {
private:
    int *ptr;
    int size;
public:
    // Constructor: Acquire resource
    Resource(int sz) : size(sz) {
        ptr = new int[size];
        std::cout << "Resource acquired." << std::endl;
    }
    
    // Destructor: Release resource
    ~Resource() {
        delete[] ptr;
        std::cout << "Resource released." << std::endl;
    }
};

// Usage
{
    Resource res(10); // Constructor called - resource acquired
} // Destructor called - resource automatically released
```

## Why RAII Matters

### Problem: Memory Leak with Exceptions

```cpp
try {
    int *ptr = new int[10];
    throw std::runtime_error("Error!"); // Exception thrown
    delete[] ptr; // This line never executes - MEMORY LEAK!
} catch (const std::exception &e) {
    // Memory is leaked here
}
```

### Solution: RAII Handles Exceptions

```cpp
try {
    Resource res(10); // Resource acquired
    throw std::runtime_error("Error!"); // Exception thrown
} catch (const std::exception &e) {
    // Destructor still called - resource properly released!
}
```

## Running the Example

```bash
cd /workspace/RAII
cmake -B build
cd build
make
./singleton
```

## Key Takeaways

1. **Constructors acquire resources**: Use initialization lists and constructor bodies to allocate
2. **Destructors release resources**: Use destructors to deallocate and cleanup
3. **Automatic cleanup on scope exit**: Works with normal returns, exceptions, or exits
4. **No manual management**: Eliminates the need to remember to delete/close/unlock resources

## Modern C++ Alternative

Consider using **smart pointers** for even safer resource management:

```cpp
std::unique_ptr<int[]> ptr(new int[10]); // Automatic cleanup
std::shared_ptr<Resource> res = std::make_shared<Resource>(10);
// All cleanup handled automatically
```

---

This is a fundamental concept in C++ that makes code safer, more maintainable, and less prone to resource leaks.
