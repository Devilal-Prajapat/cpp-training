#include <iostream>
#include <string>

// High-level module that depends on the abstraction (IMessageSender)

// “High-level modules should not depend on low-level modules. Both should depend on abstractions.“

class IMessageSender {
public:
    virtual void send(const std::string& msg) = 0;
    virtual ~IMessageSender() = default;
};

class EmailSender : public IMessageSender {
public:
    void send(const std::string& msg) override {
        std::cout << "Email: "
                  << msg
                  << std::endl;
    }
};

class SMSSender : public IMessageSender {
public:
    void send(const std::string& msg) override {
        std::cout << "SMS: "
                  << msg
                  << std::endl;
    }
};

class NotificationService {
private:
    IMessageSender& sender;

public:
    NotificationService(IMessageSender& s)
        : sender(s) {}

    void notify(const std::string& msg) {
        sender.send(msg);
    }
};


int main() {
    std::cout << "Demonstrating Dependency Inversion Principle" << std::endl;
    EmailSender emailSender;
    SMSSender smsSender;

    NotificationService emailNotification(emailSender);
    NotificationService smsNotification(smsSender);

    emailNotification.notify("Hello via Email!");
    smsNotification.notify("Hello via SMS!");

    return 0;
}

// g++ -o out dependency_inversion.cpp