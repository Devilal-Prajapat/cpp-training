# WSL CPP Container

A small C++ repository demonstrating design pattern examples with CMake-based selection.

## Description

This repository contains multiple design pattern samples implemented in C++ using modern language features such as smart pointers and interfaces.

The patterns currently included are:
- `singleton` — single instance access
- `observer` — subject/observer event notification
- `factory` — object creation through a factory method

Each pattern is implemented in its own source folder under `src/`.

## Repository structure

- `CMakeLists.txt` — build configuration with `PATTERN` selection
- `src/singleton/main.cpp` — singleton pattern example
- `src/observer/main.cpp` — observer pattern example
- `src/factory/main.cpp` — factory pattern example
- `src/singleton/README.md` — singleton documentation
- `src/observer/README.md` — observer documentation
- `src/factory/README.md` — factory documentation

## Build with CMake

From the repository root, create a build folder and configure the desired pattern:

```bash
mkdir -p build
cd build
cmake -DPATTERN=singleton ..
cmake --build .
```

Replace `singleton` with `observer` or `factory` to build the corresponding demo.

## Run

From the `build` directory:

```bash
./singleton
```

Or for the other patterns:

```bash
./observer
./factory
```

On Windows:

```powershell
.
```

and run the executable from the build folder.

## Notes

- The `CMakeLists.txt` file selects the demo using the `PATTERN` cache variable.
- If no valid pattern is provided, CMake will report an error.
- The `builder` pattern is referenced in `CMakeLists.txt` but is not currently present in the source tree.

## Docker

This repository also includes a `Dockerfile` and `docker-compose.yaml` for container-based workflows, but the primary build method is CMake.
