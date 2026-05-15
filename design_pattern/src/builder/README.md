# Builder Design Pattern

This project demonstrates the **Builder Design Pattern** using UART and SPI communication managers as examples.

## Overview

The Builder Pattern is a creational design pattern that separates the construction of a complex object from its representation. It allows you to build objects step-by-step using a fluent interface, making object creation more flexible and readable.

## The Problem Builder Solves

**Without Builder Pattern:**
- Complex objects require many parameters in constructors
- Constructor overloading becomes unwieldy
- Some parameters are optional, leading to many constructor variants
- Object creation logic is scattered and hard to understand

Example without builder (problematic):
```
UartManager(int rx, int tx, int baud) 
UartManager(int rx, int tx)  // Different order?
UartManager(int baud)         // Missing rx?
// Many confusing overloads...
```

**With Builder Pattern:**
- Clear, readable step-by-step object construction
- Optional parameters easily handled
- Single, intuitive creation interface
- Construction logic centralized

## Pattern Structure

### Roles

1. **Product** - The complex object being constructed (UartManager, SpiManager)
2. **Builder** - Abstract/concrete class defining construction methods (UartBuilder, SPIBuilder)
3. **Director** (Optional) - Orchestrates step-by-step construction using a builder
4. **Client** - Uses the builder to construct products

### Pattern Flow

```
Client
  ↓
  ├─→ Builder (with fluent interface)
  │     ↓
  │   Configure step-by-step
  │     ↓
  │   build() returns Product
  │
  └─→ Director (optional)
        ↓
      Encapsulates construction logic
        ↓
      Calls builder methods
        ↓
      Returns configured Product
```

## Key Characteristics

### 1. Fluent Interface (Method Chaining)
Methods return `*this` allowing chaining:
```cpp
Builder()
  .step1()
  .step2()
  .step3()
  .build();
```

### 2. Private Constructor in Product
Ensures object can only be created through builder:
```cpp
class Product {
private:
    Product() { }  // Private
    friend class Builder;  // Only builder can create
};
```

### 3. Builder Accumulates State
Builder stores partial construction state:
```cpp
class Builder {
private:
    Product product;  // Holds state during construction
public:
    Builder& configure(...) {
        product.member = value;
        return *this;
    }
};
```

### 4. Final build() Method
Validates and returns the constructed object:
```cpp
Product build() {
    // Optional: validate state
    return product;
}
```

## Components

### 1. Interface (IDriver)
Defines a common interface for different communication managers:
- `init()` - Initialize the communication interface
- `write(char c)` - Write a character
- `read()` - Read data
- `display()` - Display configuration details

### 2. Product Classes

#### UartManager
Represents a UART (Universal Asynchronous Receiver-Transmitter) communication interface.

**Configuration Parameters:**
- `rx_pin` - Receive pin number
- `tx_pin` - Transmit pin number
- `baud_rate` - Communication speed (bits per second)

#### SpiManager
Represents an SPI (Serial Peripheral Interface) communication interface.

**Configuration Parameters:**
- `rx_pin` - Receive pin number
- `tx_pin` - Transmit pin number
- `ss_pin` - Slave Select pin number
- `speed` - Communication speed (Hz)

### 3. Builder Classes

#### UartBuilder
Constructs a `UartManager` object with a fluent interface.

**Methods (all return `*this` for chaining):**
- `add_rx_pin(int pin)` - Set receive pin
- `add_tx_pin(int pin)` - Set transmit pin
- `add_baud_rate(int baud)` - Set baud rate
- `build()` - Create and return the configured `UartManager`

#### SPIBuilder
Constructs a `SpiManager` object with a fluent interface.

**Methods (all return `*this` for chaining):**
- `add_rx_pin(int pin)` - Set receive pin
- `add_tx_pin(int pin)` - Set transmit pin
- `add_ss_pin(int pin)` - Set slave select pin
- `add_speed(int speed)` - Set communication speed
- `build()` - Create and return the configured `SpiManager`

### 4. Director Class
Provides pre-configured object creation methods:
- `create_default()` - Default UART configuration (9600 baud)
- `create_high_speed()` - High-speed UART configuration (115200 baud)
- `create_default_spi()` - Default SPI configuration (1MHz)
- `create_high_speed_spi()` - High-speed SPI configuration (10MHz)

## Key Features

### Fluent Interface (Method Chaining)
Builders return `*this` allowing methods to be chained:
```
UartManager uart = UartBuilder()
    .add_rx_pin(2)
    .add_tx_pin(3)
    .add_baud_rate(9600)
    .build();
```

### Private Constructors
Product classes have private constructors and declare builders as `friend`, ensuring objects can only be created through the builder.

### Director Pattern
The Director class encapsulates common object creation patterns:
- Standard configurations
- Pre-set parameters
- Simplified API for users

## Usage Patterns

### Direct Builder Usage
Directly instantiate a builder and configure step-by-step:
```cpp
UartManager uart = UartBuilder()
    .add_rx_pin(2)
    .add_tx_pin(3)
    .add_baud_rate(9600)
    .build();
```

### Director Usage
Use pre-configured creation methods:
```cpp
UartManager uart = Director::create_high_speed();
SpiManager spi = Director::create_default_spi();
```

## Benefits of Builder Pattern

1. **Flexibility** - Configure objects with different parameters on the fly
2. **Readability** - Clear, self-documenting code using method chaining
3. **Immutability** - Once built, objects can be immutable
4. **Step-by-step Construction** - Build complex objects incrementally
5. **Reusability** - Builders can be reused to create multiple objects
6. **Separation of Concerns** - Construction logic separate from product classes

## When to Use

- Creating objects with many optional parameters
- Different representations of the same object needed
- Complex object initialization
- Avoiding constructor overloading
- Step-by-step construction is beneficial

## When NOT to Use

- **Simple objects** with few parameters - overhead not justified
- **Immutable data** that never changes after creation
- **Performance-critical** tight loops - extra allocations/calls overhead
- **Single representation** of objects with fixed parameters

## Advantages

| Advantage | Explanation |
|-----------|--|
| **Cleaner Code** | No constructor overloading, readable method chains |
| **Flexibility** | Easy to add optional parameters, skip parameters easily |
| **Maintainability** | Isolates construction logic from product class |
| **Validation** | Can validate complete state in `build()` method |
| **Multiple Representations** | Same builder pattern for different products |
| **Reusability** | Builders can create multiple instances |
| **Reduced Parameters** | Constructor takes no parameters, builders do |
| **Self-Documenting** | Method names clearly indicate what's being set |

## Disadvantages

| Disadvantage | Impact |
|---|---|
| **Code Complexity** | More classes needed, extra boilerplate |
| **Memory Overhead** | Builder instances take additional memory |
| **Initialization Time** | Slower than direct construction (multiple calls) |
| **Overkill for Simple Objects** | Unnecessary complexity for simple cases |
| **Thread Safety** | Builder state needs synchronization in multithreaded code |

## Real-World Examples

### Web Request Builder
```cpp
HttpRequest request = HttpRequestBuilder()
    .set_url("http://example.com")
    .set_method("POST")
    .add_header("Content-Type", "application/json")
    .add_header("Authorization", "Bearer token")
    .set_body(jsonData)
    .build();
```

### Database Query Builder
```cpp
Query query = QueryBuilder()
    .select("name, email")
    .from("users")
    .where("age > 18")
    .order_by("name")
    .limit(10)
    .build();
```

### Configuration Builder
```cpp
ServerConfig config = ServerConfigBuilder()
    .set_host("localhost")
    .set_port(8080)
    .set_timeout(30)
    .enable_ssl(true)
    .add_middleware("logging")
    .build();
```

## Comparison with Similar Patterns

### Builder vs Abstract Factory
| Aspect | Builder | Abstract Factory |
|--------|---------|-----------------|
| **Purpose** | Builds complex objects step-by-step | Creates families of related objects |
| **Construction** | Gradual, sequential | All at once |
| **Complexity** | Single complex object | Multiple related objects |
| **Emphasis** | How to build | What to create |

### Builder vs Prototype
| Aspect | Builder | Prototype |
|--------|---------|-----------|
| **Focus** | Step-by-step construction | Clone existing objects |
| **Source** | Empty default state | Existing template |
| **Modification** | During construction | After cloning |
| **Use Case** | Complex initialization | Avoiding expensive creation |

## Compilation

```bash
cd /workspace/design_pattern/src/builder
g++ -o builder main.cpp
./builder
```

## Example Output

```
tx 3 rx 2 baud_rate 9600
tx 2 rx 0 baud_rate 115200
tx 2 rx 0 baud_rate 115200
tx 3 rx 2 ss 4 speed_ 1000000
```

## Design Pattern in Action

The code demonstrates:
1. **Separation of construction and representation** - Builders handle construction
2. **Fluent interface** - Methods return `*this` for chaining
3. **Encapsulation** - Private constructors enforce builder usage
4. **Director pattern** - Pre-configured creation methods
5. **Flexibility** - Different configurations easily created

## Implementation Tips and Best Practices

### 1. Return *this for Chaining
```cpp
Builder& set_value(int val) {
    obj.value = val;
    return *this;  // Enables method chaining
}
```

### 2. Make Constructors Private
```cpp
class Product {
private:
    Product() { }  // Prevent direct instantiation
    friend class Builder;
};
```

### 3. Validate in build()
```cpp
Product build() {
    if (obj.rx_pin == 0) throw std::invalid_argument("rx_pin not set");
    if (obj.tx_pin == 0) throw std::invalid_argument("tx_pin not set");
    return obj;  // Only return if valid
}
```

### 4. Provide Default Values
```cpp
class Builder {
private:
    Product obj = Product();  // Default initialized
};
```

### 5. Consider Using std::move
```cpp
Product build() {
    return std::move(obj);  // Avoid copying
}
```

### 6. Use Const References Where Appropriate
```cpp
Builder& set_name(const std::string& name) {
    obj.name = name;  // Avoid unnecessary copies
    return *this;
}
```

### 7. Immutable Products (Optional)
```cpp
class Product {
private:
    const int rx_pin;
    const int tx_pin;
    // Members are const after construction
};
```

## Related Patterns

- **Abstract Factory** - Both create objects, but Builder constructs step-by-step
- **Prototype** - Both create new objects, but Builder allows more control
- **Template Method** - Can be used with Director for creation logic

## References

- Builder Pattern: Separates construction from representation
- Fluent Interface: Method chaining for readable API
- Director Pattern: Encapsulates complex construction logic
