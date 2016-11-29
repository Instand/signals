#ifndef SIGNALDEMO_H
#define SIGNALDEMO_H

#include <QTimer>
#include <QObject>

class SignalDemo : public QObject
{

    Q_OBJECT

public:
    SignalDemo();
    QTimer timer;

    void start();

private slots:
    void tick();
};

#endif // SIGNALDEMO_H
