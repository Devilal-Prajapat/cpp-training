# Thread Pool Example

This small example demonstrates a simple C++ thread pool implementation using
`std::thread`, `std::mutex`, `std::condition_variable`, and a task queue.

## Features

- Fixed-size thread pool (configured in `main.cpp`).
- Safe task enqueueing with a condition variable.
- Graceful shutdown via `stop()` and destructor.

## Files

- `main.cpp` — example program and `ThreadPool` implementation.

## Build

From the `thread-pool` directory:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
```
or
```bash
    cmake -B build .
    cmake --build build --config debug
```

This will generate the executable under the `build/` directory (e.g. `build/app`).

## Run

From the `thread-pool` directory run:

```bash
./build/app
```

## Usage

The example creates a `ThreadPool` with a hardcoded thread count (`ThreadPool(2)`).
To change the pool size or tasks, edit `main.cpp` and rebuild.

## Notes

- The implementation uses a condition variable to avoid busy-waiting.
- Tasks are stored as `std::function<void()>` and moved into the queue.
- The pool shuts down cleanly by notifying all worker threads.


