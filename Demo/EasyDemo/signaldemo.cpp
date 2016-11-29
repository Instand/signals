#include "signaldemo.h"
#include "anyclass.h"
#include "easysignals.h"

SignalDemo::SignalDemo()
{
    //Qt connect
    QObject::connect(&timer, SIGNAL(timeout()), SLOT(tick()));
}

void SignalDemo::start()
{
    timer.start(1000);
}

void SignalDemo::tick()
{
    //EasySignals connection

    //set protype
    using Prototype = std::function<void(int)>;

    //create signal
    Room427::Signal<Prototype> easySignal;

    //create listner
    AnyClass obj;

    //create connection
    Room427::Connector::connect(easySignal, obj, &AnyClass::tick);

    //generate signal
    easySignal(100);
}

