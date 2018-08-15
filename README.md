# EasySignals
Easy to use object-oriented "callbacks"

# How to use

Use C++14 compiler

- Add signals.h to your project;
- Create easy signal:

 	es::Signal<void(const std::string&)> easySignal;

- Connect easySignal to function/any class method:

	es::Connector::connect(this->easySignal, someObject, &ClassName::method);

- Generate signal:

	emit easySignal("Hello, world!");

- Enjoy;
