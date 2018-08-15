#include <QCoreApplication>
#include "signaldemo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SignalDemo demo;
    demo.start();

    return a.exec();
}
