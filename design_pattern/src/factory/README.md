# Factory Pattern Example in C++

This folder contains a small C++ example that demonstrates the Factory design pattern using runtime polymorphism and smart pointers.

## Factory design pattern

The Factory design pattern provides a way to create objects without exposing the creation logic to the client. In this example, the `factory` class centralizes object creation and returns a common interface type (`Icar`), so the client code does not need to know which concrete car class is being instantiated.

This improves flexibility, reduces coupling, and makes it easier to add new product types later.

## Overview

- `src/factory/main.cpp` contains the example code.
- `Icar` is the abstract interface for cars.
- `bmwx` and `bmwy` are concrete implementations.
- `factory::getCar(int type)` creates and returns a `std::unique_ptr<Icar>`.

## What it shows

- Use of an abstract base class (`Icar`) for runtime polymorphism.
- Concrete implementations that override `color()` and `max_speed(int)`.
- A simple factory that centralizes object creation.
- Ownership via `std::unique_ptr` for safe memory management.

## Source behavior

The example currently does the following:

1. Calls `factory::getCar(1)`.
2. Prints the selected car color.
3. Prints the runtime type name using `typeid`.

## Build

From the repository root:

```bash
g++ src/factory/main.cpp -o factory_example -std=c++17
```

## Run

```bash
./factory_example
```

On Windows:

```powershell
.actory_example.exe
```

## Notes

- `factory::getCar(1)` returns a `bmwx` instance.
- `factory::getCar(2)` returns a `bmwy` instance.
- To add a new car type:
  1. Add a new class implementing `Icar`.
  2. Add a new `case` in `factory::getCar(int type)`.

## Improvements

- The example can be extended to use configuration or command-line input.
- `max_speed(int)` is defined but not currently used in `main()`.
