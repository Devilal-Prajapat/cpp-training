# C++ Casting Examples

## Overview

This small example demonstrates different C++ cast types and object-oriented casting patterns:

- `static_cast` — compile-time conversion between related types
- `dynamic_cast` — safe downcasting in class hierarchies using RTTI
- `const_cast` — adding/removing `const` (use with extreme care)
- `reinterpret_cast` — low-level reinterpreting of bit patterns

The example also shows upcasting via a base class pointer and virtual dispatch.

## Files

- `main.cpp` — Contains demonstrations of the casts and a simple `Animal`/`Dog`/`Cat` hierarchy.

## What the program does

- Converts between `int` and `double` using `static_cast`.
- Upcasts a `Dog*` to `Animal*` and calls a virtual method.
- Attempts safe downcasts using `dynamic_cast` to `Dog*` and `Cat*`.
- Uses `const_cast` to remove `const` (demonstrates undefined behavior risk).
- Uses `reinterpret_cast` to convert between `void*` and `int*`.

## Build and run

From the `cast` directory build and run with:

```bash
cd /workspace/cast
g++ -o out main.cpp
./out
```

## Safety notes

- `dynamic_cast` returns `nullptr` on failure when casting pointers — always check the result before use.
- `const_cast` can produce undefined behavior if you modify an originally `const` object; avoid it unless you know what you're doing.
- `reinterpret_cast` is implementation-defined and should be limited to low-level code where necessary.
- Prefer safer alternatives (smart pointers, references, well-defined APIs) over unsafe casts.

## Learning goals

- Understand when to use each C++ cast operator
- See runtime behavior differences between upcasting and downcasting
- Recognize language constructs that can lead to undefined behavior and how to avoid them

---

This example is for educational purposes; it intentionally shows unsafe operations to illustrate risks. Make sure to follow best practices in production code.
