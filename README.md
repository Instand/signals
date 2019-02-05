# EasySignals
Easy to use object-oriented "callbacks"

# How to use

Use C++17 compiler

- Add signals.h to your project;
- Create easy signal:

 	es::Signal<void(const std::string&)> easySignal;

- Connect easySignal to function/any class method:

	es::Connector::connect(&easySignal, someObject, &ClassName::method);

- Generate signal:

	emit easySignal("Hello, world!");

- Enjoy;
