#include "anyclass.h"
#include <QDebug>

AnyClass::AnyClass()
{

}

void AnyClass::tick(int value)
{
    qDebug() << "Tick " << value;
}
