# Signals
Header only C++17 library provides easy to use object-oriented "callbacks"

## Features

- C++17
- Header-only
- Easy to use
- Connection to functions, methods, lambdas

## Glance

- Create signal
```cpp
 	cs::Signal<void(const std::string&)> signal;
```

- Connect signal to method
```cpp
	cs::Connector::connect(&signal, &object, &ClassName::method);
```

- or to function/lambda

```cpp
	cs::Connector::connect(&signal, [](const std::string& message){
		std::cout << message << std::endl;
	});
```
	
- Generate signal:
```cpp
	emit signal("Hello, world!");
```

- Output
```cpp
	Hello, world!
```

## Example
```cpp
#include <iostream>
#include <string>
#include <signals/signals.hpp>

using SendMessageSignal = cs::Signal<void(const std::string&)>;

// it's better to define signals at classes (OOP style)
class Foo {
public signals:
    SendMessageSignal sendMessage;
};

void onMesageCallback(const std::string& message) {
    std::cout << message << "function!\n";
}

struct Functor {
    void operator()(const std::string& message) {
        std::cout << message << "functor!\n";
    }
};

// signals and slots are just an empty macros
class Bar {
public slots:
    void onMessage(const std::string& message) {
        std::cout << message << "method!\n";
    }
};

int main() {
    Foo foo;
    Bar bar;

    // connect any entity
    cs::Connector::connect(&foo.sendMessage, &onMesageCallback);
    cs::Connector::connect(&foo.sendMessage, Functor{});
    cs::Connector::connect(&foo.sendMessage, &bar, &Bar::onMessage);
    cs::Connector::connect(&foo.sendMessage, [](const std::string& message) {
        std::cout << message << "lambda!\n";
    });

    // generate signal
    emit foo.sendMessage("Hello, world from ");

    return 0;
}
```
