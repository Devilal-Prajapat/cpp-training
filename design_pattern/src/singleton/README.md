# Singleton Pattern Example in C++

This folder contains a C++ example that demonstrates the Singleton design pattern.

## Singleton design pattern

The Singleton design pattern ensures that a class has only one instance and provides a global point of access to that instance. It is useful when exactly one object is needed to coordinate actions across the system, such as a logger, configuration manager, or connection pool.

In this example, the `Logger` class uses a private constructor and a static `getInstance()` method to control object creation. The copy constructor and assignment operator are deleted so no additional copies can be created.

## Overview

- `src/singleton/main.cpp` contains the example code.
- `Logger` is the singleton class.
- `getInstance()` returns the shared singleton instance.
- `log()` writes a message to `std::cout`.

## What it shows

- Private constructor to prevent direct construction.
- Deleted copy constructor and assignment operator to prevent duplication.
- Static instance pointer and lazy initialization.
- Global access through `Logger::getInstance()`.

## Source behavior

The example currently does the following:

1. Calls `Logger::getInstance()`.
2. Logs a message using `Logger::log("Hello world from singleton")`.

## Build

From the repository root:

```bash
g++ src/singleton/main.cpp -o singleton_example -std=c++17
```

## Run

```bash
./singleton_example
```

On Windows:

```powershell
.\singleton_example.exe
```

## Notes

- The example uses a pointer-based singleton implementation.
- Only one `Logger` instance is created and reused.
- To switch to the reference-based singleton implementation, you can use the `#if 0` block in `main.cpp`.
