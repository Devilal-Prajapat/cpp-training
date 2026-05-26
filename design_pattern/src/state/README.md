# State Design Pattern

```text
+------------------+
|     Context      |
+------------------+
| - state: State   |
+------------------+
| + setState()     |
| + request()      |
+------------------+
          |
          | uses
          v
+------------------+
|      State       |<<interface>>
+------------------+
| + handle()       |
+------------------+
        / \
       /   \
      /     \
     v       v

+----------------------+     +----------------------+
|   ConcreteStateA     |     |   ConcreteStateB     |
+----------------------+     +----------------------+
| + handle()           |     | + handle()           |
+----------------------+     +----------------------+
           |                            |
           | state transition           |
           +----------------------------+
```

---

## Table of Contents

* Overview
* Diagram
* Explanation
* Workflow Example
* Example Structure
* Benefits
* Common Use Cases

---

## Overview

The State Design Pattern is a behavioral design pattern that allows an object to change its behavior when its internal state changes. The object appears to change its class dynamically.

---

## Diagram

```text
+------------------+
|     Context      |
+------------------+
| - state: State   |
+------------------+
| + setState()     |
| + request()      |
+------------------+
          |
          | uses
          v
+------------------+
|      State       |<<interface>>
+------------------+
| + handle()       |
+------------------+
        / \
       /   \
      /     \
     v       v

+----------------------+     +----------------------+
|   ConcreteStateA     |     |   ConcreteStateB     |
+----------------------+     +----------------------+
| + handle()           |     | + handle()           |
+----------------------+     +----------------------+
           |                            |
           | state transition           |
           +----------------------------+
```

---

## Explanation

### Context

* Maintains the current state
* Delegates state-specific behavior to the current state object

### State Interface

* Declares common behavior for all states

### Concrete States

* Implement behavior associated with a specific state
* Can change the context's state dynamically

---

# Workflow Example

```text
+-----------+
|  Context  |
+-----------+
      |
      v
+------------------+
| ConcreteStateA   |
+------------------+
      |
      | transition
      v
+------------------+
| ConcreteStateB   |
+------------------+
```

---

# Example Structure

```text
Context
 └── has-a → State

State
 ├── ConcreteStateA
 └── ConcreteStateB
```

---

# Benefits

* Removes complex if-else or switch statements
* Encapsulates state-specific behavior
* Makes transitions cleaner and maintainable
* Supports Open/Closed Principle

---

# Common Use Cases

* ATM machines
* Media players
* Order management systems
* Traffic light controllers
* Game AI states
