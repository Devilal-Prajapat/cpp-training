
class Widget
{
public:
    Widget();
    ~Widget();
    void doSomething();
private:
    class Impl; // Forward declaration of the implementation class
    Impl* pImpl; // Pointer to the implementation
};
