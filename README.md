# Signals
Header only C++17 library provides easy to use object-oriented "callbacks"

## Features

- C++17
- Header-only
- Easy to use
- Thread safe connections via Connector
- Connection to functions, methods, lambdas

## Example

- Create signal:
```cpp
 	cs::Signal<void(const std::string&)> signal;
```

- Connect signal to method
```cpp
	cs::Connector::connect(&signal, &object, &ClassName::method);
```
	or to function/lambda
```cpp
	cs::Connector::connect(&signal, [](const std::strin& message){
		std::cout << message << std::endl;
	});
```
	
- Generate signal:
```cpp
	emit signal("Hello, world!");
```

- Enjoy;
