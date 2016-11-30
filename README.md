# EasySignals
Easy to use object-oriented "callbacks"

# How to use

Use C++11 compiler

- Add easysignals.h to your project;
- Create easy signal:

 	Room427::Signal<std::function<void(int)>> easySignal;

- Connect easySignal to function/any class method:

	Room427::Connector::connect(this->easySignal, someObject, ClassName::method);

- Generate signal:

	easySignal("Hello, world!");

- Enjoy;
