#include "signals.h"
#include <iostream>
#include <string>

using Callback = void(const std::string&);

class A
{
public:
    void generateSignal()
    {
        emit signal("Hello, world!");
    }

public signals:
    es::Signal<Callback> signal;
};

class B
{
public slots:
    void onSignal(const std::string& str)
    {
        std::cout << str << " from method" << std::endl;
    }
};

void onSignal(const std::string& str)
{
    std::cout << str << " from function" << std::endl;
}

int main()
{
    A a;
    B b;

    // member pointer
    es::Connector::connect(a.signal, b, &B::onSignal);

    // function
    es::Connector::connect(a.signal, &onSignal);

    // lambda
    es::Connector::connect(a.signal, [](const std::string& str) {
        std::cout << str << " from lambda" <<std::endl;
    });

    a.generateSignal();
    return 0;
}
