# SOLID Principles

SOLID is an acronym for five design principles that make software more understandable, flexible, and maintainable.

## The Five Principles

### 1. **S**ingle Responsibility Principle (SRP)
A class should have only one reason to change. Each class should have a single, well-defined responsibility.

**Bad Example:**
```cpp
class User {
public:
    void saveToDatabase() { /* ... */ }
    void sendEmail() { /* ... */ }
    void validatePassword() { /* ... */ }
};
```

**Good Example:**
```cpp
class User {
public:
    std::string getName() { return name; }
private:
    std::string name;
};

class UserRepository {
public:
    void save(const User& user) { /* ... */ }
};

class EmailService {
public:
    void sendEmail(const std::string& email) { /* ... */ }
};
```

### 2. **O**pen/Closed Principle (OCP)
Software entities should be open for extension but closed for modification. You should be able to add new functionality without changing existing code.

**Bad Example:**
```cpp
class PaymentProcessor {
public:
    void processPayment(const std::string& type) {
        if (type == "card") { /* process card */ }
        else if (type == "paypal") { /* process paypal */ }
        // Need to modify this class for each new payment type!
    }
};
```

**Good Example:**
```cpp
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual void process() = 0;
};

class CardPayment : public PaymentMethod {
public:
    void process() override { /* process card */ }
};

class PayPalPayment : public PaymentMethod {
public:
    void process() override { /* process paypal */ }
};

// To add new payment types, just create new classes!
```

### 3. **L**iskov Substitution Principle (LSP)
Subclasses should be substitutable for their base classes. A derived class should not break the expected behavior of the base class.

### 4. **I**nterface Segregation Principle (ISP)
Many client-specific interfaces are better than one general-purpose interface. Clients should not depend on interfaces they don't use.

**Bad Example:**
```cpp
class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};

class Robot : public Worker {
public:
    void work() override { /* robot works */ }
    void eat() override { /* error! robots don't eat */ }
    void sleep() override { /* error! robots don't sleep */ }
};
```

**Good Example:**
```cpp
class Workable {
public:
    virtual ~Workable() = default;
    virtual void work() = 0;
};

class Eatable {
public:
    virtual ~Eatable() = default;
    virtual void eat() = 0;
};

class Sleepable {
public:
    virtual ~Sleepable() = default;
    virtual void sleep() = 0;
};

class Human : public Workable, public Eatable, public Sleepable {
public:
    void work() override { /* ... */ }
    void eat() override { /* ... */ }
    void sleep() override { /* ... */ }
};

class Robot : public Workable {
public:
    void work() override { /* ... */ }
};
```

### 5. **D**ependency Inversion Principle (DIP)
High-level modules should not depend on low-level modules. Both should depend on abstractions (interfaces).

**Bad Example:**
```cpp
class MySQLDatabase {
public:
    void save(const std::string& data) { /* save to MySQL */ }
};

class UserService {
private:
    MySQLDatabase db; // Tightly coupled to MySQLDatabase!
public:
    void saveUser(const std::string& user) {
        db.save(user);
    }
};
```

**Good Example:**
```cpp
class Database {
public:
    virtual ~Database() = default;
    virtual void save(const std::string& data) = 0;
};

class MySQLDatabase : public Database {
public:
    void save(const std::string& data) override { /* save to MySQL */ }
};

class MongoDatabase : public Database {
public:
    void save(const std::string& data) override { /* save to MongoDB */ }
};

class UserService {
private:
    Database* db; // Depends on abstraction, not concrete class
public:
    UserService(Database* database) : db(database) {}
    void saveUser(const std::string& user) {
        db->save(user);
    }
};
```

---

## Files in This Folder

- `single_responsibility.cpp` — Example of SRP
- `open_close.cpp` — Example of OCP
- `liskov_subsitution.cpp` — Example of LSP
- `interface_segration.cpp` — Example of ISP
- `dependency_inversion.cpp` — Example of DIP

## How to Compile

```bash
g++ -std=c++17 -O2 -Wall <filename>.cpp -o out && ./out
```

Replace `<filename>` with the example you want to run.

---

**Learn more:** SOLID principles are foundational to writing clean, maintainable object-oriented code.
