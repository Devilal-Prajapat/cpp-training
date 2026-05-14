# Observer Pattern Example in C++

This folder contains a small C++ example that demonstrates the Observer design pattern.

## Observer design pattern

The Observer design pattern defines a one-to-many dependency between objects so that when one object (the subject) changes state, all of its dependents (observers) are notified automatically. It decouples the subject from its observers and allows dynamic registration and removal of observer objects.

In this example, `Sensor` acts as the subject, while `displayObs` and `buzzerobs` act as observers. The observers subscribe to the subject and receive event notifications when the sensor reads new data.

## Overview

- `src/observer/main.cpp` contains the example implementation.
- `Iobserver` is the observer interface.
- `Isubject` is the subject interface.
- `Sensor` implements `Isubject` and sends event notifications to all attached observers.
- `displayObs` and `buzzerobs` implement `Iobserver` and react to events.

## What it shows

- Use of an abstract observer interface to define callback behavior.
- Subject maintains a list of observers and notifies them on state changes.
- Observers can be attached and detached dynamically.
- Events are delivered using `EventData` objects.

## Source behavior

The example currently does the following:

1. Creates a `Sensor` instance.
2. Attaches `displayObs` and `buzzerobs` observers.
3. Calls `Sensor::read_data()`.
4. The `Sensor` creates measurement and battery-low events and notifies attached observers.
5. Each observer prints a message based on the event type.

## Build

From the repository root:

```bash
g++ src/observer/main.cpp -o observer_example -std=c++17
```

## Run

```bash
./observer_example
```

On Windows:

```powershell
.\observer_example.exe
```

## Notes

- `EventType::MEASUREMENT` and `EventType::BATTLOW` are handled by both observers.
- `displayObs` prints event names.
- `buzzerobs` prints event names with beep notifications.
- To extend the example, add new observer classes or new event types.
